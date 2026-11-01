#!/usr/bin/env python3
"""Arregla el escape de caracteres no latin-1 en los listados (TexPost).

dblatex (rawverb.py) envuelve los caracteres de código mayor que 255 de los
listados (por ejemplo, «→») entre las marcas de escape <: y :>, pero con
Python 3 escribe str(bytes), así que en el .tex aparece b'<:'→b':>' y en el
PDF sale basura alrededor del carácter. Además pone la opción escapeinside
en un segundo [...] delante de las opciones del listado.

dblatex llama a este programa (TexPost en pecstyle.specs) con la ruta del
.tex ya compilado. Si corrige algo, sale con 0 y dblatex vuelve a compilar;
si no hay nada que corregir, sale con 1 y no se repite la compilación.
"""
import re
import sys


def main(ruta):
    with open(ruta, encoding='latin-1') as f:
        texto = f.read()
    nuevo = texto.replace("b'<:'", '<:').replace("b':>'", ':>')
    nuevo = re.sub(r'(\\begin\{lst[^}]*\})\[(escapeinside=\{<:\}\{:>\})\]\[',
                   r'\1[\2,', nuevo)
    if nuevo == texto:
        return 1
    with open(ruta, 'w', encoding='latin-1') as f:
        f.write(nuevo)
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1]))
