<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html" indent="yes" version="4.0" />
  <xsl:strip-space elements="*" />

  <xsl:template match="/">
    <html>
      <head>
        <title></title>
        <link rel="stylesheet" type="text/css" href="disassembly.css" />
      </head>
      <body>
        <h1>Disassembly of <xsl:value-of select="bitfile/@filename" /></h1>
        <h2>File meta data:</h2>
        <b>Source file: </b><xsl:value-of select="bitfile/meta/sourcefilename" /><br />
        <b>Target device: </b><xsl:value-of select="bitfile/meta/targetdevicename" /><br />
        <b>Creation date: </b><xsl:value-of select="bitfile/meta/creationdate" /><br />
        <b>Creation time: </b><xsl:value-of select="bitfile/meta/creationtime" /><br />
        <h2>Packet stream:</h2>
        <table id="disassemblytable">
          <tr><th id="indexcol">Index</th><th id="ptypecol">Packet type</th><th id="opcodecol">Opcode</th><th id="registercol">Register</th><th id="wcountcol">Word count</th><th>Data</th></tr>
          <xsl:apply-templates select="bitfile/packets/dummyword | bitfile/packets/buswidthpattern | bitfile/packets/syncword | bitfile/packets/type1packet | bitfile/packets/type2packet" />
        </table>
      </body>
    </html>
  </xsl:template>

  <xsl:template match="dummyword">
    <tr class="dummywordclr"><td><xsl:value-of select="position()-1" /></td><td>Dummy word</td><td></td><td></td><td></td><td><xsl:value-of select="." /></td></tr>
  </xsl:template>

  <xsl:template match="buswidthpattern">
    <tr class="buswidthpatternclr"><td><xsl:value-of select="position()-1" /></td><td>Buswidth pattern</td><td></td><td></td><td></td><td></td></tr>
  </xsl:template>

  <xsl:template match="syncword">
    <tr class="syncwordclr"><td><xsl:value-of select="position()-1" /></td><td>Sync word</td><td></td><td></td><td></td><td></td></tr>
  </xsl:template>

  <xsl:template match="type1packet">
    <tr class="type1clr">
      <td><xsl:value-of select="position()-1" /></td>
      <td>Type 1 packet</td>
      <td>
        <xsl:choose>
          <xsl:when test="@opcode='REGISTER_WRITE'"><xsl:attribute name="class">writeopclr</xsl:attribute></xsl:when>
          <xsl:when test="@opcode='REGISTER_READ'"><xsl:attribute name="class">readopclr</xsl:attribute></xsl:when>
          <xsl:otherwise><xsl:attribute name="class">noopclr</xsl:attribute></xsl:otherwise>
        </xsl:choose>
        <xsl:value-of select="@opcode" />
      </td>
      <td>
        <xsl:if test="@register='FDRI' or @register='MFWR'"><xsl:attribute name="class">configregclr</xsl:attribute></xsl:if>
        <xsl:value-of select="@register" />
      </td>
      <td><xsl:value-of select="@wordcount" /></td>
      <td><xsl:value-of select="." /></td>
    </tr>
  </xsl:template>

  <xsl:template match="type2packet">
    <tr class="type2clr">
      <td><xsl:value-of select="position()-1" /></td>
      <td>Type 2 packet</td>
      <td>
          <xsl:choose>
          <xsl:when test="@opcode='REGISTER_WRITE'"><xsl:attribute name="class">writeopclr</xsl:attribute></xsl:when>
          <xsl:when test="@opcode='REGISTER_READ'"><xsl:attribute name="class">readopclr</xsl:attribute></xsl:when>
          <xsl:otherwise><xsl:attribute name="class">noopclr</xsl:attribute></xsl:otherwise>
        </xsl:choose>
        <xsl:value-of select="@opcode" />
      </td>
      <td></td>
      <td><xsl:value-of select="@wordcount" /></td>
      <td><xsl:value-of select="." /></td>
    </tr>
  </xsl:template>

</xsl:stylesheet>