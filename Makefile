

#XSLSTYLE=http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl
#XSLSTYLE=/usr/share/sgml/docbook/stylesheet/xsl/ldp/ldp-html.xsl
#XSLSTYLE=/usr/share/sgml/docbook/stylesheet/xsl/ldp/ldp-html-chunk.xsl
XSLSTYLE=/usr/share/xml/docbook/stylesheet/ldp/html/tldp-sections.xsl
#XSLSTYLE=/usr/share/xml/docbook/stylesheet/nwalsh/html/docbook.xsl
XSLSTYLETEX=/usr/share/xml/docbook/stylesheet/db2latex/latex/docbook.xsl

FILES=$(wildcard *.sgml)

all: htmls

htmls: $(FILES)
	-mkdir htmls
	xsltproc  --xinclude \
	-stringparam chunker.output.encoding ISO-8859-1 \
	-stringparam chunker.output.indent yes \
	-stringparam base.dir htmls/ \
	--output  $@  $(XSLSTYLE)  PensarEnC++.xml


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
	$(RM) htmls/*
	-rmdir htmls pdfs
	$(RM) *.ok_sgml
	$(RM) *~


vclean: clean

# Otras tareas
install: 
	scp htmls/* arco:public_html/pensar_en_C++/

# Para crear PDFS.
pdf: pdfs pdfs/PensarEnC++.pdf

pdfs:
	-mkdir pdfs

pdfs/PensarEnC++.pdf: pdfs/PensarEnC++.tex

%.pdf: %.tex
	cat $< |rubber-pipe -d 
	mv rubtmp0.pdf $@
	$(RM) rubtmp*

pdfs/PensarEnC++.tex: PensarEnC++.xml $(FILES)
	xsltproc  --xinclude \
	-stringparam chunker.output.encoding ISO-8859-1 \
	-stringparam chunker.output.indent yes \
	-stringparam base.dir pdfs/ \
	--output  $@  $(XSLSTYLETEX)  $<

