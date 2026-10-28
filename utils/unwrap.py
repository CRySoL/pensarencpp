#!/usr/bin/python3
# -*- coding: utf-8 -*-

# Proyecto «Pensar en C++», traducción de «Thinking in C++» de Bruce Eckel
#
# Junta en una sola línea el texto de los <para> y el de los comentarios
# que son claramente texto corrido, para que cada párrafo sea una unidad
# manejable (diffs por párrafo, traducción párrafo a párrafo).
#
# No toca los listados (<programlisting>, <screen>), ni los <para> vacíos
# que esperan traducción, ni los comentarios que no son prosa: cabeceras
# de fichero, URLs, títulos de sección, trozos de código.
#
# Uso:  unwrap.py [-n] fichero.xml ...
#       -n, --simular   dice lo que haría sin escribir nada
#
# Copyright (C) 2026 David Villa
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

import re
import sys

# regiones que se copian tal cual, y las que sí se procesan
BLOQUE = re.compile(
    r'(?P<codigo><(?P<et>programlisting|screen)\b.*?</(?P=et)>)'
    r'|(?P<comentario><!--.*?-->)'
    r'|(?P<parrafo><para\b[^>]*>.*?</para>)',
    re.S)

# un <para> con hijos de bloque se deja en paz: juntarlo estropearía el anidado
HIJOS_BLOQUE = re.compile(
    r'<(para|programlisting|screen|itemizedlist|orderedlist|variablelist'
    r'|table|informaltable|example|figure|footnote)\b')

# señales de que un bloque de comentario NO es prosa
CAMPO = re.compile(r'^\s*(Editor|Traducci|Formateado|Revisi|Autor|Fecha)\b.*:', re.M)
NO_PROSA = re.compile(r'^\s*(//|#|\*|={2,}|-{3,}|\}|<\?)')
FIN_CODIGO = re.compile(r'[;{}]\s*$')


def es_prosa(lineas):
    """¿Este bloque de comentario es claramente texto corrido?

    Pide varias líneas, ninguna con pinta de código o URL, y que estén
    plegadas como prosa: casi todas llenas salvo la última.
    """
    utiles = [l for l in lineas if l.strip()]
    if len(utiles) < 2:
        return False                       # nada que juntar
    texto = '\n'.join(utiles)
    if '://' in texto or CAMPO.search(texto):
        return False                       # URL de referencia o cabecera
    if '--' in texto:
        return False                       # juntarlo crearía un '--' ilegal
    for l in utiles:
        if NO_PROSA.match(l) or FIN_CODIGO.search(l):
            return False
    cortas = sum(1 for l in utiles[:-1] if len(l.strip()) < 40)
    return cortas <= len(utiles[:-1]) * 0.2


def junta_comentario(txt):
    """Junta los bloques de prosa de un comentario, respetando su sangría."""
    cuerpo = txt[4:-3]
    if '\n' not in cuerpo:
        return txt                         # ya cabe en una línea

    m = re.match(r'[^\n]*\n([ \t]*)', cuerpo)
    sangria = m.group(1) if m else '  '
    m = re.search(r'\n([ \t]*)$', cuerpo)       # la del '-->' de cierre
    cierre = m.group(1) if m else sangria

    salida, cambios = [], 0
    for bloque in re.split(r'\n\s*\n', cuerpo):
        lineas = bloque.split('\n')
        if es_prosa(lineas):
            salida.append(sangria + ' '.join(bloque.split()))
            cambios += 1
        else:
            salida.append(bloque.strip('\n'))
    if not cambios:
        return txt
    return '<!--\n' + '\n\n'.join(salida) + '\n' + cierre + '-->'


def junta_parrafo(txt):
    """Pone el contenido de un <para> en una sola línea."""
    ini = txt.index('>') + 1
    apertura, cuerpo, cierre = txt[:ini], txt[ini:-len('</para>')], '</para>'
    if not cuerpo.strip():
        return txt                         # hueco por traducir: se respeta
    if '\n' not in cuerpo:
        return txt
    if HIJOS_BLOQUE.search(cuerpo):
        return txt                         # tiene estructura dentro
    return apertura + ' '.join(cuerpo.split()) + cierre


def procesa(texto):
    salida, pos = [], 0
    n_par = n_com = 0
    for m in BLOQUE.finditer(texto):
        salida.append(texto[pos:m.start()])
        pos = m.end()
        if m.group('codigo'):
            salida.append(m.group('codigo'))
        elif m.group('comentario'):
            nuevo = junta_comentario(m.group('comentario'))
            n_com += nuevo != m.group('comentario')
            salida.append(nuevo)
        else:
            nuevo = junta_parrafo(m.group('parrafo'))
            n_par += nuevo != m.group('parrafo')
            salida.append(nuevo)
    salida.append(texto[pos:])
    return ''.join(salida), n_par, n_com


def comprueba(antes, despues):
    """Sólo se admite haber cambiado espacio en blanco."""
    sin_blancos = lambda s: re.sub(r'\s+', '', s)
    if sin_blancos(antes) != sin_blancos(despues):
        return 'el texto ha cambiado, no sólo los espacios'

    codigo = lambda s: re.findall(
        r'<(programlisting|screen)\b.*?</\1>', s, re.S)
    if codigo(antes) != codigo(despues):
        return 'algún listado ha cambiado'

    for c in re.findall(r'<!--(.*?)-->', despues, re.S):
        if '--' in c or c.endswith('-'):
            return 'se ha generado un comentario XML ilegal'
    return None


def main(argv):
    simular = False
    ficheros = []
    for a in argv:
        if a in ('-n', '--simular'):
            simular = True
        else:
            ficheros.append(a)

    if not ficheros:
        sys.exit(__doc__ or 'uso: unwrap.py [-n] fichero.xml ...')

    for nombre in ficheros:
        antes = open(nombre, encoding='utf-8').read()
        despues, n_par, n_com = procesa(antes)

        problema = comprueba(antes, despues)
        if problema:
            print('%-16s ERROR: %s (no se escribe)' % (nombre, problema))
            continue

        if antes == despues:
            print('%-16s sin cambios' % nombre)
            continue

        if not simular:
            open(nombre, 'w', encoding='utf-8').write(despues)
        print('%-16s %3d párrafos, %3d comentarios%s'
              % (nombre, n_par, n_com, '  (simulado)' if simular else ''))


main(sys.argv[1:])
