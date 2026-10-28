#!/usr/bin/python3
"""Notas al pie del original del volumen 2.

En el original las notas aparecen como marcas [15] y su texto no está en el
repositorio. Este script lo saca del HTML del original, cuya URL figura en la
cabecera de cada capítulo:

    curl -o TicV2.html https://web.mit.edu/merolish/ticpp/TicV2.html

La numeración es única para todo el volumen. Ver DOCBOOK, «Notas al pie».

Uso: footnotes.py [-o] TicV2.html [FICHERO.xml...]
  sin ficheros  imprime todas las notas
  con ficheros  lista las marcas [n] que quedan en el texto traducido, con la
                nota original, para sustituirlas por <footnote>
  -o            lista en su lugar las notas que cita el original (los
                comentarios): las que hay que añadir al traducir
"""

import html
import re
import sys

NOTE = re.compile(r'<div id=ftn(\d+)>(.*?)</div>', re.S)
MARK = re.compile(r'\[(\d{1,3})\]')
COMMENT = re.compile(r'<!--.*?-->', re.S)
LISTING = re.compile(r'<(programlisting|screen)\b.*?</\1>', re.S)


def load_notes(path):
    "{número: texto} a partir del HTML del original (Windows-1252)"
    source = open(path, 'rb').read().decode('cp1252', errors='replace')
    notes = {}
    for m in NOTE.finditer(source):
        body = re.sub(r'<i>(.*?)</i>', r'«\1»', m.group(2), flags=re.S)
        body = html.unescape(re.sub(r'<[^>]+>', '', body))
        text = ' '.join(body.split())
        notes[int(m.group(1))] = re.sub(r'^\[\d+\]\s*', '', text)
    return notes


def blank(m):
    "borra un trozo sin cambiar la numeración de líneas"
    return re.sub(r'[^\n]', ' ', m.group(0))


def marks(path, in_comments):
    "(línea, número) de cada marca, en el texto traducido o en los comentarios"
    text = LISTING.sub(blank, open(path, encoding='utf-8').read())
    if in_comments:
        regions = [(m.start(), m.group(0)) for m in COMMENT.finditer(text)]
    else:
        regions = [(0, COMMENT.sub(blank, text))]
    for start, region in regions:
        for m in MARK.finditer(region):
            yield text.count('\n', 0, start + m.start()) + 1, int(m.group(1))


def main():
    args = sys.argv[1:]
    original = '-o' in args
    args = [a for a in args if a != '-o']
    if not args:
        sys.exit(__doc__)

    notes = load_notes(args[0])
    if len(args) == 1:
        for n in sorted(notes):
            print(f'[{n}] {notes[n]}')
        return

    for path in args[1:]:
        seen = set()
        for line, n in marks(path, original):
            if original and n in seen:
                continue
            seen.add(n)
            print(f'{path}:{line} [{n}] {notes.get(n, "(no existe en el original)")}')


if __name__ == '__main__':
    main()
