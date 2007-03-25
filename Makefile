
XSLSTYLETEX=/usr/share/xml/docbook/stylesheet/db2latex/latex/docbook.xsl

XSL_HTML=stylesheets/plainhtml.xsl
XSL_PDF=stylesheets/plainprint.xsl

MAIN=Volumen1
FILES=$(wildcard Capitulo*.xml Apendice*.xml) Volumen?-master.xml

all: make_images html $(MAIN).pdf


html: Volumen1-tagged.xml
	@-mkdir -p html/images
	xsltproc  --xinclude \
	  --stringparam chunker.output.encoding ISO-8859-1 \
	  --stringparam chunker.output.indent yes \
	  --stringparam base.dir html/ \
	  --output  $@  $(XSL_HTML)  $<

	cp images/*.png html/images
	cp images/web/* html/images/
	cp stylesheets/*.css html/

	grep -l BEGINCODE html/*.html | xargs python utils/html_colorize.py 
	$(RM) html/*.code

	highlight --data-dir ./stylesheets/highlight --style emacs21 code/C02/Hello.cpp > /dev/null
	mv highlight.css html/


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

Volumen1-tagged.xml: Volumen1.xml
	@echo "--- Añadiendo marcas en listados para coloreado"
	python utils/xml_tag_codes.py $< > $@

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


install: pack
	$(MAKE) -f Makeinstall

pack:
	@-mkdir products
	mv html products/
	mv $(MAIN).pdf products/


validate:
	xsltproc --xinclude --noout stylesheets/profile.xsl $(MAIN).xml


# Para Descomprimir y arreglar los ficheros de código
VOL1_ALL=../original/TICPP-2nd-ed-Vol-one.zip
VOL1_CODE=TICPP-2nd-ed-Vol-one-code.zip

.INTERMEDIATE: $(VOL1_CODE)

code:   $(VOL1_CODE)
	unzip $< -d $@
	python ./PatchSources.py code

$(VOL1_CODE): $(VOL1_ALL)
	unzip $< $@



# Limpieza
clean:
	$(RM) join.xml fase?.xml 
	$(RM) Volumen?.xml *-tagged.xml
	$(RM) *.tex *.log *.glo *.aux *.idx *.out *.pdf *.toc *.ilg *.ind
	$(RM) *~ 


vclean: clean
	$(RM) -r products
	$(RM) html/images/*
	-rmdir html/images
	$(RM) html/*
	-rmdir -p html
	$(MAKE) -C images clean





