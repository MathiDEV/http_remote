#include <stdio.h>
#include <unistd.h>

int countoc(char *str, char to_find);

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putnbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10) {
        my_putnbr(nb / 10);
    }
    my_putchar(nb % 10 + '0');
}

void my_putstr_FORTESTING(char *s)
{
    int i = -1;

    while (s[++i])
        write(1, &s[i], 1);
}

void newline(void)
{
    write(1, "\n", 1);
}

int main(int argc, char *argv[])
{
    int ret = 0;

    my_putstr_FORTESTING("$[Basic]%");
    ret = countoc("EPITECH", 'E');
    my_putnbr(ret);
    newline();

    my_putstr_FORTESTING("$[Advanced]%");
    ret = countoc(
    "SALUT LE CODDING CLUB MOI AUJOURDHUI CA VA PLUTOT BIEN JAI CODE LA MOULI "
    "TOUTE LAPRES MIDI ET JECRIS EN MAAAAJJJUSS C U L E S",
    ' ');
    my_putnbr(ret);
    newline();

    my_putstr_FORTESTING("$[Count everything]%");
    ret = countoc("..............", '.');
    my_putnbr(ret);
    newline();

    my_putstr_FORTESTING("$[Nothing to count]%");
    ret = countoc("EPITECH", '7');
    my_putnbr(ret);
    newline();

    my_putstr_FORTESTING("$[Only one in a sea of bullshit]%");
    ret = countoc("asdewfqwefqwefqewf155wef5ew56fwef4ew5f1we5f1wefu9bfqwpyf"
                  "gbhryqw&ubfoywebfoqewybfqywfqwefqewf78515fw0",
    '&');
    my_putnbr(ret);
    newline();
    return 0;
}
