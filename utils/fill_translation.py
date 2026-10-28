#!/usr/bin/python3
"""Rellena los huecos de traducción que siguen a los comentarios con el original.

En los capítulos sin traducir, cada comentario con el texto original va
seguido de un <para> o un <title> vacío. Este script los rellena a partir de
un fichero de reglas en Python:

    FILL = [
        ("fragmento del comentario", "traducción"),
        ("=comentario completo", "traducción"),
        ("struct tm {", "código tal cual", 'code'),
    ]

- El fragmento se busca en los comentarios normalizando espacios y tiene que
  identificar un único comentario que aún tenga el hueco vacío detrás. Si
  empieza por '=', debe coincidir con el comentario entero (útil en tablas,
  donde se repiten cabeceras como "Effect").
- La traducción se escribe en una sola línea, como deja los párrafos
  unwrap.py.
- Con el tipo 'code' o 'screen', el hueco se sustituye por un
  <programlisting> o un <screen> con el texto tal cual (se escapan &, < y >).

Si alguna regla falla, no se escribe nada.

Uso: fill_translation.py [-n] FICHERO.xml REGLAS.py
  -n  dice lo que haría sin escribir nada
"""

import re
import sys

EMPTY = re.compile(r'\s*<(para|title)>\s*</\1>')
COMMENT = re.compile(r'<!--(.*?)-->', re.S)
LISTING = {'code': 'programlisting', 'screen': 'screen'}


def norm(text):
    return ' '.join(text.split())


def escape(text):
    return text.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')


def matcher(snippet):
    if snippet.startswith('='):
        key = norm(snippet[1:])
        return lambda comment: norm(comment) == key
    key = norm(snippet)
    return lambda comment: key in norm(comment)


def fill(text, rules):
    "devuelve (texto, errores)"
    errors = []
    for rule in rules:
        snippet, translation = rule[0], rule[1]
        kind = rule[2] if len(rule) > 2 else None
        match = matcher(snippet)
        # solo cuentan los comentarios que aún tienen el hueco vacío detrás
        hits = [m for m in COMMENT.finditer(text)
                if match(m.group(1)) and EMPTY.match(text, m.end())]
        if len(hits) != 1:
            errors.append(f'{len(hits)} huecos: {snippet[:60]!r}')
            continue

        gap = EMPTY.match(text, hits[0].end())
        lead = gap.group(0)[:gap.group(0).index('<')]
        if kind:
            if gap.group(1) != 'para':
                errors.append(f'el hueco no es un <para>: {snippet[:60]!r}')
                continue
            tag = LISTING[kind]
            indent = lead.rsplit('\n', 1)[-1]
            new = (f'{lead}<{tag}>\n{escape(translation.strip(chr(10)))}\n'
                   f'{indent}</{tag}>')
        else:
            tag = gap.group(1)
            new = f'{lead}<{tag}>{norm(translation)}</{tag}>'
        text = text[:gap.start()] + new + text[gap.end():]
    return text, errors


def main():
    args = sys.argv[1:]
    dry_run = '-n' in args
    args = [a for a in args if a != '-n']
    if len(args) != 2:
        sys.exit(__doc__)
    path, rules_path = args

    rules = {}
    exec(open(rules_path, encoding='utf-8').read(), rules)
    text = open(path, encoding='utf-8').read()
    text, errors = fill(text, rules['FILL'])
    if errors:
        sys.exit('NO APLICADO\n' + '\n'.join(errors))

    if not dry_run:
        open(path, 'w', encoding='utf-8').write(text)
    print(f'{path}: {len(rules["FILL"])} huecos rellenados'
          + ('  (simulado)' if dry_run else ''))


if __name__ == '__main__':
    main()
