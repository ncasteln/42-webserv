#!/usr/bin/python3

import os
import cgi

# print("Content-Type: text/html\n")
# print("<html><body>")
# print("<h1>POST Data Received</h1>")

form = cgi.FieldStorage()

for key in form.keys():
    print(f"<p>{key}: {form.getvalue(key)}</p>")

# print("</body></html>")
