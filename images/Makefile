
ifndef EPS2PDF
EPS2PDF=epstopdf --filter
endif

PNG=$(patsubst %.svg, %.png,  $(wildcard *.svg))
PDF=$(patsubst %.svg, %.pdf,  $(wildcard *.svg))

all: $(PNG) $(PDF)

%.png: %.svg
	inkscape -e $@ -d 85 $<

%.ps: %.svg
	inkscape -P $@ $<

%.pdf: %.svg
	inkscape -A $@ $<

#%.pdf: %.ps
#	$(EPS2PDF) < $< > $@

clean::
	$(RM) $(PNG) $(PDF)

