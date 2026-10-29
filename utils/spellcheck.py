#!/usr/bin/python3
"""Repaso ortográfico de la traducción con aspell (diccionario «es»).

Saca el texto castellano de los ficheros DocBook (párrafos y títulos) y deja
fuera lo que no hay que revisar: los comentarios con el original en inglés,
los listados y las salidas, y los elementos que contienen código,
identificadores o títulos en inglés (<classname>, <function>, <citetitle>,
<foreignphrase>, etc.). Las palabras desconocidas se comparan además con una
lista de palabras admitidas (términos técnicos, nombres propios), una por
línea.

Uso: spellcheck.py [-v] [-p LISTA] FICHERO.xml...
  sin -v  cada palabra desconocida con su número de apariciones
  -v      además, el fichero y la línea de cada aparición
  -p      lista de palabras admitidas (por defecto, utils/spellcheck.words)
"""

import collections
import os
import re
import subprocess
import sys

FUERA = ('programlisting', 'screen', 'literallayout', 'classname', 'function',
         'varname', 'type', 'code', 'literal', 'filename', 'citetitle',
         'foreignphrase', 'kw', 'oper', 'constant', 'ulink', 'email',
         'computeroutput', 'userinput', 'envar', 'command', 'option',
         'parameter', 'replaceable', 'structname', 'methodname', 'author',
         'personname', 'firstname', 'surname', 'imagedata', 'xi:include')
BLOQUE = re.compile(r'<(%s)\b[^>]*?(/>|>.*?</\1>)' % '|'.join(FUERA), re.S)
LISTA = os.path.join(os.path.dirname(__file__), 'spellcheck.words')


def tapa(m):
    "borra un trozo sin cambiar la numeración de líneas"
    return re.sub(r'[^\n]', ' ', m.group(0))


def texto_castellano(texto):
    texto = re.sub(r'<!--.*?-->', tapa, texto, flags=re.S)
    texto = re.sub(r'<!DOCTYPE.*?>', tapa, texto, flags=re.S)
    texto = re.sub(r'^//:.*$', tapa, texto, flags=re.M)
    texto = BLOQUE.sub(tapa, texto)
    texto = re.sub(r'<[^>]+>', tapa, texto)
    texto = re.sub(r'&\w+;', ' ', texto)
    return re.sub(r'https?://\S+|www\.\S+', tapa, texto)


def desconocidas(texto):
    res = subprocess.run(['aspell', 'list', '-d', 'es', '--encoding=utf-8'],
                         input=texto, capture_output=True, text=True, check=True)
    return set(res.stdout.split())


def main():
    args = sys.argv[1:]
    detalle = '-v' in args
    lista = LISTA
    if '-p' in args:
        lista = args[args.index('-p') + 1]
        del args[args.index('-p'):args.index('-p') + 2]
    ficheros = [a for a in args if not a.startswith('-')]
    if not ficheros:
        sys.exit(__doc__)
    admitidas = set()
    if os.path.exists(lista):
        admitidas = {l.strip() for l in open(lista, encoding='utf-8')
                     if l.strip() and not l.startswith('#')}

    cuenta, sitios = collections.Counter(), collections.defaultdict(list)
    for f in ficheros:
        texto = texto_castellano(open(f, encoding='utf-8').read())
        malas = desconocidas(texto) - admitidas
        for n, linea in enumerate(texto.split('\n'), 1):
            for palabra in re.findall(r"[\wáéíóúüñÁÉÍÓÚÜÑ]+", linea):
                if palabra in malas:
                    cuenta[palabra] += 1
                    sitios[palabra].append(f'{f}:{n}')
    for palabra, n in sorted(cuenta.items(), key=lambda x: (-x[1], x[0].lower())):
        print(f'{n:4} {palabra}')
        if detalle:
            print('       ' + ' '.join(sitios[palabra][:8]))


if __name__ == '__main__':
    main()
