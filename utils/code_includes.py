#!/usr/bin/python

import sys, re

regex = [
    ('\n\s*\n\s*//:\s*C(\d{2}):([\w\d\.]+)\s*[\{\}OL]*', '\n\n<programlisting>\n' +\
     '<xi:include parse="text" href="./code/C\\1/\\2"/>\n' +\
     '</programlisting>'),
    ]

if len(sys.argv) > 1: 
    f1 = open(sys.argv[1])
else:
    f1 = sys.stdin
  
data = f1.read()

for i in regex:
    data = re.compile(i[0], re.M).sub(i[1], data)

if len(sys.argv) > 2:
    f2 = open(sys.argv[2], 'w')
else:
    f2 = sys.stdout
    
f2.write(data)

