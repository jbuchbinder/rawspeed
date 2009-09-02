<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method = "html" indent = "yes" />
<xsl:template match="/">

<html>
	<head>
		<title>Known RawSpeed Cameras</title>
		<style type="text/css">
			body {
				font-family:Verdana;font-size:12pt;background-color:#ffffff;
			}
			h1 {
				font-size:16pt;padding:8px;
			}
			h2 {
				background-color:teal;color:white;padding:8px;font-size:13pt;
			}
			span.param {
				font-style:italic;color:#666;
			}
			div.text {
				margin-left:20px;margin-bottom:15px;font-size:10pt;margin-top:0px;line-height:120%;
			}
		</style>
	</head>

	<body>
		<h1>The <xsl:value-of select="count(Cameras/Camera)"/> Known RawSpeed Cameras:</h1>
		<xsl:for-each select="Cameras/Camera">
		<xsl:sort data-type = "text" select = "concat(@make,@model)"/>
			<h2>
				<span style="font-weight:bold"><xsl:value-of select="@make"/></span>
				- <xsl:value-of select="@model"/>
				<xsl:if test="@mode != ''">, Mode: <span style="font-style:italic;"><xsl:value-of select="@mode"/></span></xsl:if>
			</h2>
			<div class="text">
				<xsl:variable name = "supported" ><xsl:value-of select="@supported"/></xsl:variable>
				<xsl:if test ="$supported = 'no'">Supported: <span style="color:red;font-style:italic;">No.</span></xsl:if>
					<xsl:if test ="not($supported = 'no')">Supported: <span style="color:green;font-style:italic;">Yes.</span>
					<br/>
					Cropped Image Size: <span class="param"><xsl:value-of select="Crop/@width"/>x<xsl:value-of select="Crop/@height"/></span> pixels.
					<br/>
					Crop Top-Left: <span class="param"><xsl:value-of select="Crop/@x"/>,<xsl:value-of select="Crop/@y"/> pixels.</span>
					<br/>
					Sensor Black: <span class="param"><xsl:value-of select="Sensor/@black"/></span>, White:
					<span class="param"><xsl:value-of select="Sensor/@white"/>.</span>
					<br/>
					Uncropped Sensor Colors Positions:<br/>
					<xsl:for-each select="CFA/Color">
						<xsl:sort data-type = "number" select = "@y*2+@x"/>
						<xsl:variable name = "color" ><xsl:value-of select="."/></xsl:variable>
						<xsl:if test="position()=last()-1"><br/></xsl:if>						
						<xsl:if test ="$color = 'RED'"><span class="param" style="color:red;">[<xsl:copy-of select="$color" />]</span></xsl:if>
						<xsl:if test ="$color = 'GREEN'"><span class="param" style="color:green;">[<xsl:copy-of select="$color" />]</span></xsl:if>
						<xsl:if test ="$color = 'BLUE'"><span class="param" style="color:blue;">[<xsl:copy-of select="$color" />]</span></xsl:if>
					</xsl:for-each>
				 </xsl:if>
			</div>
		 <br/>
		</xsl:for-each>

	</body>
</html>

</xsl:template>
</xsl:stylesheet>