<?xml version="1.0" encoding="utf-8"?>
<!-- This file is part of the gimp-help-2 project and is 
     (C) 2002, 2003, 2004, 2005, 2006 Daniel Egger, Róman Joost
     You may use this file in accordance to the GNU Free Documentation License
     Version 1.1 which is available from http://www.gnu.org. -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:import href="http://docbook.sourceforge.net/release/xsl/current/xhtml/profile-chunk.xsl" />
  <xsl:param name="html.stylesheet">gimp-help-plain.css
    gimp-help-screen.css gimp-help-custom.css</xsl:param>
  <xsl:param name="generate.index">1</xsl:param>
  <xsl:param name="use.id.as.filename">1</xsl:param>
  <xsl:param name="admon.graphics" select="1" />
  <xsl:param name="admon.graphics.path">../images/</xsl:param>
  <xsl:param name="callout.graphics.path">../images/callouts/</xsl:param>
  <xsl:param name="section.autolabel" select="1" />
  <xsl:param name="make.valid.html" select="1" />
  <xsl:param name="collect.xref.targets" select="'yes'" />
  <xsl:param name="targets.filename" select="'gimp-xrefs.xml'" />
  <xsl:param name="toc.section.depth" select="2" />
  <xsl:param name="chunk.section.depth" select="2" />
  <!-- doesn't work correctly currently
  <xsl:param name="chunk.tocs.and.lots" select="1" />
  <xsl:param name="chunk.seperate.lots" select="1" /> 
  -->
  <xsl:param name="chunker.output.indent" select="'yes'" />
  <xsl:param name="navig.showtitles" select="1" />
  <xsl:param name="navig.graphics" select="1" />
  <xsl:param name="navig.graphics.extension">.png</xsl:param>
  <xsl:param name="navig.graphics.path">../images/</xsl:param>

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
  
  <!-- custom header and footer navigation -->
  <xsl:template name="header.navigation">
    <xsl:call-template name="footer.navigation">
      <xsl:with-param name="prev" select="$prev" />
      <xsl:with-param name="next" select="$next" />
      <xsl:with-param name="nav.context" select="$nav.context" />
    </xsl:call-template>
  </xsl:template>
  <xsl:template name="footer.navigation">
    <xsl:param name="prev" select="/foo"/>
    <xsl:param name="next" select="/foo"/>
    <xsl:param name="nav.context"/>

    <xsl:variable name="home" select="/*[1]"/>
    <xsl:variable name="up" select="parent::*"/>

    <xsl:variable name="row1" select="count($prev) &gt; 0                                                             or count($up) &gt; 0
                                      or count($next) &gt; 0"/>

    <xsl:variable name="row2" select="($prev and $navig.showtitles != 0)
                              or (generate-id($home) != generate-id(.)
                              or $nav.context = 'toc')
                              or ($chunk.tocs.and.lots != 0                   
                              and $nav.context != 'toc')                      
                              or ($next and $navig.showtitles != 0)"/>

    <xsl:if test="$suppress.navigation = '0' and $suppress.footer.navigation = '0'">
      <div class="navfooter">
        <xsl:if test="$footer.rule != 0">
          <hr/>
        </xsl:if>

        <xsl:if test="$row1 or $row2">
          <table width="100%" summary="Navigation footer">
            <xsl:if test="$row1">
              <tr>
                <td width="40%" align="left">
                  <xsl:if test="count($prev)&gt;0">
                    <a accesskey="p">
                      <xsl:attribute name="href">
                        <xsl:call-template name="href.target">
                          <xsl:with-param name="object" select="$prev"/>
                        </xsl:call-template>
                      </xsl:attribute>
                      <xsl:call-template name="navig.content">
                        <xsl:with-param name="direction" select="'prev'"/>
                      </xsl:call-template>
                    </a>
                  </xsl:if>
                  <xsl:text>&#160;</xsl:text>
                </td>
                <td width="20%" align="center">
                  <xsl:choose>
                    <xsl:when test="count($up)&gt;0 and generate-id($up) != generate-id($home)">
          <a accesskey="u">
                        <xsl:attribute name="href">
                          <xsl:call-template name="href.target">
                            <xsl:with-param name="object" select="$up"/>
                          </xsl:call-template>
                        </xsl:attribute>
                        <xsl:call-template name="navig.content">
                          <xsl:with-param name="direction" select="'up'"/>
                        </xsl:call-template>
                      </a>
                    </xsl:when>
                    <xsl:otherwise>&#160;</xsl:otherwise>
                  </xsl:choose>
                </td>
                <td width="40%" align="right">
                  <xsl:text>&#160;</xsl:text>
                  <xsl:if test="count($next)&gt;0">
                    <a accesskey="n">
                      <xsl:attribute name="href">
                        <xsl:call-template name="href.target">
                          <xsl:with-param name="object" select="$next"/>
                        </xsl:call-template>
                      </xsl:attribute>
                      <xsl:call-template name="navig.content">
                        <xsl:with-param name="direction" select="'next'"/>
                      </xsl:call-template>
                    </a>
                  </xsl:if>
                </td>
              </tr>
            </xsl:if>

            <xsl:if test="$row2">
              <tr>
                <td width="40%" align="left" valign="top">
                  <xsl:if test="$navig.showtitles != 0 and count($prev)&gt;0">
                    <a accesskey="p">
                      <xsl:attribute name="href">
                        <xsl:call-template name="href.target">
                          <xsl:with-param name="object" select="$prev"/>
                        </xsl:call-template>
                      </xsl:attribute>
                    <xsl:apply-templates select="$prev" mode="object.title.markup"/>
                    </a>
                  </xsl:if>
                  <xsl:text>&#160;</xsl:text>
                </td>
                <td width="20%" align="center">
                  <xsl:choose>
                    <xsl:when test="$home != . or $nav.context = 'toc'">
                      <a accesskey="h">
                        <xsl:attribute name="href">
                          <xsl:call-template name="href.target">
                            <xsl:with-param name="object" select="$home"/>
                          </xsl:call-template>
                        </xsl:attribute>
                        <xsl:call-template name="navig.content">
                          <xsl:with-param name="direction" select="'home'"/>
                        </xsl:call-template>
                      </a>
                      <xsl:if test="$chunk.tocs.and.lots != 0 and $nav.context != 'toc'">
                        <xsl:text>&#160;|&#160;</xsl:text>
                      </xsl:if>
                    </xsl:when>
                    <xsl:otherwise>&#160;</xsl:otherwise>
                  </xsl:choose>

                  <xsl:if test="$chunk.tocs.and.lots != 0 and $nav.context != 'toc'">
                    <a accesskey="t">
                      <xsl:attribute name="href">
                        <xsl:apply-templates select="/*[1]" mode="recursive-chunk-filename"/>
                        <xsl:text>-toc</xsl:text>
                        <xsl:value-of select="$html.ext"/>
                      </xsl:attribute>
                      <xsl:call-template name="gentext">
                        <xsl:with-param name="key" select="'nav-toc'"/>
                      </xsl:call-template>
                    </a>
                  </xsl:if>
                </td>
                <td width="40%" align="right" valign="top">
                  <xsl:text>&#160;</xsl:text>
                  <xsl:if test="$navig.showtitles != 0 and count($next) &gt; 0">
                    <a accesskey="n">
                      <xsl:attribute name="href">
                        <xsl:call-template name="href.target">
                          <xsl:with-param name="object" select="$next"/>
                        </xsl:call-template>
                      </xsl:attribute>
                    <xsl:apply-templates select="$next" mode="object.title.markup"/>
                    </a>
                  </xsl:if>
                </td>
              </tr>
            </xsl:if>
          </table>
        </xsl:if>
      </div>
    </xsl:if>
  </xsl:template>
  
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
</xsl:stylesheet>