#!/usr/bin/env python
'''
Transforma ficheros de texto plano en DB listo para traducir. El original debe tener los títulos de las secciones delimitados con:

:SECT:1: Título de la sección

palabrería bla bla bla

:SECT:2: Título de subsección

'''

import sys

OUTPAR = 0
INPAR = 1


def indent(cad, offset=None):
    if offset == None: offset = level+1
    sp = ' ' * 2 * offset
    return '%s%s' % (sp, cad)
    
def print_par(fd, par):
    global level
    put_para = True
    fd.write('\n')
    par = par.strip('\n')
    if par.count('\n') == 0:
        par = par.strip()
        if par.startswith(':SECT:'):
            newlevel = int(par[6])
           
            # cerrar las secciones si newlevel > level
            dif = newlevel - level
            if dif <= 0:
                for i in range(abs(dif)+1):
                    fd.write(indent('</sect%d>\n' % (level - i), level-i))

            
            level = newlevel
            par = par[7:].strip()
            fd.write(indent('<sect%d>\n' % level, level))
            fd.write(indent('<!-- %s -->\n' % par))
            fd.write(indent('<title> </title>\n'))
            put_para = False
        else:
            fd.write(indent('<!-- %s -->\n' % par))
    else:
        fd.write(indent('<!--\n%s\n' % par))
        fd.write(indent('-->\n'))

    if put_para:
        fd.write(indent('<para>\n\n'))
        fd.write(indent('</para>\n'))


src = open(sys.argv[1])
dst = open('salida', 'w')

status = OUTPAR
level = 0

par = ''
for line in src:
    line = line.strip()
    if line and line[0] == '<': continue
        
    if status == INPAR:
        if not line:
            status = OUTPAR
            if par: print_par(dst, par)
            continue

        par += indent(line + '\n')


    if status == OUTPAR:
        if line:
            status = INPAR
            par = indent(line + '\n')
            continue

    

src.close()
dst.close()
    
