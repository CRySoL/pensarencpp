#!/usr/bin/env python3
"""Comprueba que la traducción de los listados solo ha tocado comentarios.

Uso: check_code_comments.py [-l N] ORIGINAL TRADUCIDO [FICHERO...]
     check_code_comments.py --xml [-l N] FICHERO.xml...

Con dos directorios, compara cada fichero .cpp o .h de TRADUCIDO (o solo
los FICHEROs indicados, con su ruta relativa) con el del mismo nombre en
ORIGINAL. Con --xml, compara los <programlisting> de cada capítulo con los
de la última versión confirmada en git (HEAD).

Por cada listado comprueba que:
  - el código sin comentarios es idéntico, símbolo a símbolo (los literales
    de cadena incluidos);
  - las cinco primeras líneas (la marca «//: Cxx:Fichero» y la cabecera de
    copyright que quita patch_sources.py) no cambian;
  - las directivas «//{...}», las marcas «///:~» y el código comentado de
    las líneas «//!» siguen igual;
  - ninguna línea pasa de N caracteres (60 por defecto) si no pasaba ya en
    el original.

Sale con código 1 si encuentra algún problema.
"""
import os
import re
import subprocess
import sys

SIMBOLO = re.compile(r'''
    (?P<coment>//(?:[^\n\\]|\\.)*|/\*.*?\*/)
  | (?P<cadena>"(?:[^"\\\n]|\\.)*"|'(?:[^'\\\n]|\\.)*')
  | (?P<espacio>\s+)
  | (?P<otro>\w+|.)
''', re.S | re.X)


def codigo(texto):
    """Símbolos del código, sin comentarios ni espacios."""
    return [m.group(0) for m in SIMBOLO.finditer(texto)
            if m.lastgroup in ('cadena', 'otro')]


def protegidas(texto):
    """Líneas que no se traducen: directivas, marcas y código comentado."""
    salida = []
    for linea in texto.split('\n'):
        s = linea.strip()
        if s.startswith('//{') or s.startswith('///:~'):
            salida.append(s)
        elif s.startswith('//!'):
            # el código comentado, sin el comentario que pueda llevar detrás
            salida.append(re.sub(r'\s*//(?!!).*$', '', s[3:]).rstrip())
    return salida


def compara(nombre, viejo, nuevo, limite):
    errores = []
    viejo = viejo.replace('\r\n', '\n')
    nuevo = nuevo.replace('\r\n', '\n')
    if codigo(viejo) != codigo(nuevo):
        a, b = codigo(viejo), codigo(nuevo)
        i = next((k for k in range(min(len(a), len(b))) if a[k] != b[k]),
                 min(len(a), len(b)))
        errores.append('el código cambia cerca de: '
                       + ' '.join(a[max(0, i - 5):i + 5]) + '  ->  '
                       + ' '.join(b[max(0, i - 5):i + 5]))
    if viejo.split('\n')[:5] != nuevo.split('\n')[:5] and \
       viejo.startswith('//:'):
        errores.append('cambian las cinco primeras líneas')
    if protegidas(viejo) != protegidas(nuevo):
        errores.append('cambian las directivas //{...}, ///:~ o el código '
                       'de las líneas //!')
    largo_viejo = max((len(l) for l in viejo.split('\n')), default=0)
    for n, linea in enumerate(nuevo.split('\n'), 1):
        if len(linea) > limite and len(linea) > largo_viejo:
            errores.append(f'línea {n} de {len(linea)} caracteres')
    for e in errores:
        print(f'{nombre}: {e}')
    return not errores


def listados_xml(texto):
    return [m.group(1) for m in re.finditer(
        r'<programlisting[^>]*>(.*?)</programlisting>', texto, re.S)]


def main():
    args = sys.argv[1:]
    limite = 60
    if '-l' in args:
        i = args.index('-l')
        limite = int(args[i + 1])
        del args[i:i + 2]
    ok = True
    if args and args[0] == '--xml':
        for f in args[1:]:
            viejo = subprocess.run(['git', 'show', f'HEAD:{f}'],
                                   capture_output=True, text=True).stdout
            nuevo = open(f, encoding='utf-8').read()
            a, b = listados_xml(viejo), listados_xml(nuevo)
            if len(a) != len(b):
                print(f'{f}: {len(a)} -> {len(b)} programlisting')
                ok = False
                continue
            for k, (x, y) in enumerate(zip(a, b), 1):
                if x != y:
                    ok &= compara(f'{f} (listado {k})', x, y, limite)
    elif len(args) >= 2:
        orig, trad = args[0], args[1]
        ficheros = args[2:] or sorted(
            os.path.relpath(os.path.join(r, n), trad)
            for r, _, ns in os.walk(trad) for n in ns
            if n.endswith(('.cpp', '.h')))
        for rel in ficheros:
            viejo = open(os.path.join(orig, rel), encoding='latin-1').read()
            nuevo = open(os.path.join(trad, rel), encoding='utf-8').read()
            ok &= compara(rel, viejo, nuevo, limite)
    else:
        sys.exit(__doc__)
    sys.exit(0 if ok else 1)


if __name__ == '__main__':
    main()
