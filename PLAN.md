# Plan para completar la traducción

## Estado (medido el 28/10/2026)

Cifras de `make status` (`utils/translation_status.py`). Para cada
comentario con el original en inglés, el script comprueba si el bloque que le
sigue está traducido. Las cifras son palabras del original.

- **Volumen 1: traducido por completo.** Lo único que queda en inglés se deja
  así a propósito: las condiciones de Eckel, citadas en el Prólogo, y algunas
  referencias bibliográficas.
- **Volumen 2: unas 46.300 palabras traducidas y unas 86.700 pendientes, un
  34 % hecho.**

| Cap.  | Tema                   | Pendiente | Hecho | En `master_Volumen2.xml`                    |
|-------|------------------------|----------:|------:|---------------------------------------------|
| C01   | Excepciones            |     9.210 |   8 % | incluido                                    |
| C02   | Programación defensiva |        61 |  99 % | incluido                                    |
| C03   | Cadenas                |        90 |  98 % | incluido                                    |
| C04   | Iostreams              |     4.410 |  67 % | incluido                                    |
| C05   | Plantillas a fondo     |    14.370 |   0 % | incluido (**sale vacío**)                   |
| C06   | Algoritmos genéricos   |    16.090 |  13 % | incluido (**con el inglés copiado en el texto**) |
| C07   | Contenedores genéricos |    21.380 |   0 % | comentado                                   |
| C08   | RTTI                   |     3.070 |   0 % | comentado                                   |
| C09   | Herencia múltiple      |     4.350 |  20 % | incluido                                    |
| C10   | Patrones de diseño     |     6.430 |  49 % | incluido                                    |
| C11   | Concurrencia           |     5.790 |  62 % | incluido                                    |
| ApenA | Lecturas recomendadas  |     1.420 |   0 % | comentado                                   |
| ApenB | Etc.                   |        25 |   0 % | comentado                                   |

Los capítulos incluidos que tienen párrafos vacíos se publican con huecos: el
PDF lleva C05 entero en blanco. Por eso el plan empieza por terminar lo que ya
está incluido.

## Fase 0: preparación, antes de traducir nada (hecha el 29/10/2026)

1. **Dependencias.** Instalar todo lo que lista [DEPENDS](DEPENDS), en
   especial `docbook-xsl` y `highlight`. Sin `docbook-xsl`, `xsltproc` intenta
   descargar las hojas de estilo de sourceforge y falla.
2. **Seguimiento.** `make status` mide lo pendiente por capítulo.
   `utils/translation_status.py -s FICHERO` lo desglosa por sección y `-v`
   indica la línea de cada bloque pendiente. Pendiente: usarlo para sustituir
   la tabla manual de [STATUS](STATUS), que lleva años desfasada.
3. **Glosario.** Hecho: el glosario de [TRADUCCION](TRADUCCION) recoge los
   términos que fija el volumen 1, marcados con `[V1]`. Cuando una propuesta
   anterior del glosario choca con el uso del volumen 1, manda el volumen 1.
4. **Notas al pie.** Decidido: se escriben como `<footnote>` en el punto de
   la marca `[n]`, igual que en el volumen 1. La convención está en
   [DOCBOOK](DOCBOOK). El texto de las notas se toma del original en HTML.

## Fase 1: cerrar lo casi terminado (hecha el 29/10/2026)

- **C02 y C03:** restos sueltos. Lo que el script daba por pendiente eran
  sobre todo fragmentos de código metidos en `<para>`; ahora van en
  `<programlisting>`. El ejercicio 5 de C03 se queda en inglés a propósito:
  son cadenas de código y la frase que debe producir el programa.
- **C04:** el resto de «Manipuladores», y además «Iostream examples»,
  «Internationalization», «Summary» y «Exercises».
- En los tres capítulos se han incorporado las notas al pie y se ha
  normalizado la terminología del texto ya traducido según el glosario
  (sobre todo «stream», que pasa a «flujo»).

## Fase 2: completar los capítulos a medias (hecha el 29/10/2026)

- **C11 (hecho el 29/10/2026):** el final de «Finalización de tareas», más
  «Cooperación entre hilos», «Interbloqueo», el resumen y los ejercicios.
  Además: la parte ya traducida tuteaba al lector en las primeras secciones
  y tenía 22 «FIXME» y párrafos a medias; se han rehecho esos párrafos y se
  han restaurado cinco `<sect3>` cuyos títulos estaban pegados al texto.
- **C10 (hecho el 29/10/2026):** el resto de «Factorías», más Builder,
  Observador, «Despachado múltiple», el resumen y los ejercicios. Además:
  14 «FIXME», un párrafo a medias, 55 `<kw>` aplicados a nombres de clase,
  funciones o palabras normales, y dos encabezados restaurados («Destructor
  operation» y «The inner class idiom»).
- **C09 (hecho el 29/10/2026):** desde «Herencia de implementación» hasta el
  final, con sus ocho figuras redibujadas en SVG (`images/V2_13.svg` a
  `V2_20.svg`) a partir de las GIF del original.
- **C01 (hecho el 29/10/2026):** desde «Capturar una excepción» hasta el
  final. Además: los párrafos ya traducidos pasan a la terminología del
  glosario («gestión de excepciones», «palabra reservada», «librería») y se
  restauran 18 encabezados que estaban pegados al texto.

## Fase 3: capítulos sin empezar (hecha el 29/10/2026)

- **C08 (RTTI) (hecho el 29/10/2026):** traducido entero, con sus tres
  notas y la figura redibujada en SVG (`images/V2_12.svg`). Ya está incluido
  en el maestro. Las dos salidas de programa pasan de `<programlisting>` a
  `<screen>`.
- **C05 (Plantillas) (hecho el 29/10/2026):** traducido entero, con sus 35
  notas y la fórmula de Fibonacci redibujada en SVG (`images/V2_11.svg`).
  Se restauran tres `sect3` cuyos encabezados estaban pegados al texto o
  convertidos en párrafo, y los términos de plantillas pasan al glosario.
- **C06 (Algoritmos) (hecho el 29/10/2026):** traducido el inglés que estaba
  copiado en los `<para>` y revisada la parte que ya estaba traducida
  («functor» pasa a «objeto función», erratas, notas). Además: la tabla de
  objetos función estándar pasa a `<informaltable>`, los prototipos y los
  datos de los ejercicios que estaban troceados en comentarios van en
  `<programlisting>` o `<screen>`, se restauran dos `sect3` y se recupera
  el primer párrafo de «Eliminación de elementos», que faltaba.
- **C07 (Contenedores) (hecho el 29/10/2026):** traducido entero, con sus
  18 notas, y ya incluido en el maestro. La tabla de categorías de
  contenedores, que era un «FIXME», pasa a `<informaltable>`, y se quitan del
  final del capítulo los cinco párrafos de la introducción de la tercera
  parte, que ya están en el `<partintro>` del maestro.

## Fase 4: apéndices y cierre (hecha el 29/10/2026)

- **ApenA y ApenB:** traducidos e incluidos en el maestro, dentro de una
  `<part>` «Apéndices» (si no, dblatex los sube a nivel de parte y
  numera mal sus secciones). En ApenA los títulos de los libros se quedan en
  inglés.
- **Figuras del volumen 2:** hechas. Todas están en SVG
  (`images/V2_07.svg` a `V2_21.svg`), redibujadas a partir de las GIF del
  original (`images/image0NN.gif`).
- **Repaso final:**
  - ortografía del volumen 2 revisada con aspell mediante
    `utils/spellcheck.py`, que solo mira el texto castellano y admite los
    términos de `utils/spellcheck.words`: unas 290 erratas corregidas,
    sobre todo tildes y letras cambiadas en los capítulos traducidos hace
    años;
  - la sección del volumen 2 de [README.rst](README.rst) ya dice que la
    traducción está terminada y pendiente de revisión;
  - [STATUS](STATUS) actualizado, con una nota que remite a `make status`.

- **Revisión de estilo:** hecha en todo lo que se tradujo hace años
  (introducción, C02, C03, la primera parte de C04, la primera mitad de C10,
  la parte antigua de C11 y los restos de C01 y C09). Los párrafos se han
  retraducido con el estilo del volumen 1 y el glosario; de paso:
  - código y salidas que estaban en párrafos pasan a `programlisting` y
    `screen`, las tablas escritas como párrafos a `informaltable` y las
    listas numeradas a mano a `orderedlist`;
  - se han recuperado notas al pie y frases que faltaban, y corregido
    errores de sentido (en C11, «even» se había traducido como «constante»);
  - `utils/restore_original.py` ha restaurado la tipografía del original
    (apóstrofos, comillas, rayas) en los comentarios en inglés que la habían
    perdido («youre», «you?ll»), en C01, C03, C09, C10 y C11;
  - el glosario fija ahora también «despachado múltiple/doble».

## Segunda pasada de estilo del volumen 2 (en curso)

Lo que tradujo Claude desde cero se cotejó con el original al traducirlo y
pasó el corrector ortográfico, pero no se ha releído para pulir el estilo.
Falta hacerlo, con el mismo criterio que la revisión anterior y un commit
por capítulo:

- capítulos enteros: C05, C06, C07, C08, ApenA y ApenB;
- partes de capítulos: casi todo C01; C04 desde el final de «Manipuladores
  con argumentos»; C09 desde «Herencia de implementación»; C10 desde
  «Constructores virtuales»; C11 desde «Comprobación de una interrupción».

C02, C03 y la introducción ya se retradujeron enteros en la revisión de
estilo, así que no entran.

Después de esta pasada, lo que queda del volumen 2 es la revisión humana de
David Villa.

## Cómo se trabaja cada sección

Cada unidad de trabajo es un `sect1`, o un `sect2` si la sección pasa de
4.000 palabras. Salen unas 35 unidades.

1. **Traducir:** rellenar el bloque vacío que sigue a cada comentario en
   inglés. Los títulos también cuentan: en C05, C07 y C08 aparecen como
   `<title> </title>`. **El comentario no se borra**, como pide el README.
   `utils/fill_translation.py` rellena los huecos a partir de un fichero de
   reglas (fragmento del comentario y traducción) y no escribe nada si alguna
   regla no encaja. Con el tipo `'replace'` rehace un párrafo ya traducido.
   Antes de dar un capítulo por cerrado, `utils/translation_status.py -r`
   señala las traducciones a medias, y conviene buscar los «FIXME» y el
   tuteo que hayan quedado de traducciones anteriores.
2. **Normas:** seguir [TRADUCCION](TRADUCCION) y `misc/guiaestilo.html`:
   - nada de gerundios en los títulos y la menor pasiva posible;
   - dirigirse al lector en tercera persona del singular, sin escribir
     «usted» salvo que haga falta para evitar ambigüedad;
   - no traducir el código ni los identificadores;
   - usar `<kw>`, `<oper>`, `<code>` y `<classname>` como indica
     [DOCBOOK](DOCBOOK).
3. **Listados:** respetar las marcas `//: V2Cxx:Fichero.cpp`, con una línea en
   blanco encima y otra debajo. `fix_includes.py` se encarga del resto. Los
   fragmentos de código o de salida que estén metidos en un `<para>` o
   aplanados dentro de un comentario van en `<programlisting>` o `<screen>`,
   con el formato del original.
4. **Notas al pie:** sustituir cada marca `[n]` del texto traducido por su
   `<footnote>`, según [DOCBOOK](DOCBOOK). `utils/footnotes.py -o` lista las
   notas que cita el original de un capítulo, con su texto; sin `-o`, las
   marcas que aún quedan en la traducción.
5. **Resto del capítulo:** al cerrar un capítulo, aplicar el glosario también
   al texto que ya estaba traducido (sin reescribirlo), y pasar
   `utils/unwrap.py` por el fichero para dejar en una sola línea cada párrafo,
   tanto de la traducción como del original en los comentarios.
6. **Verificar:** ejecutar `make Volumen2.xml validate`, comprobar con
   `utils/translation_status.py -s -v FICHERO` que la sección no deja bloques
   pendientes y, de vez en cuando, generar `make vol2 Volumen2.pdf` para ver
   el resultado.
7. **Revisión:** revisar el diff y hacer el commit, por sección o por
   capítulo.

## Fuera de este plan

Original comentado del volumen 1 (hecho el 29/10/2026): V1-C15, V1-C16 y
V1-ApenC no tenían el original en inglés, y a otros capítulos les faltaba
en algunos títulos y párrafos. `utils/add_original.py` lo añade a partir
del HTML del MIT (https://web.mit.edu/merolish/ticpp/).

La tarea pendiente del volumen 1 que figura en [TODO](TODO): traducir los
comentarios de los listados. Es una tarea de revisión, no de traducción. (El
cambio de «template» por «plantilla» ya está hecho en la prosa del volumen 1;
solo queda la aclaración «(o templates)» de la primera mención en C16.)

## Revisión de estilo del volumen 1 (pendiente)

La traducción del volumen 1 no se ha releído con el criterio que se aplicó
al volumen 2: cotejar cada párrafo con el original, retraducir lo poco
natural y aplicar el glosario y `misc/guiaestilo.html`. Se hará capítulo a
capítulo, con un commit por capítulo, y aprovechando para pasar a
`programlisting`, `screen`, `informaltable` y `orderedlist` lo que siga
escrito como párrafos. Se empezará cuando termine la segunda pasada del
volumen 2. Los asuntos de terminología que la bloqueaban ya están resueltos
(sección siguiente).

## Asuntos del volumen 1 (resueltos el 30/10/2026)

Surgieron en la revisión automática del volumen 1:

1. **Agradecimientos del Prólogo.** La sección de
   [V1-Prologo.xml](V1-Prologo.xml) solo decía «Por hacer: LuCAS,
   spanglish@uma.es, docbook-ayuda@es.tldp.org». Claude ha redactado un
   borrador a partir de esas notas y de lo que consta en el repositorio;
   **pendiente de que David Villa lo corrija**.
2. ***Redefining* frente a *overriding*.** Decidido: los dos se traducen
   «redefinir», y donde Eckel los contrasta (C14, «Ocultación de nombres», y
   C15) se añade el término inglés entre paréntesis, como ya estaba. Anotado
   en el glosario; no hace falta cambiar el texto.
3. ***Librarian*.** Decidido: «gestor de librerías», como en C02 y C03.
   Añadido al glosario y retirado «bibliotecario» de «No convencen».
