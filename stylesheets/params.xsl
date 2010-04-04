<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  version="1.0">

  <xsl:param name="generate.index">1</xsl:param>
  <xsl:param name="use.id.as.filename">1</xsl:param>

  <xsl:param name="admon.graphics" select="1" />
  <xsl:param name="admon.graphics.path">./images/</xsl:param>
  <xsl:param name="callout.graphics.path">./images/callouts/</xsl:param>

  <xsl:param name="section.autolabel" select="1" />
  <xsl:param name="section.label.includes.component.label">1</xsl:param>
  <xsl:param name="make.valid.html" select="1" />

<!-- todavía no
  <xsl:param name="collect.xref.targets" select="'yes'" />
  <xsl:param name="targets.filename" select="'pec-xrefs.xml'" />
-->

  <xsl:param name="toc.section.depth" select="1" />
  <!-- doesn't work correctly currently
  <xsl:param name="chunk.tocs.and.lots" select="1" />
  <xsl:param name="chunk.seperate.lots" select="1" />
  -->

  <xsl:param name="chunk.section.depth" select="2" />
  <xsl:param name="chunker.output.indent" select="'yes'" />
  <xsl:param name="chunker.output.encoding" select="'ISO-8859-1'"/>

  <xsl:param name="navig.showtitles" select="1" />
  <xsl:param name="navig.graphics" select="1" />
  <xsl:param name="navig.graphics.extension">.png</xsl:param>
  <xsl:param name="navig.graphics.path">./images/</xsl:param>

  <!-- colocación de los caption en los flotantes -->
  <xsl:param name="formal.title.placement">
    figure after
    example after
    equation before
    table after
    procedure before
  </xsl:param>

  <!-- Add NotInToc role to simplesect, which is using in fdl.xml to
       deal with FDL-In-TOC issue.
       also omit title 'image' if the links in header and footer
       pointing to the images
    -->
  <xsl:template match="simplesect[@role = 'NotInToc']" mode="toc"/>

  <!-- suppress all elements which have the 'tex' role, because we don't
       want to process elements which are obviously for PDF generation
    -->
  <xsl:template match="*[@role='tex']" />


  <!-- For unknown reasons the original version of the template starting
       from August 2004 would unwind the path of the sourcecode several
       times into the processing of the fileref thus prepending the path
       a few times into the src attribute of the img tag -->
  <xsl:template name="mediaobject.filename">
    <xsl:param name="object"></xsl:param>

    <xsl:variable name="data" select="$object/videodata
				      |$object/imagedata
				      |$object/audiodata
				      |$object"/>

    <xsl:variable name="filename">
      <xsl:choose>
	<xsl:when test="$data[@fileref]">
	  <xsl:value-of select="$data/@fileref"/>
	</xsl:when>
	<xsl:when test="$data[@entityref]">
	  <xsl:value-of select="unparsed-entity-uri($data/@entityref)"/>
	</xsl:when>
	<xsl:otherwise></xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="real.ext">
      <xsl:call-template name="filename-extension">
	<xsl:with-param name="filename" select="$filename"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="ext">
      <xsl:choose>
	<xsl:when test="$real.ext != ''">
	  <xsl:value-of select="$real.ext"/>
	</xsl:when>
	<xsl:otherwise>
	  <xsl:value-of select="$graphic.default.extension"/>
	</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="graphic.ext">
      <xsl:call-template name="is.graphic.extension">
	<xsl:with-param name="ext" select="$ext"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:choose>
      <xsl:when test="$real.ext = ''">
	<xsl:choose>
	  <xsl:when test="$ext != ''">
	    <xsl:value-of select="$filename"/>
	    <xsl:text>.</xsl:text>
	    <xsl:value-of select="$ext"/>
	  </xsl:when>
	  <xsl:otherwise>
	    <xsl:value-of select="$filename"/>
	  </xsl:otherwise>
	</xsl:choose>
      </xsl:when>
      <xsl:when test="not($graphic.ext)">
	<xsl:choose>
	  <xsl:when test="$graphic.default.extension != ''">
	    <xsl:value-of select="$filename"/>
	    <xsl:text>.</xsl:text>
	    <xsl:value-of select="$graphic.default.extension"/>
	  </xsl:when>
	  <xsl:otherwise>
	    <xsl:value-of select="$filename"/>
	  </xsl:otherwise>
	</xsl:choose>
      </xsl:when>
      <xsl:otherwise>
	<xsl:value-of select="$filename"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:param name="local.l10n.xml" select="document('')"/>
  <l:i18n xmlns:l="http://docbook.sourceforge.net/xmlns/l10n/1.0">
    <l:l10n language="es">
      <l:gentext key="ListofExamples" text="Índice de listados"/>
      <l:context name="title-numbered">
	<l:template name="chapter" text="%t: "/>
      </l:context>
      <l:context name="title">
	<l:template name="example" text="Listado %n. %t"/>
      </l:context>
    </l:l10n>
  </l:i18n>

  <xsl:template match="revision[@role='svn']/date" mode="titlepage.mode">
    <xsl:value-of select="substring(.,8,10)"/>
  </xsl:template>

  <xsl:template match="revision[@role='svn']/authorinitials" mode="titlepage.mode">
    <xsl:value-of select="substring-before(substring-after(.,'Author: '), '$')"/>
  </xsl:template>


  <!-- pec++ -->
  <xsl:template match="highlights">
    <div class="highlights">
      <xsl:apply-templates/>
    </div>
  </xsl:template>

  <xsl:template match="type">
    <code class="type"><xsl:apply-templates/></code>
  </xsl:template>

  <xsl:template match="quote">
    <xsl:text>«</xsl:text><xsl:apply-templates/><xsl:text>»</xsl:text>
  </xsl:template>


</xsl:stylesheet>
