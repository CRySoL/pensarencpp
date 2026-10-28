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

## Fase 0: preparación, antes de traducir nada

1. **Dependencias.** Instalar todo lo que lista [DEPENDS](DEPENDS), en
   especial `docbook-xsl` y `highlight`. Sin `docbook-xsl`, `xsltproc` intenta
   descargar las hojas de estilo de sourceforge y falla.
2. **Seguimiento.** `make status` mide lo pendiente por capítulo.
   `utils/translation_status.py -s FICHERO` lo desglosa por sección y `-v`
   indica la línea de cada bloque pendiente. Falta usarlo para sustituir la
   tabla manual de [STATUS](STATUS), que lleva años desfasada: asigna
   responsable a capítulos que siguen al 0 %.
3. **Glosario.** Reunir en un fichero los términos ya fijados en el volumen 1
   y en lo traducido del volumen 2:
   - términos traducidos: plantilla, iterador, contenedor, objeto-función,
     hilo, bloqueo letal…;
   - términos que se dejan en inglés: *framework*, y los patrones *Template
     Method* y *Builder*.

   Hay que tenerlo cerrado antes de C05, C06 y C07, que son los capítulos con
   más terminología.
4. **Decidir qué hacer con las notas al pie.** El texto traducido conserva las
   marcas `[15]` del original, pero el texto de las notas no está en el
   repositorio. Propuesta: resolverlo mientras se traduce cada sección,
   recuperando la nota del original (cada capítulo lleva la URL en la
   cabecera) y escribiéndola como `<footnote>`. Si se deja para el final, habrá
   que repasar todo el volumen otra vez.

## Fase 1: cerrar lo casi terminado (unas 4.600 palabras)

- **C02 y C03:** restos sueltos, unas 150 palabras, casi todo en los
  ejercicios de C03.
- **C04:** el resto de «Manipuladores», y además «Iostream examples»,
  «Internationalization», «Summary» y «Exercises».

## Fase 2: completar los capítulos a medias (unas 25.800 palabras)

- **C11:** el final de «Finalización de tareas», más «Cooperación entre
  hilos», «Bloqueo letal», el resumen y los ejercicios.
- **C10:** el resto de «Factorías», más Builder, Observador, «Despachado
  múltiple», el resumen y los ejercicios.
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
2. **Normas:** seguir [TRADUCCION](TRADUCCION) y `misc/guiaestilo.html`:
   - nada de gerundios en los títulos y la menor pasiva posible;
   - dirigirse al lector en tercera persona («usted»);
   - no traducir el código ni los identificadores;
   - usar `<kw>`, `<oper>`, `<code>` y `<classname>` como indica
     [DOCBOOK](DOCBOOK).
3. **Listados:** respetar las marcas `//: V2Cxx:Fichero.cpp`, con una línea en
   blanco encima y otra debajo. `fix_includes.py` se encarga del resto.
4. **Verificar:** ejecutar `make Volumen2.xml validate`, comprobar con
   `utils/translation_status.py -s -v FICHERO` que la sección no deja bloques
   pendientes y, de vez en cuando, generar `make vol2 Volumen2.pdf` para ver
   el resultado.
5. **Revisión:** revisar el diff y hacer el commit, por sección o por
   capítulo.

## Fuera de este plan

Las tareas pendientes del volumen 1 que figuran en [TODO](TODO): cambiar
«template» por «plantilla» en todo el libro y traducir los comentarios de los
listados. Son tareas de revisión, no de traducción.
