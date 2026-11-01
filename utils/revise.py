#!/usr/bin/env python3
"""Rehace párrafos ya traducidos conservando sus notas al pie.

Uso: revise.py [-n] FICHERO.xml REGLAS.py

REGLAS.py define FILL = [(fragmento, traducción nueva)], como
fill_translation.py: el fragmento identifica un único comentario con el
original (o el comentario entero, si empieza por «=») y la traducción nueva
sustituye al <para> o <title> que lo sigue. Cada «[NOTA]» de la traducción
nueva se sustituye, en orden, por los <footnote> que ya tiene el bloque, y
el número de marcas tiene que coincidir con el de notas. Después se llama a
fill_translation.py con el tipo 'replace', así que si alguna regla falla no
se escribe nada.

  -n  dice lo que haría sin escribir nada

Se ejecuta desde la raíz del repositorio. Deja junto a REGLAS.py un
REGLAS.py.tmp.py con las reglas ya expandidas.
"""
import os
import re
import subprocess
import sys


def norm(texto):
    return ' '.join(texto.split())


def cuerpo_del_bloque(resto, frag):
    """Contenido del <para> o <title> que abre RESTO, con las notas dentro."""
    m = re.match(r'\s*<(para|title)>', resto)
    assert m, f'sin <para> ni <title> detrás: {frag[:60]}'
    nivel, pos = 0, m.start(1) - 1
    for t in re.finditer(r'<(/?)%s\b[^>]*>' % m.group(1), resto[pos:]):
        nivel += -1 if t.group(1) else 1
        if nivel == 0:  # el cierre que no pertenece a una nota
            return resto[m.end():pos + t.start()]
    raise AssertionError(f'bloque sin cerrar: {frag[:60]}')


def main():
    simula = '-n' in sys.argv
    args = [a for a in sys.argv[1:] if a != '-n']
    if len(args) != 2:
        sys.exit(__doc__)
    fichero, reglas = args
    ns = {}
    exec(open(reglas, encoding='utf-8').read(), ns)
    texto = open(fichero, encoding='utf-8').read()

    salida = []
    for frag, nuevo in ns['FILL']:
        exacto = frag.startswith('=')
        clave = norm(frag[1:] if exacto else frag)
        hits = [m for m in re.finditer(r'<!--(.*?)-->', texto, re.S)
                if (norm(m.group(1)) == clave if exacto
                    else clave in norm(m.group(1)))]
        assert len(hits) == 1, f'{len(hits)} comentarios: {frag[:60]}'
        cuerpo = cuerpo_del_bloque(texto[hits[0].end():], frag)
        notas = re.findall(r'<footnote>.*?</footnote>', cuerpo, re.S)
        huecos = nuevo.count('[NOTA]')
        assert huecos == len(notas), \
            f'{frag[:50]}: {huecos} [NOTA] y {len(notas)} notas'
        for n in notas:
            nuevo = nuevo.replace('[NOTA]', n, 1)
        salida.append((frag, norm(nuevo), 'replace'))

    tmp = reglas + '.tmp.py'
    with open(tmp, 'w', encoding='utf-8') as f:
        f.write('FILL = ' + repr(salida) + '\n')
    herramienta = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                               'fill_translation.py')
    orden = [sys.executable, '-B', herramienta] + \
        (['-n'] if simula else []) + [fichero, tmp]
    sys.exit(subprocess.call(orden))


if __name__ == '__main__':
    main()
