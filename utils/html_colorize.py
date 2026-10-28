#!/usr/bin/python3

import subprocess
import sys

# Los HTML generados por los XSL usan 'chunker.output.encoding'
# (ISO-8859-1). Se trabaja con latin-1 porque es transparente a nivel de
# byte: cualquier secuencia se lee y se reescribe sin alterarla, sea cual
# sea la codificación real del fichero.
ENCODING = 'iso-8859-1'

NORMAL, INCODE = range(2)
SKIP_LINES = [1,2,3,4]

replaces = [
  ('&lt;', '<'),
  ('&gt;', '>'),
  ('&amp;' , '&'),
#  ('&#13;', ''),
  ]


def colorize(fname):
  fd = open(fname, encoding=ENCODING)
  content = fd.readlines()
  fd.close()

  fo = open(fname, 'w', encoding=ENCODING)

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
        tmpfd = open(tmpname, 'w', encoding=ENCODING)
        tmpfd.write(listing)
        tmpfd.close()
#        command = ['highlight', '--data-dir', './stylesheets/highlight',
#                   '--style', 'emacs21', '-fS', 'c++', tmpname]

        command = ['highlight', '--style=edit-emacs', '-fS', 'c++', tmpname]

#        command = ['highlight', '-fS', 'c++', tmpname]
        fo.write(subprocess.run(command, stdout=subprocess.PIPE,
                                check=True).stdout.decode(ENCODING))

      else:
        #if not nline in SKIP_LINES:
        listing += line
        nline += 1


  fo.close()



for fname in sys.argv[1:]:
  print('Colorizing', fname)
  colorize(fname)
