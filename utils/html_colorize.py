#!/usr/bin/python

import sys, os

NORMAL, INCODE = range(2)

replaces = [
  ('&lt;', '<'),
  ('&gt;', '>'),
  ('&amp;' , '&'),
  ('///:~', ''),
  ]
  

def colorize(fname):
  fd = open(fname)
  content = fd.readlines()
  fd.close()

  fo = open(fname, 'w')

  status = NORMAL
  
  for line in content:
    if status == NORMAL:    
      if '[BEGINCODE' in line:
        status = INCODE
        listing = ''
      else:
        fo.write(line)

    elif status == INCODE:
      if '[ENDCODE]' in line:
        status = NORMAL

        for r in replaces:
          listing = listing.replace(r[0], r[1])
        
        tmpname = fname + '.code'
        tmpfd = open(tmpname, 'w')
        tmpfd.write(listing)
        tmpfd.close()
        command = 'highlight -fS c++ %s' % tmpname
        fo.write(os.popen(command).read())
      else:
        listing += line

  fo.close()



for fname in sys.argv[1:]:
  print 'Colorizing', fname
  colorize(fname)
