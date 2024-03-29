import sys
from urllib import request, parse, error
import http.server
import os
import platform
import json
import base64

def is_binary(file_name):
    try:
        with open(file_name, 'tr') as check_file:
            check_file.read()
            return False
    except:
        return True

def parse_post_data(data):
    data = data.split('&')
    data = [x.split('=') for x in data]
    data = {x[0]: x[1] for x in data}
    return data

class CobraServer:
    def __init__(self, ip, port = "8888"):
        self.url = ip
        self.port = port
    def post_to(self, endpoint, data):
        data = parse.urlencode(data).encode()
        req =  request.Request("http://%s:%s/%s.php" % (self.url, self.port, endpoint), data=data)
        return request.urlopen(req)

def ping(data = {}):
    return {"status": True}

def ls(data = {}):
    if "dir" not in data:
        return {"status": True, "body": "[]"}
    if ".." in data["dir"]:
        return {"status": True, "body": "[]"}
    data["dir"] = os.path.join(".", data["dir"])
    if not os.path.isdir(data["dir"]):
        return {"status": True, "body": "[]"}
    files = []
    for file in os.listdir(data["dir"]):
        filepath = file.replace("\\", "/")
        filetype = "file" if os.path.isfile(os.path.join(data["dir"], file)) else "dir"
        files.append({"name": file, "type": filetype, "path": data["dir"] + "/" + filepath, "size": os.path.getsize(os.path.join(data["dir"], file))})
    return {"status": True, "body": json.dumps(files)}

def cat(data = {}):
    if "dir" not in data:
        return {"status": True, "body": ""}
    if ".." in data["dir"]:
        return {"status": True, "body": "[]"}
    data["dir"] = os.path.join(".", data["dir"])
    if not os.path.isfile(data["dir"]):
        return {"status": True, "body": ""}
    if is_binary(data["dir"]):
        return {"status": True, "body": "[binary content]"}
    with open(data["dir"], "r") as f:
        return {"status": True, "body": f.read()}

def getfiles(data = {}):
    all_files = {}
    check_file_types = False
    if "filetypes" in data:
        filetypes = data["filetypes"].split(",")
        check_file_types = True
    for subdir, _, files in os.walk("."):
        for file in files:
            file = os.path.join(subdir, file)
            if os.path.isfile(file):
                if check_file_types and os.path.splitext(file)[1][1:] not in filetypes:
                    continue
                with open(file, "rb") as f:
                    data = f.read()
                file = file.replace("\\", "/")
                file = "/".join(file.split("/")[1:])
                all_files[file] = base64.b64encode(data).decode("utf-8")
    return {"status": True, "body": json.dumps(all_files)}

endpoints = {
    "ping": ping,
    "ls": ls,
    "cat": cat,
    "getfiles": getfiles
}

class Handler( http.server.CGIHTTPRequestHandler ):
    def log_message(self, format, *args):
        pass
    def do_POST(self):
        ip = self.address_string()
        if ip not in [admin_ip, "127.0.0.1", "::1"]:
            self.send_response(400)
            self.end_headers()
            return
        endpoint = self.path.split("/")[-1]
        if (self.headers['Content-Length']):
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            data = parse_post_data(post_data.decode("utf-8"))
        else:
            data = {}
        if endpoint in endpoints:
            result = endpoints[endpoint](data)
            if not result["status"]:
                self.send_response(400)
            else:
                if "body" in result:
                    self.send_response(200)
                    self.send_header("Content-type", "application/json")
                    self.end_headers()
                    self.wfile.write(result["body"].encode("utf-8"))
                    return
                else:
                    self.send_response(200)
        else:
            self.send_response(404)
        self.end_headers()

if len(sys.argv) != 2:
    print("Usage: %s <ip>" % sys.argv[0])
    exit(1)

if not sys.argv[1].count(".") != 4:
    print("Invalid IP")
    exit(1)

admin_ip = sys.argv[1]

server = CobraServer(admin_ip)
try:
    server.post_to("connect", {"name": os.getlogin(), "port": "8887", "os": platform.system()})

    server_address = ("", 8887)
    httpd = http.server.HTTPServer(server_address, Handler)
    print('''\033[1m   ___          _ _               ___ _       _     
  / __\___   __| (_)_ __   __ _  / __\ |_   _| |__  
 / /  / _ \ / _` | | '_ \ / _` |/ /  | | | | | '_ \ 
/ /__| (_) | (_| | | | | | (_| / /___| | |_| | |_) |
\____/\___/ \__,_|_|_| |_|\__, \____/|_|\__,_|_.__/ 
                          |___/           ©MathiDev\033[0m''')
    httpd.serve_forever()
except error.URLError:
    print("\033[91mCan't connect to host !\033[0m")
except OSError:
    print("\033[91mCan't connect serve on port !\033[0m")
except KeyboardInterrupt:
    print("\n\033[94mDisconnected from host !\033[0m")