<?xml version="1.0" encoding="windows-1251"?>
 
<xsl:stylesheet version="1.0" 
		xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
        xmlns="http://www.w3.org/1999/xhtml">
    <xsl:output method="xml" indent="yes"
		encoding="windows-1251"
        doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN" 
        doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"/>
        <xsl:template match="/">
            <html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru">
            <head>
                <meta http-equiv="Content-Type" content="text/html; charset=windows-1251" />
                <title>Лабораторная 1</title>
                <style type="text/css">
                    html {font: 11px Serif;}
					.odd td {background-color:#eef;}
					.even td {background-color:#ddf;}
					th {background-color:#aaf;}
                </style>
            </head>
            <body style="background-color:#eee;">
				<div style="margin:100px auto;width:600px;background-color:#fff;border:1px solid #ccc; padding: 0;">
					<xsl:apply-templates/>
					<div style="background-color:#ddf;border-top:1px solid #ccc; padding:1px 4px"><xsl:text> © Никитин Иван, А-14-07</xsl:text><span style="float:right;">Работа с файловой системой.</span></div>
				</div>
            </body>
			</html>
        </xsl:template>
		
		<xsl:template match="page[@action='listdir']">
			<div style="background-color:#ddf;border-bottom:1px solid #ccc;padding:1px 4px;">
				<xsl:text>Директрория:~</xsl:text>
				<xsl:value-of select="@dir"/>
				<span style="float:right;">
					<xsl:text>Привет, </xsl:text>
					<xsl:value-of select="@extra"/>
					<xsl:text> | </xsl:text>
					<xsl:if test="@uid &gt; 0">
						<a href="index.php?action=logout">Выйти</a>
					</xsl:if>
					<xsl:if test="@uid = 0">
						<a href="index.php?action=login">Войти</a>
					</xsl:if>
				</span>
			</div>
			<table style="padding:10px;width:100%">
			<tr><th>#</th><th>Имя файла</th><th>Размер</th><th>Стат-ка</th></tr>	
				<xsl:apply-templates select="item"/>
			</table>
		</xsl:template>
		
		<xsl:template match="item[position() mod 2 = 1]">
			<tr class="odd">
				<xsl:apply-templates select="." mode="icon"/>
				<xsl:apply-templates select="." mode="link"/>
				<td style="width:10%"><xsl:value-of select="@size"/></td>
				<td style="width:10%"><xsl:value-of select="@stat"/></td>
			</tr>
		</xsl:template>
		
		<xsl:template match="item[position() mod 2 = 0]">
			<tr class="even">
				<xsl:apply-templates select="." mode="icon"/>
				<xsl:apply-templates select="." mode="link"/>
				<td style="width:10%"><xsl:value-of select="@size"/></td>
				<td style="width:10%"><xsl:value-of select="@stat"/></td>
			</tr>
		</xsl:template>
		
		<xsl:template match="item[@type='directory']" mode="link">
			<td style="width:80%"><a href="index.php?dir={@file}"><xsl:value-of select="@name"/></a></td>
		</xsl:template>
		
		<xsl:template match="item[@type!='directory']" mode="link">
			<td style="width:80%"><a href="{@href}"><xsl:value-of select="@name"/></a></td>
		</xsl:template>
		
		<xsl:template match="item[@type='directory']" mode="icon">
			<td><img src="images/folder.png"/></td>
		</xsl:template>
		<xsl:template match="item[@type='text']" mode="icon">
			<td><img src="images/page.png"/></td>
		</xsl:template>
		<xsl:template match="item[@type='image']" mode="icon">
			<td><img src="images/image.png"/></td>
		</xsl:template>
		<xsl:template match="item[@type='html']" mode="icon">
			<td><img src="images/page_code.png"/></td>
		</xsl:template>
		
		<xsl:template match="page[@action='login']">
			<div style="background-color:#ddf;border-bottom:1px solid #ccc;padding:1px 4px;">
				<xsl:text>Представьтесь, Гость</xsl:text> <xsl:value-of select="@extra"/>
			</div>
			<form action="index.php?action=login" method="post">
			<xsl:if test="@error &gt; 0">
			<div style="width:60%; margin: 10px auto; border:1px solid #fbb;background-color:#fee;padding:1px 4px;text-align:center;">Что-то нет у нас такого пользователя c таким паролем.</div>
			</xsl:if>
			<table style="margin:auto;width:50%;text-align:center;padding-top:10px;">
				<tr><td>Логин:</td><td><input type="text" name="login" value="{@login}" style="border:1px solid #ccc"/></td></tr>
				<tr><td>Пароль:</td><td><input type="password" name="password" style="border:1px solid #ccc"/></td></tr>
				<tr><td colspan="2" style=""><a href="index.php?action=reg">Зарегистрироваться</a></td></tr>			
				<tr><td colspan="2" style=""><input type="submit" value="Войти"/></td></tr>			
			</table>
			</form>
		</xsl:template>
		<xsl:template match="page[@action='reg']">
			<div style="background-color:#ddf;border-bottom:1px solid #ccc;padding:1px 4px;">
				<xsl:text>Представьтесь, Гость</xsl:text> <xsl:value-of select="@extra"/>
			</div>
			<form action="index.php?action=reg" method="post">
			<xsl:apply-templates select="." mode="error"/>
			<table style="margin:auto;width:50%;text-align:center;padding-top:10px;">
				<tr><td>Логин:</td><td><input type="text" name="login" value="{@login}" style="border:1px solid #ccc"/></td></tr>
				<tr><td>Пароль:</td><td><input type="password" name="password" style="border:1px solid #ccc"/></td></tr>
				
				<tr><td>Домашняя папка:</td><td><input type="text" name="home" value="{@home}" style="border:1px solid #ccc"/></td></tr>
				
				<tr><td>Группа(1=admin):</td><td><input type="text" name="group" value="{@group}" style="border:1px solid #ccc"/></td></tr>
				
				<tr><td colspan="2" style=""><input type="submit" value="Зарегистрироваться"/></td></tr>			
			</table>
			</form>
		</xsl:template>
		<xsl:template match="page[@action='reg'][@error='1']" mode="error">
			<div style="width:60%; margin: 10px auto; border:1px solid #fbb;background-color:#fee;padding:1px 4px;text-align:center;">Ошибочка. Возможно такой пользователь уже есть.</div>
		</xsl:template>
		<xsl:template match="page[@action='reg'][@error='2']" mode="error">
			<div style="width:60%; margin: 10px auto; border:1px solid #fbb;background-color:#efe;padding:1px 4px;text-align:center;">Вы зарегистрированы.<a href="index.php?action=login">Вход</a></div>
		</xsl:template>
		
</xsl:stylesheet>