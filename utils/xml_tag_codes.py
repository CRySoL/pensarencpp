#!/usr/bin/python

import sys, re

regex = [
    ('\n?\s*(<programlisting[\s\w\"=]*>)\s*\n*', '\n\n\\1\n [BEGINCODE] \n'),
    ('\n?\s*(</programlisting>)\s*\n', '\n [ENDCODE] \n\\1\n\n'),
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

if f2 != sys.stdout: f2.close()

