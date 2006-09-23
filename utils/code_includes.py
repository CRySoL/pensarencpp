#!/usr/bin/python

import sys, re

regex = [
    ('\n\n\s*//:\sC(\d{2}):([\w\d\.]+)\s*', '<programlisting>\n' +\
     '<xi:include parse="text" href="./code/C\\1/\\2"/>\n' +\
     '</programlisting>\n'),
    ]

if len(sys.argv) > 1: 
    f1 = open(sys.argv[1])
else:
    f1 = sys.stdin
  
data = f1.read()

for i in regex:
    data = re.compile(i[0]).sub(i[1], data)

if len(sys.argv) > 2:
    f2 = open(sys.argv[2], 'w')
else:
    f2 = sys.stdout
    
f2.write(data)

