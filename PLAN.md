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

## Fase 2: completar los capítulos a medias (unas 25.800 palabras)

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
- **C09:** desde «Herencia de implementación» hasta el final.
- **C01:** desde «Capturar una excepción» hasta el final. Los títulos están
  traducidos, pero los párrafos no.

## Fase 3: capítulos sin empezar (unas 54.900 palabras)

- **C08 (RTTI):** es corto y no depende de otros capítulos. Al terminarlo se
  descomenta en el maestro.
- **C05 (Plantillas):** ocho secciones. Necesita el glosario ya cerrado.
- **C06 (Algoritmos):** aquí el inglés está **copiado dentro de los
  `<para>`**, así que hay que sustituirlo en lugar de añadir texto. «Un
  catálogo de algoritmos STL» tiene 10.300 palabras y conviene dividirlo por
  `sect2`.
- **C07 (Contenedores):** el más largo. Va después de C06 para mantener la
  misma terminología. Al terminarlo se descomenta en el maestro.

## Fase 4: apéndices y cierre (unas 1.400 palabras)

- **ApenA y ApenB:** traducir y descomentar en el maestro. En ApenA los
  títulos de los libros se quedan en inglés.
- **Figura `V2_13` de C09:** el capítulo la referencia dos veces, pero no
  existe en `images/`. Hay que dibujarla en SVG, traduciendo el texto según
  las normas de [TRADUCCION](TRADUCCION).
- **Repaso final:**
  - pasar `aspell-es` a todo el volumen;
  - actualizar la sección del volumen 2 en [README.rst](README.rst), que
    todavía dice «hace poco que hemos empezado»;
  - actualizar [STATUS](STATUS).

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

La tarea pendiente del volumen 1 que figura en [TODO](TODO): traducir los
comentarios de los listados. Es una tarea de revisión, no de traducción. (El
cambio de «template» por «plantilla» ya está hecho en la prosa del volumen 1;
solo queda la aclaración «(o templates)» de la primera mención en C16.)

## Asuntos pendientes del volumen 1

Surgieron en la revisión automática del volumen 1 y requieren una decisión:

1. **Agradecimientos del Prólogo.** La sección «Agradecimientos» de
   [V1-Prologo.xml](V1-Prologo.xml) publica literalmente «Por hacer: LuCAS,
   spanglish@uma.es, docbook-ayuda@es.tldp.org». Falta escribir el texto.
2. ***Redefining* frente a *overriding*.** El glosario traduce *override*
   como «redefinir», pero Eckel distingue *redefining* (función miembro
   ordinaria) de *overriding* (función virtual). Por ahora, la definición de
   C14 («Ocultación de nombres») deja ambos términos en inglés, como ya hacía
   C15, y el resto de C15 y C16 usa «redefinir». Hay que fijar un término para
   cada uno y aplicarlo a C14, C15 y al glosario, que también rige el
   volumen 2.
3. ***Librarian*.** El glosario tiene «bibliotecario» en «No convencen». En
   C02 y C03 se ha usado «gestor de librerías». Si se acepta, hay que
   añadirlo al glosario.
