#!/usr/bin/env python3
"""Busca comentarios que repiten al principio el título de su sección.

Uso: runin_titles.py [-w] FICHERO.xml...

En el original, algunas secciones llevan el título integrado en el primer
párrafo, y al pasarlo a DocBook el comentario de ese párrafo conserva el
título delante («Avoid naked pointers See Wrapped.cpp...»), aunque ya esté
en el comentario del <title>. Este programa lista esos casos.

  -w  quita el título repetido de los comentarios

Revise la lista antes de usar -w: hay falsos positivos cuando la frase
empieza de verdad por las palabras del título («Adapter takes one type...»).
"""
import re
import sys


def norm(texto):
    return ' '.join(texto.split())


def repetido(titulo, cuerpo):
    """Caracteres del principio de cuerpo que repiten titulo (0 si no)."""
    letras = re.sub(r'\W', '', titulo.lower())
    i = j = 0
    while i < len(cuerpo) and j < len(letras):
        if re.match(r'\w', cuerpo[i]):
            if cuerpo[i].lower() != letras[j]:
                return 0
            j += 1
        i += 1
    while i < len(cuerpo) and cuerpo[i] in ')”’':
        i += 1
    if len(letras) > 3 and j == len(letras) and \
       len(cuerpo) > i + 5 and cuerpo[i] == ' ':
        return i + 1
    return 0


def main():
    args = sys.argv[1:]
    escribe = '-w' in args
    ficheros = [a for a in args if a != '-w']
    if not ficheros:
        sys.exit(__doc__)
    total = 0
    for f in ficheros:
        t = open(f, encoding='utf-8').read()
        cambios = []
        patron = (r'<!--((?:(?!-->).)*?)-->\s*<title>[^<]*</title>\s*'
                  r'<!--((?:(?!-->).)*?)-->')
        for m in re.finditer(patron, t, re.S):
            texto = m.group(2)
            cuerpo = texto.lstrip()
            n = repetido(norm(m.group(1)), cuerpo)
            if not n:
                continue
            total += 1
            linea = t.count('\n', 0, m.start(2)) + 1
            print(f'{f}:{linea}: {norm(cuerpo[:n + 40])}')
            cambios.append((m.start(2) + len(texto) - len(cuerpo), n))
        if escribe and cambios:
            for inicio, n in reversed(cambios):
                t = t[:inicio] + t[inicio + n:]
            open(f, 'w', encoding='utf-8').write(t)
    print(total, 'comentarios', 'corregidos' if escribe else 'encontrados')


if __name__ == '__main__':
    main()
