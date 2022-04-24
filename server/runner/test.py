import os, json, base64

all_files = {}
for subdir, _, files in os.walk("."):
    for file in files:
        file = os.path.join(subdir, file)
        if os.path.isfile(file):
            with open(file, "rb") as f:
                data = f.read()            
            file = "/".join(file.split("/")[1:])
            all_files[file] = base64.b64encode(data).decode("utf-8")
print({"status": True, "body": json.dumps(all_files)})