# -*- coding:utf-8 -*-

CHUNK_XSL=stylesheets/htmlchunk.xsl
SINGLE_XSL=stylesheets/htmlsingle.xsl
XSL_PDF=stylesheets/plainprint.xsl

FILES=$(wildcard V1-*.xml V2-*.xml master_Volumen*.xml)


all: make_images vol1 Volumen1.pdf Volumen1.rst vol2 Volumen2.pdf

Volumen%-html.tar.bz2: vol%
	tar cfj $@ $<

vol%: tagged-Volumen%.xml stylesheets/highlight.css
	@-mkdir -p $@/images
	xsltproc  --xinclude \
	  --stringparam base.dir $@/ \
	  --output  $@  $(CHUNK_XSL)  $<

	xsltproc  --xinclude \
	  --stringparam base.dir $@/ \
	  --output $@/$@.html $(SINGLE_XSL)  $<

	cp images/*.png $@/images
	cp images/*.gif $@/images    # solo para incluir los dibujos originales
	cp images/web/* $@/images/

	cp stylesheets/*.css $@/

#	ln -s ../stylesheets/common.css $@/
#	ln -s ../stylesheets/single.css $@/
#	ln -s ../stylesheets/chunk.css $@/
#	ln -s ../stylesheets/highlight.css $@/

	grep -l BEGINCODE $@/*.html | xargs python utils/html_colorize.py
	$(RM) $@/*.code


stylesheets/highlight.css: code_v1/C02/Hello.cpp stylesheets/highlight/themes/emacs21.style
	highlight --print-style --data-dir ./stylesheets/highlight --style emacs21 --outdir stylesheets $<


tagged-Volumen%.xml: Volumen%.xml
	@echo "--- AÑADIENDO MARCAS EN LISTADOS PARA COLOREADO"
	python utils/xml_tag_codes.py $< > $@

%.pdf: %.xml
	dblatex --debug --style dblatex/pecstyle $<

%.rst: %.xml
	echo "-*- coding:utf-8 -*-" > $@
	python db2rst/db2rst.py $< >> $@


Volumen1.xml: master_Volumen1.xml $(wildcard V1-*.xml)
Volumen2.xml: master_Volumen2.xml $(wildcard V2-*.xml)


Volumen%.xml: code_v%
	@echo "--- MONTANDO EL DOCUMENTO"
	xsltproc --xinclude stylesheets/profile.xsl master_$(basename $@).xml > fase1.xml
	@echo "--- RUTAS A LOS LISTADOS"
	python utils/fix_includes.py fase1.xml > fase2.xml
	@echo "--- INCLUYENDO LISTADOS"
	xsltproc --xinclude stylesheets/profile.xsl fase2.xml > join.xml
	@echo "--- ELIMINANDO XMLNS Y TRADUCCIÓN DE TAGS EXTRA"
	sed -e "s/xmlns[:a-z]*\=\"[^\"]*\" //" join.xml |\
	sed -e "s/\/\/\/:~//" |\
	python utils/db_filter.py > $@
	xmllint --noout --postvalid $@

code_v%: code_orig_v%
	rm -rf $@
	cp -r $< $@
	python utils/patch_sources.py $@


make_images:
	$(MAKE) -C images

products: Volumen1-html.tar.bz2 vol1 Volumen1.pdf \
	  Volumen2-html.tar.bz2 vol2 Volumen2.pdf # Volumen1.rst
	@-mkdir products
	cp -r $^ products/

install: products
	scp -r products repo:public_html/pensar_en_C++/


validate:
	xsltproc --xinclude --noout stylesheets/profile.xsl Volumen%.xml


# Limpieza
clean:
	$(RM) fase?.xml join.xml *.bz2
	$(RM) Volumen?.xml *-tagged.xml
	$(RM) *.pdf *.tex *.log *.glo *.aux *.idx *.out *.toc *.ilg *.ind
	$(RM) Volumen?.rst
	$(RM) stylesheets/highlight.css
	$(RM) *~
	$(RM) -r products
	$(RM) vol1/images/* vol2/images/*
	-rmdir vol1/images  vol2/images
	$(RM) vol1/* vol2/*
	-rmdir -p vol1 vol2

vclean: clean
	$(MAKE) -C images clean
	rm -rf code_v1 code_v2
	$(RM) pec-xrefs.xml

