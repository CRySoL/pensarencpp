#!/usr/bin/python

import sys

changes = [\
  ('{#include', '{\#include'),
  ('{#define',  '{\#define'),
  ('{#ifdef',   '{\#ifdef'),
  ('{#ifndef',  '{\#ifndef'),
  ('{#endif',   '{\#endif'),
  ('{#undef',   '{\#undef'),
  ('<', '\<'),
  ('{&', '{\&'),
  ('(&', '(\&'),
  ]


f1 = open(sys.argv[1])
data = f1.read()
f1.close()

for i in changes:
  data = data.replace(i[0], i[1])

f2 = open(sys.argv[2], 'w')
f2.write(data)
f2.close()
