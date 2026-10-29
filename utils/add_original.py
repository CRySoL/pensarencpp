#!/usr/bin/python3
"""Añade el original en inglés, comentado, a los capítulos que no lo tienen.

Delante de cada título y de cada párrafo traducido que no tenga ya su
comentario, pone el texto original como en el resto del libro:

    <!--
    One of the most compelling features about C++ is code reuse...
    -->
    <para>Una de las características más atractivas de C++...</para>

El original es el HTML del volumen 1 que publica el MIT, un fichero por
capítulo (ChapterNN.html, AppendixX.html, Preface.html):

    curl -O https://web.mit.edu/merolish/ticpp/Chapter15.html

Las dos secuencias de bloques (títulos, párrafos y listados) se alinean con
programación dinámica: los listados (//: C15:Fichero.cpp) y los títulos
sirven de anclas, y los párrafos se emparejan por su longitud, admitiendo
que el traductor haya juntado dos párrafos en uno o partido uno en dos. Las
notas al pie del original se añaden al comentario del párrafo que las cita,
detrás de su texto, como «[54] Texto de la nota».

Uso: add_original.py [-n] [-v] ORIGINAL.html FICHERO.xml
  -n  dice lo que haría sin escribir nada
  -v  muestra cada pareja (original, traducción) para revisarla; las de
      longitud sospechosa van marcadas con «??»
"""

import html
import math
import re
import sys

import lxml.html

LISTADO_HTML = re.compile(r'^\s*//:\s*\w+:(\S+)')
LISTADO_XML = re.compile(r'^//:\s*V\d\w*:(\S+)', re.M)
NOTA = re.compile(r'\[(\d+)\]')
ETIQUETA = re.compile(r'<(/?)([\w:]+)[^>]*?(/?)>')
EXPANSION = 1.12                 # el castellano ocupa algo más que el inglés


def limpia(texto):
    "texto de un bloque en una línea, apto para un comentario XML"
    texto = ' '.join(texto.replace('\xa0', ' ').split())
    while '--' in texto:
        texto = texto.replace('--', '- -')
    return texto.rstrip('-')


# --- original -------------------------------------------------------------

def bloques_originales(path):
    """[(tipo, texto)] del HTML: 'h' título, 'p' párrafo, 'l' listado, 'c'
    código suelto; y {número: texto} de las notas al pie."""
    raiz = lxml.html.parse(path).getroot()
    bloques, notas, dentro = [], {}, False
    for el in raiz.iter():
        tag = el.tag if isinstance(el.tag, str) else ''
        tag = tag.lower()
        if tag == 'h1':
            texto = limpia(el.text_content())
            if not texto:
                continue                           # separadores vacíos
            dentro = True
            bloques.append(('h', re.sub(r'^[\w]+:\s*', '', texto)))
        elif not dentro and tag != 'p':
            continue
        elif tag in ('h2', 'h3', 'h4'):
            bloques.append(('h', limpia(el.text_content())))
        elif tag == 'pre':
            codigo = el.text_content()
            m = LISTADO_HTML.match(codigo)
            bloques.append(('l', m.group(1)) if m else ('c', codigo.strip()))
        elif tag == 'li' and dentro:
            bloques.append(('p', limpia(el.text_content())))
        elif tag == 'p':
            ancla = el.xpath('.//a[starts-with(@name, "fn") and not(starts-with(@name, "fnB"))]')
            if ancla:
                texto = limpia(el.text_content())
                m = NOTA.match(texto)
                if m:
                    notas[int(m.group(1))] = texto
                continue
            if not dentro or el.xpath('ancestor::li'):
                continue
            texto = limpia(el.text_content())
            if texto:
                bloques.append(('p', texto))
    return bloques, notas


# --- traducción -----------------------------------------------------------

def tapa(m):
    "sustituye un trozo por espacios sin mover las posiciones"
    return re.sub(r'[^\n]', ' ', m.group(0))


def bloques_traducidos(texto):
    """[(tipo, texto, posición, comentado)] de la traducción, en orden."""
    limpio = re.sub(r'<!--.*?-->', tapa, texto, flags=re.S)
    codigo = [(m.start(), m.end()) for m in
              re.finditer(r'<(programlisting|screen)\b.*?</\1>', limpio, re.S)]
    for a, b in codigo:
        limpio = limpio[:a] + ' ' * (b - a) + limpio[b:]
    bloques = []
    for a, b in codigo:
        if texto.startswith('<programlisting', a):
            bloques.append(('c', texto[a:b], a, True))
    for m in LISTADO_XML.finditer(limpio):
        bloques.append(('l', m.group(1), m.start(), True))

    pila = []
    for m in ETIQUETA.finditer(limpio):
        cierra, nombre, sola = m.group(1), m.group(2), m.group(3)
        if sola:
            continue
        if cierra:
            while pila and pila.pop()[0] != nombre:
                pass
            continue
        padres = [p for p, _ in pila]
        pila.append((nombre, m.start()))
        if 'footnote' in padres:
            continue
        if nombre == 'title' and padres and padres[-1] in (
                'chapter', 'preface', 'appendix', 'sect1', 'sect2', 'sect3', 'sect4'):
            fin = limpio.index('</title>', m.end())
            bloques.append(('h', limpio[m.end():fin], m.start(), comentado(texto, m.start())))
        elif nombre == 'para' and 'entry' not in padres:
            fin = fin_para(limpio, m.start())
            cuerpo = re.sub(r'<footnote\b.*?</footnote>', '', limpio[m.end():fin], flags=re.S)
            cuerpo = html.unescape(re.sub(r'<[^>]+>', '', cuerpo))
            ya = comentado(texto, m.start())
            if not ya and padres[-1:] == ['listitem']:
                # a veces el original de toda la lista va en un solo
                # comentario delante de la lista
                lista = [pos for nom, pos in pila[:-1]
                         if nom in ('itemizedlist', 'orderedlist', 'variablelist')]
                if lista:
                    ya = comentado(texto, lista[-1])
            if cuerpo.strip():
                bloques.append(('p', ' '.join(cuerpo.split()), m.start(), ya))
    bloques.sort(key=lambda b: b[2])
    return bloques


def fin_para(texto, ini):
    nivel = 0
    for m in re.finditer(r'<(/?)para\b[^>]*?(/?)>', texto[ini:]):
        if m.group(2):
            continue
        nivel += -1 if m.group(1) else 1
        if nivel == 0:
            return ini + m.start()
    return len(texto)


def comentado(texto, pos):
    """Texto del comentario que hay justo antes (o antes del contenedor de la
    lista), o '' si no lo hay."""
    antes = texto[:pos].rstrip()
    for envoltorio in ('<listitem>', '<highlights>'):
        if antes.endswith(envoltorio):
            antes = antes[:-len(envoltorio)].rstrip()
    if not antes.endswith('-->'):
        return ''
    return ' '.join(antes[antes.rindex('<!--') + 4:-3].split()) or ' '


# --- alineamiento ---------------------------------------------------------

def parecido(len_en, len_es):
    "0..1 según lo que se parecen las longitudes"
    if not len_en or not len_es:
        return 0
    return max(0.0, 1 - abs(math.log(len_es / (EXPANSION * len_en))))


def alinea(en, es):
    """Programación dinámica. Devuelve [(índices_en, índices_es)].

    Juntar dos párrafos (2:1 o 1:2) solo compensa si las longitudes encajan
    mejor que emparejando uno a uno y dejando el otro suelto.
    """
    n, m = len(en), len(es)
    MENOS = -1e9
    mejor = [[MENOS] * (m + 1) for _ in range(n + 1)]
    paso = [[None] * (m + 1) for _ in range(n + 1)]
    mejor[0][0] = 0
    salto = {'p': -0.6, 'h': -1.5, 'l': -4, 'c': -0.3}

    def prueba(i, j, di, dj, valor):
        if valor > mejor[i + di][j + dj]:
            mejor[i + di][j + dj] = valor
            paso[i + di][j + dj] = (di, dj)

    for i in range(n + 1):
        for j in range(m + 1):
            v = mejor[i][j]
            if v == MENOS:
                continue
            if i < n:
                prueba(i, j, 1, 0, v + salto[en[i][0]])
            if j < m:
                prueba(i, j, 0, 1, v + salto[es[j][0]])
            if i < n and j < m and en[i][0] == es[j][0]:
                tipo = en[i][0]
                if tipo == 'l':
                    if en[i][1] == es[j][1]:
                        prueba(i, j, 1, 1, v + 10)
                elif tipo == 'c':
                    prueba(i, j, 1, 1, v + 1)
                else:
                    base = 2 if tipo == 'h' else 1 + parecido(len(en[i][1]), len(es[j][1]))
                    # el comentario que ya tiene la traducción es un ancla segura
                    if es[j][3] and mismo_texto(en[i][1], es[j][3]):
                        base += 10
                    prueba(i, j, 1, 1, v + base)
            if tipo_p(en, i, 2) and tipo_p(es, j, 1):
                largo = len(en[i][1]) + len(en[i + 1][1])
                prueba(i, j, 2, 1, v + 0.4 + parecido(largo, len(es[j][1])))
            if tipo_p(en, i, 1) and tipo_p(es, j, 2):
                largo = len(es[j][1]) + len(es[j + 1][1])
                prueba(i, j, 1, 2, v + 0.4 + parecido(len(en[i][1]), largo))

    pares, i, j = [], n, m
    while i or j:
        di, dj = paso[i][j]
        pares.append((list(range(i - di, i)), list(range(j - dj, j))))
        i, j = i - di, j - dj
    return pares[::-1]


def mismo_texto(a, b):
    "¿empiezan igual, sin contar espacios, comillas ni signos?"
    simple = lambda s: re.sub(r'\W+', '', s.lower())[:60]
    return simple(a) == simple(b)


def tipo_p(bloques, i, cuantos):
    return i + cuantos <= len(bloques) and all(b[0] == 'p' for b in bloques[i:i + cuantos])


# --- escritura ------------------------------------------------------------

def comentario(texto, pos, lineas):
    "texto del comentario para insertar en pos, con la sangría de la línea"
    ini = texto.rfind('\n', 0, pos) + 1
    sangria = texto[ini:pos]
    if sangria.strip():
        sangria = re.match(r'\s*', texto[ini:]).group(0) + '  '
        inicio = '\n' + sangria
    else:
        inicio = ''
    if len(lineas) == 1 and len(lineas[0]) < 70 and '\n' not in lineas[0]:
        return f'{inicio}<!-- {lineas[0]} -->\n{sangria}'
    cuerpo = f'\n\n'.join(sangria + l for l in lineas)
    return f'{inicio}<!--\n{cuerpo}\n{sangria}-->\n{sangria}'


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('-')]
    simula, detalle = '-n' in sys.argv, '-v' in sys.argv
    if len(args) != 2:
        sys.exit(__doc__)
    original, destino = args
    texto = open(destino, encoding='utf-8').read()

    en, notas = bloques_originales(original)
    es = bloques_traducidos(texto)
    pares = alinea(en, es)

    # texto de todos los comentarios, para no repetir un original que ya está
    # en otro sitio (p. ej., toda una lista en un comentario anterior)
    simple = lambda s: re.sub(r'\W+', '', s.lower())
    ya_comentado = simple(' '.join(re.findall(r'<!--(.*?)-->', texto, re.S)))

    inserciones, sueltos_en, sueltos_es = [], [], []
    for ie, js in pares:
        if not js:
            sueltos_en += [en[i] for i in ie if en[i][0] in 'ph']
            continue
        if not ie:
            sueltos_es += [es[j] for j in js if es[j][0] in 'ph' and not es[j][3]]
            continue
        j = js[0]
        tipo, _, pos, ya = es[j]
        if tipo not in 'ph' or ya:
            continue
        lineas = [en[i][1] for i in ie]
        clave = simple(lineas[0])[:50]
        if tipo == 'p' and len(clave) >= 30 and clave in ya_comentado:
            continue
        for i in ie:
            for n in NOTA.findall(en[i][1]):
                if int(n) in notas:
                    lineas.append(notas[int(n)])
        inserciones.append((pos, lineas))
        if detalle:
            largo_en = sum(len(en[i][1]) for i in ie)
            largo_es = sum(len(es[k][1]) for k in js)
            marca = '??' if parecido(largo_en, largo_es) < 0.45 else '  '
            linea = texto.count('\n', 0, pos) + 1
            print(f'{marca} {destino}:{linea} {len(ie)}:{len(js)}')
            print(f'     EN: {" / ".join(en[i][1] for i in ie)[:150]}')
            print(f'     ES: {es[j][1][:150]}')

    for pos, lineas in sorted(inserciones, reverse=True):
        texto = texto[:pos] + comentario(texto, pos, lineas) + texto[pos:]

    for b in sueltos_en:
        print(f'SIN PAREJA (original): {b[1][:120]}')
    for b in sueltos_es:
        print(f'SIN PAREJA (traducción): {destino}:{texto.count(chr(10), 0, b[2]) + 1}: {b[1][:100]}')
    if not simula:
        open(destino, 'w', encoding='utf-8').write(texto)
    print(f'{destino}: {len(inserciones)} comentarios'
          f'{"  (simulado)" if simula else ""}', file=sys.stderr)


if __name__ == '__main__':
    main()
