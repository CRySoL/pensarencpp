#!/usr/bin/env python3
"""Restaura la tipografía del texto original en los comentarios de un capítulo.

Uso: restore_original.py [-n] [-v] ORIGINAL FICHERO.xml...

En algunos capítulos, el texto original que se conserva comentado perdió
por el camino los apóstrofos, las comillas y las rayas («youre»,
«maintainwhich») o los tiene cambiados por «?». Este programa busca cada
comentario en ORIGINAL (el HTML del libro o un volcado de su texto)
comparando solo letras y dígitos y, si lo encuentra una única vez, sustituye
el texto del comentario por el del original.

  -n  no modifica los ficheros; solo informa
  -v  muestra cada comentario que cambia
"""
import html
import re
import sys
from html.parser import HTMLParser

MINIMO = 25  # letras y dígitos; los comentarios más cortos son ambiguos


class Texto(HTMLParser):
    def __init__(self):
        super().__init__(convert_charrefs=True)
        self.partes = []
        self.saltar = 0

    def handle_starttag(self, tag, attrs):
        if tag in ('style', 'script'):
            self.saltar += 1
        elif tag in ('p', 'br', 'li', 'h1', 'h2', 'h3', 'h4', 'pre', 'div', 'td'):
            self.partes.append('\n')

    def handle_endtag(self, tag):
        if tag in ('style', 'script'):
            self.saltar -= 1

    def handle_data(self, data):
        if not self.saltar:
            self.partes.append(data)


def lee_original(ruta):
    crudo = open(ruta, 'rb').read()
    try:
        datos = crudo.decode('utf-8')
    except UnicodeDecodeError:
        datos = crudo.decode('cp1252', errors='replace')
    if ruta.endswith(('.html', '.htm')):
        p = Texto()
        p.feed(datos)
        datos = ''.join(p.partes)
    return html.unescape(datos).replace('\xa0', ' ')


def indice(texto):
    """Devuelve el texto reducido a letras y dígitos y la posición de cada uno."""
    pos = [i for i, c in enumerate(texto) if c.isalnum()]
    return ''.join(texto[i] for i in pos), pos


ABREN = '“‘«"\''
CIERRAN = '”’»"\''


def ajusta(lado, original, k, paso):
    """Copia del original la puntuación que el comentario tiene en un extremo.

    Recorre LADO (los caracteres del comentario antes de la primera letra o
    después de la última) desde la letra hacia fuera, emparejándolos con los
    del original a partir de K en la dirección PASO. Un «?» o una comilla del
    comentario se aceptan como cualquier signo del original. Al final se
    añaden las comillas pegadas que el comentario hubiera perdido.
    """
    pegadas = CIERRAN if paso > 0 else ABREN
    lado = lado.strip()
    orden = lado if paso > 0 else lado[::-1]
    j = k
    for c in orden:
        while 0 <= j < len(original) and original[j] in pegadas and original[j] != c:
            j += paso
        if not 0 <= j < len(original):
            break
        o = original[j]
        if o == c or (c in '?' + ABREN + CIERRAN and not o.isalnum() and not o.isspace()):
            j += paso
        elif c == ' ' or o == ' ':
            j += paso
        else:
            break
    while 0 <= j < len(original) and original[j] in pegadas:
        j += paso
    return j


def restaura(original, fichero, simula, detalle):
    red, pos = indice(original)
    texto = open(fichero, encoding='utf-8').read()
    cambios = 0

    def cambia(m):
        nonlocal cambios
        cuerpo = m.group(1)
        clave, _ = indice(cuerpo)
        if len(clave) < MINIMO:
            return m.group(0)
        i = red.find(clave)
        if i < 0 or red.find(clave, i + 1) >= 0:
            return m.group(0)
        primera = next(k for k, c in enumerate(cuerpo) if c.isalnum())
        ultima = max(k for k, c in enumerate(cuerpo) if c.isalnum())
        ini = ajusta(cuerpo[:primera], original, pos[i] - 1, -1) + 1
        fin = ajusta(cuerpo[ultima + 1:], original, pos[i + len(clave) - 1] + 1, 1)
        # la puntuación del comentario manda en los extremos
        nuevo = ' '.join(original[ini:fin].split())
        viejo = ' '.join(cuerpo.split())
        if nuevo == viejo or '--' in nuevo:
            return m.group(0)
        cambios += 1
        if detalle:
            print(f'- {viejo[:100]}\n+ {nuevo[:100]}')
        cab = re.match(r'\s*', cuerpo).group(0)
        cola = re.search(r'\s*$', cuerpo).group(0)
        return f'<!--{cab}{nuevo}{cola}-->'

    texto = re.sub(r'<!--(.*?)-->', cambia, texto, flags=re.S)
    if not simula:
        open(fichero, 'w', encoding='utf-8').write(texto)
    print(f'{fichero}: {cambios} comentarios restaurados' + ('  (simulado)' if simula else ''))


def main():
    args = sys.argv[1:]
    simula = '-n' in args
    detalle = '-v' in args
    args = [a for a in args if a not in ('-n', '-v')]
    if len(args) < 2:
        sys.exit(__doc__)
    original = lee_original(args[0])
    for f in args[1:]:
        restaura(original, f, simula, detalle)


if __name__ == '__main__':
    main()
