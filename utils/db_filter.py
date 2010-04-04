#!/usr/bin/python

import sys, re

changes = [\
    ('<kw>',      '<literal role="keyword">'),
    ('</kw>',     '</literal>'),
    ('<oper>',    '<literal role="operator">'),
    ('</oper>',  '</literal>'),
    (' ///:~\n',  '')
    ]


if len(sys.argv) > 1:
    f1 = open(sys.argv[1])
else:
    f1 = sys.stdin

data = f1.read()

for i in changes:
    data = data.replace(i[0], i[1])

if len(sys.argv) > 2:
    f2 = open(sys.argv[2], 'w')
else:
    f2 = sys.stdout

f2.write(data)

