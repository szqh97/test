<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="text"/>

<xsl:template match="/shots">
<xsl:for-each select="shot">
      <xsl:value-of select="start"/>
      <xsl:text>
</xsl:text>
      <xsl:value-of select="end"/>
      <xsl:text>
</xsl:text>
</xsl:for-each>
</xsl:template>

</xsl:stylesheet>
