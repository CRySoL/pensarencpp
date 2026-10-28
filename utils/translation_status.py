#!/usr/bin/python3
"""Estado de la traducción de los fuentes DocBook.

Cada comentario con el original en inglés cuenta como traducido si el
elemento que le sigue contiene texto en castellano, y como pendiente si está
vacío o sigue en inglés. Las cifras son palabras del original.

Uso: translation_status.py [-s] [-v] [-r] FICHERO.xml...
  -s  desglose por sect1
  -v  línea de cada bloque pendiente
  -r  línea de cada traducción mucho más corta que su original: suele ser
      un párrafo a medias o con un trozo del original pegado
"""

import re
import sys
from lxml import etree

BLOCKS = {'para', 'simpara', 'title', 'term', 'entry', 'member', 'caption',
          'remark', 'subtitle', 'titleabbrev', 'attribution'}

# su texto no cuenta para decidir el idioma
CODE = {'programlisting', 'screen', 'literallayout', 'synopsis', 'literal',
        'code', 'function', 'classname', 'varname', 'filename', 'command',
        'type', 'kw', 'oper', 'token', 'constant', 'methodname', 'parameter',
        'envar', 'option', 'userinput', 'computeroutput', 'symbol',
        'structname', 'returnvalue', 'markup', 'ulink', 'email'}

EN = set('''the of and to is in that you it for are with this be as can an
    when which by on or your from have will if one they there these what
    would how its was but all into than only also because however each other
    such has use used using'''.split())

ES = set('''el la de que y en los las un una es se por con para del al lo
    como su sus más pero este esta estos estas cuando puede también sólo
    solo donde cual ya hay porque usted ser son está'''.split())

WORD = re.compile(r"[a-záéíóúñü']+", re.I)


def name(node):
    return etree.QName(node).localname if isinstance(node.tag, str) else None


def text_of(block):
    "texto natural del bloque, sin comentarios, código ni bloques anidados"
    out = [block.text or '']
    for child in block:
        if isinstance(child.tag, str) and name(child) not in CODE | BLOCKS:
            out.append(text_of(child))
        out.append(child.tail or '')
    return ' '.join(''.join(out).split())


def language(text, strict=False):
    "con strict, hacen falta al menos dos palabras de referencia"
    words = [w.lower() for w in WORD.findall(text)]
    en = sum(w in EN for w in words)
    es = sum(w in ES for w in words)
    if not words:
        return 'empty'
    if en + es < 2:
        if strict:
            return 'short'
        return 'es' if es else 'en' if en else 'short'
    if en > 2 * es:
        return 'en'
    if es > 2 * en:
        return 'es'
    return 'mixed'


def is_translated(element):
    blocks = [b for b in element.iter() if name(b) in BLOCKS]
    if not blocks:
        return None
    return any(language(text_of(b)) not in ('empty', 'en') for b in blocks)


def next_element(node):
    node = node.getnext()
    while node is not None and not isinstance(node.tag, str):
        node = node.getnext()
    return node


def measure(root):
    "devuelve (traducido, pendiente, [líneas pendientes])"
    done, pending, lines = 0, 0, []
    for comment in root.iter(etree.Comment):
        if not comment.text or language(comment.text, strict=True) != 'en':
            continue
        target = next_element(comment)
        if target is None:
            continue
        words = len(comment.text.split())
        state = is_translated(target)
        if state:
            done += words
        elif state is False:
            pending += words
            lines.append(target.sourceline)
    return done, pending, lines


def too_short(root, ratio=0.6, minimum=15):
    "líneas de las traducciones con menos de ratio veces las palabras del original"
    lines = []
    for comment in root.iter(etree.Comment):
        if not comment.text or language(comment.text, strict=True) != 'en':
            continue
        target = next_element(comment)
        if target is None or not is_translated(target):
            continue
        original = len(comment.text.split())
        blocks = [b for b in target.iter() if name(b) in BLOCKS]
        translated = sum(len(text_of(b).split()) for b in blocks)
        if original >= minimum and translated < ratio * original:
            lines.append(target.sourceline)
    return lines


def section_title(sect):
    title = sect.find('title')
    if title is None:
        return ''
    text = text_of(title)
    if not text:
        comment = title.getprevious()
        if comment is not None and name(comment) is None and comment.text:
            text = '[EN] ' + ' '.join(comment.text.split()).lstrip(': ')
    return text[:60]


def percent(done, pending):
    return 100 * done // (done + pending) if done + pending else 100


def main():
    args = sys.argv[1:]
    sections = '-s' in args
    verbose = '-v' in args
    review = '-r' in args
    files = [a for a in args if not a.startswith('-')]
    if not files:
        sys.exit(__doc__)

    parser = etree.XMLParser(load_dtd=False, no_network=True,
                             resolve_entities=False, recover=True)
    width = max(len(f) for f in files)
    total_done = total_pending = 0

    print(f"{'fichero':{width}}  {'traducido':>9}  {'pendiente':>9}  hecho")
    for path in files:
        root = etree.parse(path, parser).getroot()
        done, pending, lines = measure(root)
        total_done += done
        total_pending += pending
        print(f"{path:{width}}  {done:9}  {pending:9}  "
              f"{percent(done, pending):4}%")

        if sections:
            for sect in root.iter('sect1'):
                d, p, _ = measure(sect)
                mark = 'ok' if not p else '--' if not d else '~~'
                print(f"    {mark} {d:7} {p:7}  {section_title(sect)}")

        if verbose and lines:
            print('    pendiente en líneas:', ' '.join(map(str, lines)))

        if review:
            short = too_short(root)
            if short:
                print('    revisar en líneas:', ' '.join(map(str, short)))

    if len(files) > 1:
        print(f"{'TOTAL':{width}}  {total_done:9}  {total_pending:9}  "
              f"{percent(total_done, total_pending):4}%")


if __name__ == '__main__':
    main()
