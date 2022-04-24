import numpy as np
import pandas as pd
import torch
import torch.nn as nn
import torch.nn.functional as F
import random


def create_seq(text, seq_len=5):
    sequences = []
    if len(text) > seq_len:
        for i in range(seq_len, len(text)):
            seq = text[i-seq_len:i+1]
            sequences.append(seq)
        return sequences
    else:
        return [text]

use_cuda = torch.cuda.is_available()
data = open("story.txt", "r", encoding="UTF-8").read().lower().split()
vocab = set(data)
vocab_len = len(data)

vocab_id = {word: i for i, word in enumerate(vocab)}
get_word = {i: word for i, word in enumerate(vocab)}
text_id = [vocab_id[wd] for wd in data]

seqs = create_seq(text_id)
seqs_len = len(seqs)

inputs = []
targets = []

for s in seqs:
    inputs.append(s[:-1])
    targets.append(s[1:])

inputs = np.array(inputs)
targets = np.array(targets)


class WordLSTM(nn.Module):

    def __init__(self, n_hidden=256, n_layers=4, drop_prob=0.3, lr=0.001):
        super().__init__()

        self.drop_prob = drop_prob
        self.n_layers = n_layers
        self.n_hidden = n_hidden
        self.lr = lr

        self.emb_layer = nn.Embedding(vocab_len, 200)
        self.lstm = nn.LSTM(200, n_hidden, n_layers,
                            dropout=drop_prob, batch_first=True)

        self.dropout = nn.Dropout(drop_prob)
        self.fc = nn.Linear(n_hidden, vocab_len)

    def forward(self, x, hidden):
        embedded = self.emb_layer(x)
        lstm_output, hidden = self.lstm(embedded, hidden)
        out = self.dropout(lstm_output)
        out = out.reshape(-1, self.n_hidden)
        out = self.fc(out)
        return out, hidden

    def init_hidden(self, batch_size):
        weight = next(self.parameters()).data
        if (use_cuda):
            hidden = (weight.new(self.n_layers, batch_size, self.n_hidden).zero_().cuda(),
                      weight.new(self.n_layers, batch_size, self.n_hidden).zero_().cuda())
        else:
            hidden = (weight.new(self.n_layers, batch_size, self.n_hidden).zero_(),
                      weight.new(self.n_layers, batch_size, self.n_hidden).zero_())
        return hidden


def get_batches(arr_x, arr_y, batch_size):
    prv = 0
    for n in range(batch_size, arr_x.shape[0], batch_size):
        x = arr_x[prv:n, :]
        y = arr_y[prv:n, :]
        prv = n
        yield x, y


def train(model, epochs=10, batch_size=32, lr=0.001, clip=1, print_every=32):
    global inputs, targets
    opt = torch.optim.Adam(model.parameters(), lr=lr)
    criterion = nn.CrossEntropyLoss()
    if use_cuda:
        print("GPU Training !")
        model.cuda()
    else:
        print("CPU Training !")
    counter = 0
    model.train()
    batches = list(get_batches(inputs, targets, batch_size))
    for e in range(epochs):
        h = model.init_hidden(batch_size)
        for x, y in batches:
            counter += 1
            inputs, targets = torch.from_numpy(x), torch.from_numpy(y)
            if use_cuda:
                inputs, targets = inputs.cuda(), targets.cuda()
            h = tuple([each.data for each in h])
            model.zero_grad()
            output, h = model(inputs, h)
            loss = criterion(output, targets.view(-1).to(dtype=torch.int64))
            loss.backward()
            nn.utils.clip_grad_norm_(model.parameters(), clip)
            opt.step()
            if counter % print_every == 0:
                print("Epoch: {}/{}...".format(e+1, epochs),
                      "Step: {}...".format(counter))


def predict(model, tkn, h=None):
    x = np.array([[vocab_id[tkn]]])
    inputs = torch.from_numpy(x)
    if use_cuda:
        inputs = inputs.cuda()
    h = tuple([each.data for each in h])
    out, h = model(inputs, h)
    p = F.softmax(out, dim=1).data
    p = p.cpu()
    p = p.numpy()
    p = p.reshape(p.shape[1],)
    top_n_idx = p.argsort()[-3:][::-1]
    sampled_token_index = top_n_idx[random.sample([0, 1, 2], 1)[0]]
    return get_word[sampled_token_index], h


def sample(model, size, prime='françaises , français , mes chers'):
    if use_cuda:
        model.cuda()
    model.eval()
    h = model.init_hidden(1)
    toks = prime.split()
    for t in prime.split():
        token, h = predict(model, t, h)
    toks.append(token)
    for _ in range(size-1):
        token, h = predict(model, toks[-1], h)
        toks.append(token)
    return ' '.join(toks)

model = WordLSTM()
if use_cuda:
    model.cuda()
train(model, 20)
input(sample(model, 15))
