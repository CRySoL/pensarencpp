<?xml version='1.0' encoding="iso-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>

  <!-- DB2LaTeX has its own admonition graphics -->
  <xsl:param name="figure.note">note</xsl:param>
  <xsl:param name="figure.tip">tip</xsl:param>
  <xsl:param name="figure.warning">warning</xsl:param>
  <xsl:param name="figure.caution">caution</xsl:param>
  <xsl:param name="figure.important">important</xsl:param>
  
  <!-- Options used for documentclass -->
  <xsl:param name="latex.class.options">a4paper,10pt,twoside,openright</xsl:param>


  <xsl:param name="latex.babel.use">0</xsl:param>
  <xsl:param name="latex.hyperparam">colorlinks,linkcolor=blue,urlcolor=blue,</xsl:param>
  

  <xsl:param name="latex.babel.language">spanish</xsl:param>
<!--
  <xsl:param name="draft.mode">yes</xsl:param>
-->
  <xsl:param name="latex.class.book">book</xsl:param>


  <xsl:template match="highlights">
    <xsl:text>{\fontsize{13}{13pt} \selectfont \bfseries </xsl:text>
    <xsl:apply-templates/>
    <xsl:text>} \medskip </xsl:text>
  </xsl:template>

  <xsl:template match="code">
    <xsl:call-template name="inline.monoseq"/>
<!--
    <xsl:text>\texttt{</xsl:text><xsl:value-of select="."/><xsl:text>}</xsl:text>
-->
  </xsl:template>


  <xsl:template match="*[@role='html']"/>




<xsl:template match="formalpara">
  <xsl:text>&#10;{\bf </xsl:text>
<!--
  <xsl:call-template name="normalize-scape">
    <xsl:with-param name="string" select="title"/>
  </xsl:call-template>
-->
  <xsl:text>} </xsl:text>
  <xsl:apply-templates/>
  <xsl:text>&#10;</xsl:text>
  <xsl:text>&#10;</xsl:text>
</xsl:template>


  <xsl:template match="formalpara/title">
    <xsl:apply-templates/>
  </xsl:template>

</xsl:stylesheet>
