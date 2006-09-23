

#XSLSTYLE=http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl
#XSLSTYLE=/usr/share/sgml/docbook/stylesheet/xsl/ldp/ldp-html.xsl
#XSLSTYLE=/usr/share/sgml/docbook/stylesheet/xsl/ldp/ldp-html-chunk.xsl
##XSLSTYLE=/usr/share/xml/docbook/stylesheet/ldp/html/tldp-sections.xsl
#XSLSTYLE=/usr/share/xml/docbook/stylesheet/nwalsh/html/docbook.xsl
XSLSTYLETEX=/usr/share/xml/docbook/stylesheet/db2latex/latex/docbook.xsl

XSL_HTML=stylesheets/plainhtml.xsl
XSL_PDF=stylesheets/plainprint.xsl

FILES=$(wildcard *.xml)
MAIN=PensarEnC++


all: html

html: filtered.xml
	@-mkdir html
	xsltproc  --xinclude \
	  --stringparam chunker.output.encoding ISO-8859-1 \
	  --stringparam chunker.output.indent yes \
	  --stringparam base.dir html/ \
	  --output  $@  $(XSL_HTML)  $<
	cp stylesheets/*.css html/


pdf: pdf/$(MAIN).pdf


pdf/$(MAIN).pdf: $(MAIN).tex
	@echo '-- Building PDF'
	-mkdir pdf
	pdflatex  $<
	makeindex $(MAIN).idx
	pdflatex $<


$(MAIN).tex: raw.tex
	python utils/latex_filter.py $< $@


raw.tex: filtered.xml
	@echo '-- Building LaTeX '
	xsltproc --nonet --noout -o raw.tex --xinclude \
	  --stringparam l10n.gentext.default.language es \
	  --stringparam profile.lang es \
	  --stringparam admon.graphics.path /usr/share/xml/docbook/stylesheet/db2latex/latex/figures \
	$(XSL_PDF) filtered.xml

filtered.xml: join.xml
	sed -e "s/xmlns[:a-z]*\=\"[^\"]*\" //" $< |\
	python utils/db_filter.py > $@

join.xml: $(FILES)
	xsltproc --xinclude stylesheets/profile.xsl $(MAIN).xml > aux1.xml
	python utils/code_includes.py aux1.xml > aux2.xml
	xsltproc --xinclude stylesheets/profile.xsl aux2.xml > $@

validate:
	xsltproc --xinclude --noout stylesheet/profile.xsl $(MAIN)


# Para Descomprimir y arreglar los ficheros de c�digo
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
	$(RM) html/*
	$(RM) pdf/*
	-rmdir html pdf
	$(RM) join.xml aux?.xml filtered.xml
	$(RM) *~ 
	$(RM) *.log *.glo *.aux *.idx *.out *.pdf *.toc *.ilg *.ind


vclean: clean

# Otras tareas
install: 
	scp html/* arco:public_html/pensar_en_C++/

