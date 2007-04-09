
XSLSTYLETEX=/usr/share/xml/docbook/stylesheet/db2latex/latex/docbook.xsl

XSL_HTML=stylesheets/plainhtml.xsl
XSL_PDF=stylesheets/plainprint.xsl

FILES=$(wildcard V1-*.xml V2-*.xml Volumen*-master.xml)


ad:
	echo $(FILES)

all: make_images vol1 Volumen1.pdf

Volumen%-html.bz2: vol%
	tar cfj $@ $<

vol1: Volumen1-tagged.xml
	@-mkdir -p vol1/images
	xsltproc  --xinclude \
	  --stringparam chunker.output.encoding ISO-8859-1 \
	  --stringparam chunker.output.indent yes \
	  --stringparam base.dir vol1/ \
	  --output  $@  $(XSL_HTML)  $<

	cp images/*.png vol1/images
	cp images/web/* vol1/images/
	cp stylesheets/*.css vol1/

	grep -l BEGINCODE vol1/*.html | xargs python utils/html_colorize.py 
	$(RM) vol1/*.code

	highlight --data-dir ./stylesheets/highlight --style emacs21 code/C02/Hello.cpp > /dev/null
	mv highlight.css vol1/

Volumen1-tagged.xml: Volumen1.xml
	@echo "--- Añadiendo marcas en listados para coloreado"
	python utils/xml_tag_codes.py $< > $@


%.pdf: %.xml
	dblatex -T dblatex/pec $<


#$(MAIN).pdf: $(MAIN).tex
#	@echo '-- Building PDF'
#	pdflatex  $<
#	makeindex $(MAIN).idx
#	pdflatex $<
#
#
#$(MAIN).tex: raw.tex
#	python utils/latex_filter.py $< $@
#
#
#raw.tex: Volumen1-final.xml stylesheets/plainprint.xsl
#	@echo '-- Building LaTeX '
#	xsltproc --nonet --noout -o raw.tex --xinclude \
#	  --stringparam l10n.gentext.default.language es \
#	  --stringparam profile.lang es \
#	  --stringparam admon.graphics.path /usr/share/xml/docbook/stylesheet/db2latex/latex/figures \
#	$(XSL_PDF) Volumen1-final.xml
#

Volumen1.xml: $(FILES)
	@echo "--- Montando el documento"
	xsltproc --xinclude stylesheets/profile.xsl $(basename $@)-master.xml > fase1.xml
	@echo "--- Rutas a los listados"
	python utils/fix_includes.py fase1.xml > fase2.xml
	@echo "--- Incluyendo listados"
	xsltproc --xinclude stylesheets/profile.xsl fase2.xml > join.xml
	@echo "--- Eliminando xmlns y traducción de tags extra"
	sed -e "s/xmlns[:a-z]*\=\"[^\"]*\" //" join.xml |\
	sed -e "s/\/\/\/:~//" |\
	python utils/db_filter.py > $@

make_images:
	$(MAKE) -C images

install: products
	scp -r products repo:public_html/pensar_en_C++/

products: Volumen1-html.bz2 vol1 Volumen1.pdf
	@-mkdir products
	cp -r $^ products/ 


validate:
	xsltproc --xinclude --noout stylesheets/profile.xsl Volumen1.xml


# Limpieza
clean:
	$(RM) fase?.xml join.xml 
	$(RM) Volumen?.xml *-tagged.xml
	$(RM) *.tex *.log *.glo *.aux *.idx *.out *.pdf *.toc *.ilg *.ind
	$(RM) *~ 
	$(RM) -r products
	$(RM) vol1/images/*
	-rmdir vol1/images
	$(RM) vol1/*
	-rmdir -p vol1

vclean: clean
	$(MAKE) -C images clean





