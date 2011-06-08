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

  <xsl:param name="latex.encoding">utf8</xsl:param>
  <xsl:param name="latex.unicode.use">1</xsl:param>

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


	<xsl:template match="chapter/chapterinfo|appendix/chapterinfo">
	  <xsl:text>\vspace{-1cm}{\Large </xsl:text>
	  <xsl:value-of select="ancestor::chapter/subtitle"/>
	  <xsl:value-of select="ancestor::appendix/subtitle"/>
	  <xsl:text>}\vspace{1cm}</xsl:text>

	  <xsl:text>\begin{flushright} \emph{</xsl:text>
	  <xsl:apply-templates/>
	  <xsl:text>}\end{flushright} \par</xsl:text>
	  <xsl:text>\vspace{1cm}</xsl:text>
	</xsl:template>

	<xsl:template match="appendix">
	  <xsl:if test="not (preceding-sibling::appendix)">
		<xsl:text>% ---------------------&#10;</xsl:text>
		<xsl:text>% Appendixes start here&#10;</xsl:text>
		<xsl:text>% ---------------------&#10;</xsl:text>
		<xsl:text>\appendix&#10;</xsl:text>
	  </xsl:if>
	  <xsl:call-template name="makeheading">
		<!-- raise to the highest existing book section level (part or chapter) -->
		<xsl:with-param name="level">
		  <xsl:choose>
			<xsl:when test="preceding-sibling::part or
			  following-sibling::part">-1</xsl:when>
			<xsl:when test="parent::book or parent::part">0</xsl:when>
			<xsl:otherwise>1</xsl:otherwise>
		  </xsl:choose>
		</xsl:with-param>
	  </xsl:call-template>

	  <xsl:apply-templates></xsl:apply-templates>
	</xsl:template>



</xsl:stylesheet>
