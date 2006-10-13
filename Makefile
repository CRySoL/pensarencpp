

#XSLSTYLE=http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl
#XSLSTYLE=/usr/share/sgml/docbook/stylesheet/xsl/ldp/ldp-html.xsl
#XSLSTYLE=/usr/share/sgml/docbook/stylesheet/xsl/ldp/ldp-html-chunk.xsl
##XSLSTYLE=/usr/share/xml/docbook/stylesheet/ldp/html/tldp-sections.xsl
#XSLSTYLE=/usr/share/xml/docbook/stylesheet/nwalsh/html/docbook.xsl
XSLSTYLETEX=/usr/share/xml/docbook/stylesheet/db2latex/latex/docbook.xsl

XSL_HTML=stylesheets/plainhtml.xsl
XSL_PDF=stylesheets/plainprint.xsl

MAIN=PensarEnC++
FILES=$(wildcard Capitulo*.xml Apendice*.xml) $(MAIN).xml

all: html $(MAIN).pdf
	@-mkdir products
	mv html products/
	mv $(MAIN).pdf products/


html: tagged.xml
	@-mkdir -p html/images
	xsltproc  --xinclude \
	  --stringparam chunker.output.encoding ISO-8859-1 \
	  --stringparam chunker.output.indent yes \
	  --stringparam base.dir html/ \
	  --output  $@  $(XSL_HTML)  $<

	cp images/*.gif html/images/
	cp images/web/* html/images/
	cp stylesheets/*.css html/

	grep -l BEGINCODE html/*.html | xargs python utils/html_colorize.py 
	$(RM) html/*.code

	highlight --data-dir ./stylesheets/highlight --style emacs21 code/C02/Hello.cpp > /dev/null
	mv highlight.css html/



$(MAIN).pdf: $(MAIN).tex
	@echo '-- Building PDF'
	pdflatex  $<
	makeindex $(MAIN).idx
	pdflatex $<


$(MAIN).tex: raw.tex
	python utils/latex_filter.py $< $@


raw.tex: final.xml
	@echo '-- Building LaTeX '
	xsltproc --nonet --noout -o raw.tex --xinclude \
	  --stringparam l10n.gentext.default.language es \
	  --stringparam profile.lang es \
	  --stringparam admon.graphics.path /usr/share/xml/docbook/stylesheet/db2latex/latex/figures \
	$(XSL_PDF) final.xml


tagged.xml: final.xml
	@echo "--- Poniendo marcas en listados para coloreado"
	python utils/xml_tag_codes.py $< > $@

final.xml: $(FILES)
	@echo "--- Montando el documento"
	xsltproc --xinclude stylesheets/profile.xsl $(MAIN).xml > aux1.xml
	@echo "--- Rutas a los listados"
	python utils/fix_includes.py aux1.xml > aux2.xml
	@echo "--- Incluyendo listados"
	xsltproc --xinclude stylesheets/profile.xsl aux2.xml > join.xml
	@echo "--- Eliminando xmlns y traducción de tags extra"
	sed -e "s/xmlns[:a-z]*\=\"[^\"]*\" //" join.xml |\
	python utils/db_filter.py > $@



validate:
	xsltproc --xinclude --noout stylesheet/profile.xsl $(MAIN)


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
	$(RM) -r products
	$(RM) html/images/*
	-rmdir html/images
	$(RM) html/*
	-rmdir -p html pdf
	$(RM) join.xml aux?.xml final.xml tagged.xml
	$(RM) *~ 
	$(RM) *.tex *.log *.glo *.aux *.idx *.out *.pdf *.toc *.ilg *.ind


vclean: clean

# Otras tareas
install: 
	scp html/* arco:public_html/pensar_en_C++/

