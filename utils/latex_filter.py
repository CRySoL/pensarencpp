#!/usr/bin/python

import sys
import re

changes = [\
  ('\\texttt{#', '\\texttt{\#'),
  ('{#include',  '{\\#include'),
  ('{#define',   '{\\#define'),
  ('{#ifdef',    '{\\#ifdef'),
  ('{#ifndef',   '{\\#ifndef'),
  ('{#endif',    '{\\#endif'),
  ('{#undef',    '{\\#undef'),
  ('\\texttt{<<',  '\\texttt{FIXME'),
  ('\\texttt{>>',  '\\texttt{FIXME'),
  ('{&}', '{\\&}'),
  ]

changes2 = [\
  ('(?!\\)&', '\\&'),
  ]

changes = [\
  ('{<<',  '{\\textless{}\\textless{}'),
  ('{>>',  '{\\textgreater{}\\textgreater{}'),
  ]



if len(sys.argv) > 1: 
    f1 = open(sys.argv[1])
else:
    f1 = sys.stdin
  
data = f1.read()

for i in changes:
    data = data.replace(i[0], i[1])
#  data = re.sub(i[0], i[1], data)

if len(sys.argv) > 2:
    f2 = open(sys.argv[2], 'w')
else:
    f2 = sys.stdout
    
f2.write(data)

