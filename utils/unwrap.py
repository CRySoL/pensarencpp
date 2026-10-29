#!/usr/bin/python3
# -*- coding: utf-8 -*-

# Proyecto «Pensar en C++», traducción de «Thinking in C++» de Bruce Eckel
#
# Junta en una sola línea el texto de los <para> y el de los comentarios
# que son claramente texto corrido, para que cada párrafo sea una unidad
# manejable (diffs por párrafo, traducción párrafo a párrafo).
#
# Los <para> con notas al pie se juntan enteros, nota incluida, con la
# forma <footnote><para>...</para></footnote>. En los comentarios, cada
# elemento de una lista (1. ..., · ..., * ...) se junta por separado.
#
# No toca los listados (<programlisting>, <screen>), ni los <para> vacíos
# que esperan traducción, ni los comentarios que no son prosa: cabeceras
# de fichero, URLs, títulos de sección, trozos de código, salidas de
# programas. En un <para> que contiene listas, tablas o código solo se
# juntan los <para> de dentro.
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

# lo que el recorrido de procesa() busca: listados, comentarios y párrafos
INICIO = re.compile(r'<(?P<et>programlisting|screen)\b|(?P<com><!--)|(?P<par><para\b)')
ETIQUETA_PARA = re.compile(r'<(/?)para\b[^>]*?(/?)>')

# un <para> con estos hijos no se junta entero: se entra en él
HIJOS_BLOQUE = re.compile(
    r'<(programlisting|screen|literallayout|itemizedlist|orderedlist'
    r'|variablelist|table|informaltable|example|figure|informalfigure'
    r'|mediaobject|blockquote|note|warning|tip|sidebar)\b')

# señales de que un bloque de comentario NO es prosa
CAMPO = re.compile(r'^\s*(Editor|Traducci|Formateado|Revisi|Autor|Fecha)\b.*:', re.M)
EMACS = re.compile(r'Local [Vv]ariables|ispell|coding:')
NO_PROSA = re.compile(r'^\s*(//|#|\*|={2,}|-{3,}|\}|<\?)')
# '#' y '==' también empiezan frases («#ifdef statement and...», «==. The...»)
NO_PROSA_SALVO_FRASE = re.compile(r'^\s*(#|={2,})')
FIN_CODIGO = re.compile(r'([{}]|\)\s*;)\s*$')
FIN_PUNTO_Y_COMA = re.compile(r';\s*$')
SIGNO_CODIGO = re.compile(r'[(){}=<>\[\]&|]')

# solo cuentan como blancos los ASCII: el espacio duro (U+00A0) se respeta
BLANCO = re.compile(r'[ \t\r\n]+')

PALABRA = re.compile(r"[A-Za-zÀ-ÿ'’-]+")

# comienzo de un elemento de lista dentro de un comentario; «1» solo en una
# línea, con el texto debajo, también cuenta
MARCA_LISTA = re.compile(r'^\s*(\d+[.)]|[·•*#-]|\[\d+\])\s')
SOLO_NUMERO = re.compile(r'^\s*\d+\s*$')


def junta(texto):
    """Pone el texto en una línea, con un solo espacio entre palabras."""
    return BLANCO.sub(' ', texto).strip(' ')


def proporcion_palabras(linea):
    """Fracción de trozos de la línea que son palabras normales."""
    trozos = linea.split()
    limpios = [t.strip('.,:;!?"\'“”‘’()') for t in trozos]
    return sum(1 for t in limpios if PALABRA.fullmatch(t)) / max(len(trozos), 1)


def es_codigo(linea, lista=False):
    """¿La línea tiene pinta de código, de salida de programa o de marca?

    Acabar en llave o en ');' es siempre código. Un ';' final solo lo es
    si la línea tiene signos de código: en una frase no cuenta. Empezar
    por '#' o '==' no cuenta si la línea es claramente una frase. Una
    línea con signos de código y pocas palabras también es código (con
    más exigencia en los elementos de lista, que se juntan aunque tengan
    líneas cortas).
    """
    if FIN_CODIGO.search(linea):
        return True
    if FIN_PUNTO_Y_COMA.search(linea) and SIGNO_CODIGO.search(linea):
        return True
    if NO_PROSA.match(linea):
        return not (NO_PROSA_SALVO_FRASE.match(linea)
                    and proporcion_palabras(linea) >= 0.75)
    if SIGNO_CODIGO.search(linea):
        return proporcion_palabras(linea) < (0.6 if lista else 0.5)
    return False


def es_prosa(lineas, lista=False):
    """¿Estas líneas son claramente texto corrido?

    Pide varias líneas, ninguna con pinta de código o URL, y que estén
    plegadas como prosa: casi todas llenas salvo la última. En un elemento
    de lista no se mira lo llenas que están, y su marca no cuenta como
    señal de código.
    """
    utiles = [l for l in lineas if l.strip()]
    if len(utiles) < 2:
        return False                       # nada que juntar
    texto = '\n'.join(utiles)
    if '://' in texto or CAMPO.search(texto) or EMACS.search(texto):
        return False                       # URL de referencia o cabecera
    if '--' in texto:
        return False                       # juntarlo crearía un '--' ilegal
    for i, l in enumerate(utiles):
        if i == 0 and lista:
            if SOLO_NUMERO.match(l):
                continue
            l = MARCA_LISTA.sub('', l, count=1)
        if es_codigo(l, lista):
            return False
    if lista:
        return True
    cortas = sum(1 for l in utiles[:-1] if len(l.strip()) < 40)
    return cortas <= len(utiles[:-1]) * 0.2


def elementos(lineas):
    """Parte un bloque en elementos de lista; si no es una lista, uno solo."""
    grupos = []
    for l in lineas:
        if not grupos or MARCA_LISTA.match(l) or SOLO_NUMERO.match(l):
            grupos.append([l])
        else:
            grupos[-1].append(l)
    return grupos


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
        # los elementos de una lista se juntan cada uno por su lado, nunca
        # entre sí
        partes = []
        for grupo in elementos(bloque.strip('\n').split('\n')):
            lista = bool(MARCA_LISTA.match(grupo[0]) or SOLO_NUMERO.match(grupo[0]))
            if es_prosa(grupo, lista):
                partes.append(sangria + junta(' '.join(grupo)))
                cambios += 1
            else:
                partes.append('\n'.join(grupo))
        salida.append('\n'.join(partes))
    if not cambios:
        return txt
    return '<!--\n' + '\n\n'.join(salida) + '\n' + cierre + '-->'


def fin_de_para(texto, ini):
    """Posición tras el </para> que cierra el <para> que empieza en ini."""
    nivel = 0
    for m in ETIQUETA_PARA.finditer(texto, ini):
        if m.group(2):
            continue                       # <para/>: no abre ni cierra
        nivel += -1 if m.group(1) else 1
        if nivel == 0:
            return m.end()
    raise ValueError('<para> sin cerrar en la posición %d' % ini)


def junta_parrafo(txt):
    """Pone el contenido de un <para> en una sola línea, notas incluidas.

    Devuelve None si el párrafo tiene estructura de bloque dentro.
    """
    ini = txt.index('>') + 1
    apertura, cuerpo, cierre = txt[:ini], txt[ini:-len('</para>')], '</para>'
    if not cuerpo.strip():
        return txt                         # hueco por traducir: se respeta
    if HIJOS_BLOQUE.search(cuerpo):
        return None                        # tiene estructura dentro
    if '\n' not in cuerpo:
        return txt
    junto = junta(cuerpo)
    # dentro de las notas, el espacio junto a las etiquetas sobra
    junto = re.sub(r'(<footnote\b[^>]*>|<para\b[^>]*>) ', r'\1', junto)
    junto = re.sub(r' (</para>|</footnote>|<para\b[^>]*>)', r'\1', junto)
    return apertura + junto + cierre


def procesa(texto):
    salida, pos = [], 0
    n_par = n_com = 0
    while True:
        m = INICIO.search(texto, pos)
        if not m:
            break
        salida.append(texto[pos:m.start()])
        if m.group('et'):
            fin = texto.index('</%s>' % m.group('et'), m.start()) + len(m.group('et')) + 3
            salida.append(texto[m.start():fin])
        elif m.group('com'):
            fin = texto.index('-->', m.start()) + 3
            nuevo = junta_comentario(texto[m.start():fin])
            n_com += nuevo != texto[m.start():fin]
            salida.append(nuevo)
        elif texto[m.start():texto.index('>', m.start()) + 1].endswith('/>'):
            fin = texto.index('>', m.start()) + 1
            salida.append(texto[m.start():fin])
        else:
            fin = fin_de_para(texto, m.start())
            nuevo = junta_parrafo(texto[m.start():fin])
            if nuevo is None:
                # se copia la etiqueta de apertura y se sigue por dentro
                fin = texto.index('>', m.start()) + 1
                salida.append(texto[m.start():fin])
            else:
                n_par += nuevo != texto[m.start():fin]
                salida.append(nuevo)
        pos = fin
    salida.append(texto[pos:])
    return ''.join(salida), n_par, n_com


def comprueba(antes, despues):
    """Sólo se admite haber cambiado espacio en blanco."""
    sin_blancos = lambda s: BLANCO.sub('', s)
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
