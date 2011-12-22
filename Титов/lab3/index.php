<?php
	session_start();
	header("Content-Type: text/xml");
	ob_start();
	print "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
	$db=mysql_connect("localhost","root","123") or die('<error>Unable to connect to mysql server. try edit index.php file</error>');
	if(!mysql_select_db('lab3')) sql_install();
	
	include_once('common.php');
	mysql_close($db);
	$xml = ob_get_contents();
	ob_end_clean();
	
	$xslt = new xsltProcessor;
	$xslt->importStyleSheet(DomDocument::load('common.xsl'));
	print $xslt->transformToXML(DomDocument::loadXML($xml));	
	
	//print $xml;
	
	function sql_install(){
		mysql_query("CREATE DATABASE lab3;");
		mysql_select_db('lab3');
		mysql_query("
		CREATE TABLE IF NOT EXISTS lab3_category (
		`c_category` int(10) NOT NULL PRIMARY KEY AUTO_INCREMENT, 
		`c_category_name` varchar(50) NOT NULL, 
		`c_added_timestamp` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP, 
		`c_added_user` int(10) NOT NULL DEFAULT '0', 
		`c_sortorder` mediumint(5) NOT NULL DEFAULT '10000' 
		);
		");
		mysql_query("
		CREATE TABLE IF NOT EXISTS lab3_user (
		`u_user` int(10) NOT NULL PRIMARY KEY AUTO_INCREMENT, 
		`u_name` varchar(50) NOT NULL, 
		`u_password` varchar(32) NOT NULL DEFAULT '', 
		`u_group` mediumint(5) NOT NULL DEFAULT '9', 
		`u_extra` text,
		UNIQUE (`u_name`)
		);
		");
		mysql_query("
		CREATE TABLE IF NOT EXISTS lab3_theme (
		`t_theme` int(10) NOT NULL PRIMARY KEY AUTO_INCREMENT, 
		`t_category` int(10) NOT NULL, 
		`t_theme_name` varchar(50) NOT NULL, 
		`t_added_timestamp` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP, 
		`t_added_user` int(10) NOT NULL DEFAULT '0', 
		`t_sortorder` mediumint(5) NOT NULL DEFAULT '10000' 
		);
		");
		mysql_query("
		CREATE TABLE IF NOT EXISTS lab3_test (
		`e_test` int(10) NOT NULL PRIMARY KEY AUTO_INCREMENT, 
		`e_test_name` varchar(50) NOT NULL, 
		`e_added_timestamp` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP, 
		`e_added_user` int(10) NOT NULL DEFAULT '0', 
		`e_sortorder` mediumint(5) NOT NULL DEFAULT '10000',
		`e_limit` mediumint(5) NOT NULL DEFAULT '1'
		);
		");
		mysql_query("
		CREATE TABLE IF NOT EXISTS lab3_test_theme (
		`tt_id` int(10) NOT NULL PRIMARY KEY AUTO_INCREMENT, 
		`tt_test` int(10) NOT NULL, 
		`tt_theme` int(10) NOT NULL
		);
		");
		mysql_query("
		CREATE TABLE IF NOT EXISTS lab3_question (
		`q_question` int(10) NOT NULL PRIMARY KEY AUTO_INCREMENT, 
		`q_theme` int(10) NOT NULL, 
		`q_type` mediumint(5) NOT NULL DEFAULT '0', 
		`q_text` text NOT NULL, 
		`q_correct_answer` text NOT NULL, 
		`q_added_timestamp` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP, 
		`q_added_user` int(10) NOT NULL DEFAULT '0', 
		`q_sortorder` mediumint(5) NOT NULL DEFAULT '10000',
		`q_correct_tries` mediumint(5) NOT NULL DEFAULT '0', 
		`q_tries` mediumint(5) NOT NULL DEFAULT '0'
		);
		");
		mysql_query("
		CREATE TABLE IF NOT EXISTS lab3_answer (
		`a_answer` int(10) NOT NULL PRIMARY KEY AUTO_INCREMENT, 
		`a_question` int(10) NOT NULL, 
		`a_text` text NOT NULL, 
		`a_type` mediumint(5) NOT NULL DEFAULT '0', 
		`a_sortorder` mediumint(5) NOT NULL DEFAULT '10000'
		);
		");
		mysql_query("
		CREATE TABLE IF NOT EXISTS lab3_solution (
		`s_solution` int(10) NOT NULL PRIMARY KEY AUTO_INCREMENT, 
		`s_question` int(10) NOT NULL, 
		`s_parent` int(10) NOT NULL, 
		`s_child` int(10) 
		);
		");
		mysql_query("
		CREATE TABLE IF NOT EXISTS lab3_result (
		`r_result` int(10) NOT NULL PRIMARY KEY AUTO_INCREMENT, 
		`r_test` int(10) NOT NULL, 
		`r_user` int(10) NOT NULL, 
		`r_text` text, 
		`r_started_timestamp` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP, 
		`r_ended_timestamp` TIMESTAMP
		);
		");
		mysql_query("
		INSERT INTO lab3_user (u_name, u_password, u_group) VALUES ('admin',MD5('123'),1);
		");
	}
?>

