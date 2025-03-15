import os
import cgi
import cgitb
import urllib.parse

print("Content-Type: text/plain\n")

dir_path = os.environ.get("UPLOAD_PATH")

query_string = os.environ.get('QUERY_STRING', '')

resource = query_string[query_string.find("=") + 1:]

if ".." in resource:
	print("invalid filename\n")

file_path = f"{dir_path}/{resource}"

if os.path.exists(file_path):
	os.remove(file_path)
	print(f"File '{resource}' successfully got deleted\n")
else:
	print(f"no such file '{resource}' exists\n")





