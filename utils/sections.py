#!/usr/bin/python3
"""Restaura secciones cuyo encabezado quedó pegado a un comentario.

Uso: sections.py FICHERO REGLAS.py
REGLAS.py define GROUPS = [(nivel, [(fragmento, 'after'|'before', encabezado, título), ...]), ...]

- 'after': la sección empieza después del bloque que sigue al comentario
  (el encabezado estaba al final del comentario).
- 'before': la sección empieza antes del comentario (el encabezado estaba
  al principio).
Cada sección de un grupo se cierra al abrir la siguiente; la última, antes
del primer <sectN> o </sectN-1> que aparezca después.
"""
import re
import sys

path, rules = sys.argv[1], sys.argv[2]
ns = {}
exec(open(rules, encoding='utf-8').read(), ns)
text = open(path, encoding='utf-8').read()
norm = lambda s: ' '.join(s.split())


def block_end(pos):
    "final del <para>/<title> que empieza en pos, contando anidados"
    m = re.compile(r'\s*<(para|title)>').match(text, pos)
    assert m, 'no hay bloque detrás del comentario'
    tag, depth = m.group(1), 0
    for t in re.finditer(rf'<(/?){tag}>', text[m.start(1) - 1:]):
        depth += -1 if t.group(1) else 1
        if depth == 0:
            return m.start(1) - 1 + t.end()


for level, items in ns['GROUPS']:
    ind = '    ' if level == 2 else '      '
    last = None
    for i, (snippet, where, heading, title) in enumerate(items):
        hits = [m for m in re.finditer(r'<!--(.*?)-->', text, re.S) if norm(snippet) in norm(m.group(1))]
        assert len(hits) == 1, f'{len(hits)} comentarios: {snippet}'
        if where == 'after':
            pos = block_end(hits[0].end())
        else:
            pos = text.rindex('\n', 0, hits[0].start())
        opening = (f'\n\n{ind}<sect{level}>\n{ind}<!-- {heading} -->\n'
                   f'{ind}<title>{title}</title>')
        closing = f'\n\n{ind}</sect{level}>' if i else ''
        text = text[:pos] + closing + opening + text[pos:]
        last = pos + len(closing) + len(opening)
    ends = [m.start() for m in re.finditer(rf'\n\s*(<sect{level}>|</sect{level - 1}>)', text[last:])]
    stop = last + ends[0]
    text = text[:stop] + f'\n\n{ind}</sect{level}>' + text[stop:]

open(path, 'w', encoding='utf-8').write(text)
print(f'{path}: {sum(len(g) for _, g in ns["GROUPS"])} secciones')
