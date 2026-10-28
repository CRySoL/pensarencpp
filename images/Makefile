
ifndef EPS2PDF
EPS2PDF=epstopdf --filter
endif

PNG=$(patsubst %.svg, %.png,  $(wildcard *.svg))
PDF=$(patsubst %.svg, %.pdf,  $(wildcard *.svg))

all: $(PNG) $(PDF)

# Inkscape 1.x: las opciones cortas -e/-P/-A de la rama 0.x ya no existen
%.png: %.svg
	inkscape --export-type=png --export-filename=$@ --export-dpi=85 $<

%.ps: %.svg
	inkscape --export-type=ps --export-filename=$@ $<

%.pdf: %.svg
	inkscape --export-type=pdf --export-filename=$@ $<

#%.pdf: %.ps
#	$(EPS2PDF) < $< > $@

clean::
	$(RM) $(PNG) $(PDF)

