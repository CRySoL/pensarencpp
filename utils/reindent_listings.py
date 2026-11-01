#!/usr/bin/env python3
"""Normaliza la sangría de los fragmentos de código escritos en el XML.

Uso: reindent_listings.py [-n] [-v] FICHERO.xml...

Los listados completos se incluyen desde los fuentes y tienen la sangría
del original (dos espacios por nivel). Los fragmentos escritos a mano en
<programlisting> arrastran a veces el sangrado del propio XML o usan otra
medida. Para cada fragmento, este programa:

  - convierte los tabuladores del principio de línea en espacios (de 8 en 8);
  - quita el margen que comparten todas las líneas;
  - si todas las sangrías son múltiplos de 4 (o de 8), las reduce a dos
    espacios por nivel, como en el original.

No toca los listados incluidos (los que empiezan por //: o xi:include), los
makefiles (language="Make", donde el tabulador es obligatorio) ni los
fragmentos con alineaciones que no siguen la regla (continuaciones de
línea alineadas con un paréntesis, por ejemplo): en esos solo quita el
margen común.

  -n  no modifica los ficheros; solo informa
  -v  muestra cada fragmento que cambia, antes y después
"""
import re
import sys
from functools import reduce
from math import gcd

LISTADO = re.compile(r'(<programlisting([^>]*)>)(.*?)(</programlisting>)', re.S)


def sangria(linea):
    return len(linea) - len(linea.lstrip(' '))


def normaliza(cuerpo):
    if re.match(r'\s*(//:|<xi:include)', cuerpo):
        return cuerpo
    # la primera línea puede ir pegada a la etiqueta: no cuenta para el margen
    lineas = cuerpo.split('\n')
    pegada = lineas[0].strip() != ''
    lineas = [re.sub(r'^[ \t]+', lambda m: m.group(0).expandtabs(8), l)
              for l in lineas]
    resto = lineas[1:] if pegada else lineas
    utiles = [l for l in resto if l.strip()]
    if not utiles:
        return cuerpo
    margen = min(sangria(l) for l in utiles)
    resto = [l[margen:] if l.strip() else l.strip(' \t') for l in resto]
    niveles = {sangria(l) for l in resto if l.strip()} - {0}
    paso = reduce(gcd, niveles, 0)
    if paso in (4, 8):
        resto = [' ' * (sangria(l) * 2 // paso) + l.lstrip(' ')
                 if l.strip() else l for l in resto]
    return '\n'.join(([lineas[0]] if pegada else []) + resto)


def main():
    args = sys.argv[1:]
    simula = '-n' in args
    detalle = '-v' in args
    ficheros = [a for a in args if a not in ('-n', '-v')]
    if not ficheros:
        sys.exit(__doc__)
    for f in ficheros:
        texto = open(f, encoding='utf-8').read()
        cambios = 0

        def cambia(m):
            nonlocal cambios
            if 'Make' in m.group(2):
                return m.group(0)
            nuevo = normaliza(m.group(3))
            if nuevo == m.group(3):
                return m.group(0)
            cambios += 1
            if detalle:
                print(f'--- {f}\n{m.group(3)}\n+++\n{nuevo}\n')
            return m.group(1) + nuevo + m.group(4)

        texto = LISTADO.sub(cambia, texto)
        if cambios:
            print(f'{f}: {cambios} fragmentos'
                  + ('  (simulado)' if simula else ''))
            if not simula:
                open(f, 'w', encoding='utf-8').write(texto)


if __name__ == '__main__':
    main()
