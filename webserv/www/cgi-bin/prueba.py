#!/usr/bin/env python3
import os
import sys

print("Content-Type: text/html")
print()
print("<h1>CGI Test</h1>")
print("<p>METHOD: " + os.environ.get("REQUEST_METHOD", "none") + "</p>")
print("<p>QUERY: " + os.environ.get("QUERY_STRING", "none") + "</p>")
print("<p>CONTENT_LENGTH: " + os.environ.get("CONTENT_LENGTH", "none") + "</p>")
body = sys.stdin.read()
print("<p>BODY: " + body + "</p>")