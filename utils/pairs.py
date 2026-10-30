#!/usr/bin/env python3
"""Vuelca las parejas original/traducción de un capítulo para revisarlas.

Uso: pairs.py FICHERO.xml [DESDE [HASTA]]

Por cada comentario seguido de un <para> o un <title>, escribe la línea del
comentario, el texto original (EN) y la traducción (ES), cada uno en una
sola línea. Las notas al pie de la traducción se abrevian como [NOTA].
DESDE y HASTA limitan el volcado a ese rango de líneas del fichero.
"""
import re
import sys


def norm(texto):
    return ' '.join(texto.split())


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    t = open(sys.argv[1], encoding='utf-8').read()
    desde = int(sys.argv[2]) if len(sys.argv) > 2 else 0
    hasta = int(sys.argv[3]) if len(sys.argv) > 3 else 10**9
    for m in re.finditer(r'<!--(.*?)-->', t, re.S):
        linea = t.count('\n', 0, m.start()) + 1
        if linea < 15 or not desde <= linea < hasta:
            continue  # la cabecera del fichero también es un comentario
        b = re.match(r'\s*<(para|title)>(.*?)</\1>', t[m.end():], re.S)
        if not b:
            continue
        es = re.sub(r'<footnote>.*?</footnote>', '[NOTA]', b.group(2),
                    flags=re.S)
        print(f'{linea} EN: {norm(m.group(1))}\n     ES: {norm(es)}')


if __name__ == '__main__':
    main()
