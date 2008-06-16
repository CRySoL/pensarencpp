#!/usr/bin/python

import sys, os

NORMAL, INCODE = range(2)
SKIP_LINES = [1,2,3,4]

replaces = [
  ('&lt;', '<'),
  ('&gt;', '>'),
  ('&amp;' , '&'),
  ('&#13;', ''),
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
        nline = 0
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
        command = 'highlight --data-dir ./stylesheets/highlight ' +\
                  '--style emacs21 -fS c++ %s' % tmpname

#        command = 'highlight -fS c++ %s' % tmpname
        fo.write(os.popen(command).read())

      else:
        if not nline in SKIP_LINES:
          listing += line
        nline += 1


  fo.close()



for fname in sys.argv[1:]:
  print 'Colorizing', fname
  colorize(fname)
