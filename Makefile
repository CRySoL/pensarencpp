

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

html: generated/filtered.xml
	-mkdir html
	xsltproc  --xinclude \
	-stringparam chunker.output.encoding ISO-8859-1 \
	-stringparam chunker.output.indent yes \
	-stringparam base.dir html/ \
	--output  $@  $(XSL_HTML)  $<
	cp stylesheets/*.css html/


pdf: pdf/$(MAIN).pdf


pdf/$(MAIN).pdf: generated/$(MAIN).tex
	@echo '-- Building PDF'
	-mkdir pdf
	cd generated
	pdflatex  $<
	makeindex $(MAIN).idx
	pdflatex $<


generated/$(MAIN).tex: generated/filtered.xml
	@echo '-- Building LaTeX '
	cd generated
	xsltproc --nonet --noout -o generated/$(MAIN).tex --xinclude \
	--stringparam l10n.gentext.default.language es \
	--stringparam profile.lang es \
	$(XSL_PDF) generated/filtered.xml


generated/filtered.xml: generated/join.xml
	sed -e "s/xmlns[:a-z]*\=\"[^\"]*\" //" $< |\
	sed -e "s/<kw>/<literal role=\"keyword\">/g" |\
	sed -e "s/<\/kw>/<\/literal>/g" |\
	sed -e "s/<oper>/<literal role=\"operator\">/g" |\
	sed -e "s/<\/oper>/<\/literal>/g" > $@

generated/join.xml: $(FILES)
	-mkdir generated
	xsltproc --xinclude \
	   stylesheets/profile.xsl \
           $(MAIN).xml > $@

validate:
	xsltproc  --xinclude --noout stylesheet/profile.xsl $(MAIN)



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
	$(RM) generated/*
	$(RM) html/*
	$(RM) pdf/*
	-rmdir generated html pdf
	$(RM) *~ *.log


vclean: clean

# Otras tareas
install: 
	scp html/* arco:public_html/pensar_en_C++/

