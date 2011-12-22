<?php
	ob_start();
	include_once('xml.php');
	$xml = ob_get_contents();
	ob_end_clean();
	
	$xslt = new xsltProcessor;
	$xslt->importStyleSheet(DomDocument::load('common.xsl'));
	print $xslt->transformToXML(DomDocument::loadXML($xml));	
?>

