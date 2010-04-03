#!/usr/bin/python

import sys, re

regex = [
    ['\s*(<xi:include.*)', '\n\\1'],
    ['\n\s*\n\s*//:\s*V(\d)C(\d{2}):([\w\d\.]+).*\n',
     '''

<example>
<title>C\\2/\\3</title>
<programlisting language="C++">
<xi:include parse="text" href="./code_v\\1/C\\2/\\3"/>
</programlisting>
</example>
'''],
    ['\$Date:\s(\d{4}-\d{2}-\d{2}).*\$', '\\1'],
    ['\$Revision:\s(\d+).*\$','\\1'],
    ]

# compile regex
for i in range(len(regex)):
    regex[i][0] = re.compile(regex[i][0], re.M)


if len(sys.argv) > 1:
    f1 = open(sys.argv[1])
else:
    f1 = sys.stdin

data = f1.read()

for before, after in regex:
#    data = re.compile(i[0], re.M).sub(i[1], data)
    data = before.sub(after, data)

if len(sys.argv) > 2:
    f2 = open(sys.argv[2], 'w')
else:
    f2 = sys.stdout

f2.write(data)

if f2 != sys.stdout: f2.close()

