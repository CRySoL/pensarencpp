#!/usr/bin/python

import sys, re

regex = [
    ('\s*(<xi:include.*)', '\\1\n'),
    ('\n\s*\n\s*//:\s*C(\d{2}):([\w\d\.]+)\s*[\{\}OL]*', '\n\n<programlisting>\n' +\
     '<xi:include parse="text" href="./code/C\\1/\\2"/>\n' +\
     '</programlisting>\n\n'),
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

if f2 != sys.stdout: f2.close()

