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

<!-- DB2LaTeX requires Palatino like fonts -->
<xsl:param name="xetex.font">
  <xsl:text>\setmainfont{URW Palladio L}&#10;</xsl:text>
</xsl:param>

  <xsl:param name="latex.babel.use">1</xsl:param>

  <xsl:param name="latex.babel.language">spanish</xsl:param>

  <xsl:param name="latex.hyperparam">colorlinks,linkcolor=blue,urlcolor=blue,</xsl:param>

  <xsl:param name="draft.mode">no</xsl:param>
  <xsl:param name="latex.class.book">book</xsl:param>

   <xsl:param name="appendix.autolabel">0</xsl:param>

  <xsl:template match="highlights">
    <xsl:text>{\large \bfseries </xsl:text>
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


  <xsl:template match="quote">
    <xsl:text>\guillemotleft{}</xsl:text>
    <xsl:apply-templates/>
    <xsl:text>\guillemotright{}</xsl:text>
  </xsl:template>

<!--
  <xsl:template match="programlisting">
    <xsl:variable name="language">
      <xsl:choose>
      <xsl:when test="@language!=''">
	<xsl:value-of select="@language"/>
	</xsl:when>
	<xsl:otherwise>C++</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:text>&#10;\begin{listing}[language=</xsl:text>
    <xsl:value-of select="$language"/>
    <xsl:text>]</xsl:text>
    <xsl:apply-templates mode="latex.verbatim"/>
    <xsl:text>\end{listing}&#10;</xsl:text>
  </xsl:template>
-->

  <xsl:template match="screen">
    <xsl:text>&#10;\begin{listing}[style=console]</xsl:text>
    <xsl:apply-templates mode="latex.verbatim"/>
    <xsl:text>\end{listing}&#10;</xsl:text>
  </xsl:template>

  <xsl:template match="example">
    <xsl:apply-templates select="programlisting"/>
  </xsl:template>

</xsl:stylesheet>
