<?xml version="1.0" encoding="windows-1251"?>
 
<xsl:stylesheet version="1.0" 
		xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
        xmlns="http://www.w3.org/1999/xhtml">
    <xsl:output method="xml" indent="yes"
		encoding="windows-1251"
        doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN" 
        doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"/>
        <xsl:template match="response[@ajax='0']">
            <html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
            <head>
                <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
                <title>Лабораторная 3</title>
                <link rel="stylesheet" href="css/common.css"/>
				<link rel="stylesheet" href="css/ui-lightness/jquery-ui-1.8.16.custom.css"/>
				<script type="text/javascript" src="js/jquery-1.7.1.min.js"></script>
				<script type="text/javascript" src="js/jquery-ui-1.8.16.custom.min.js"></script>
				<script type="text/javascript" src="js/common.js"></script>
            </head>
            <body style="background-color:#fff;font: 11px Verdana;">
				<div class="ui-widget ui-widget-content ui-helper-clearfix ui-corner-all"
					 style="margin:100px auto 0; width:462px; padding: 0.3em;"
					 id="wrapper">
					<xsl:apply-templates />
				</div >
				<div style="width:100%; padding: 0.5em; text-align:center;">© 2011, A-14-07 Тестирование 2.0 | <a href="index.php">На главную</a> | <a href="index.php?action=logout">Выход</a><div style="margin:0.4em;"/><a href="http://jqueryui.com/"><img src="images/jquery-ui.png"/></a></div>
            </body>
			</html>
        </xsl:template>
		<xsl:template match="response[@ajax='1']">
			<done xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en"><xsl:apply-templates /></done>
        </xsl:template>
		<xsl:template match="response[@xml='1']">
			<xsl:copy-of select="."/>
        </xsl:template>
		
		<xsl:template match="page[@action='login']">
			<div class="ui-widget-header ui-corner-all">Представьтесь, пожалуйста</div>
			<form action="index.php?action=login" method="post">
				<xsl:apply-templates match="error"/>
				<table style="margin:auto;width:90%;text-align:center;padding-top:10px;">
					<tr><td>Логин:</td><td><input type="text" name="name" value="{login/@value}" style="border:1px solid #ccc"/></td></tr>
					<tr><td>Пароль:</td><td><input type="password" name="pass" style="border:1px solid #ccc"/></td></tr>
					<tr><td colspan="2"><input type="checkbox" id="reg" name="reg"></input><label for="reg">Зарегистрировать нового пользователя</label></td></tr>
					<tr><td colspan="2"><input type="submit" name="login" value="Войти"/></td></tr>			
				</table>
			</form>
		</xsl:template>
		<xsl:template match="page[@action='']">
			<div class="ui-widget-header ui-corner-all">
				<xsl:text>Добро пожаловать, </xsl:text>
				<xsl:value-of select="@username" />
			</div>
			<xsl:apply-templates />
		</xsl:template>
		
		<!--results.xsl-->
		<xsl:template match="results">
			<table id="results_{@id}" style="width: 100%;height: 3em;text-align: center;">
				<tr><xsl:apply-templates/></tr>
			</table>
		</xsl:template>
		<xsl:template match="image">
			<div id="diagram" style="text-align:center;"><img alt="{@percentage}% right" src="images/diag.php?p={@percentage}" /></div>
		</xsl:template>
		<xsl:template match="result[@is_correct='1']" >
			<td style="background-color:green;"><xsl:value-of select="position()"/></td>
		</xsl:template>
		<xsl:template match="result[@is_correct='0']">
			<td style="background-color:red;"><a href="#" title="{@errors}"><xsl:value-of select="position()"/></a></td>
		</xsl:template>
		
		
		<xsl:template match="resultset">
			<div class="ui-widget-header ui-corner-all">Просмотр результатов</div>
			<div class="test-results" id="test_{@id}"><xsl:apply-templates /></div>
			<div id="show-results"/>
		</xsl:template>
		<xsl:template match="u_user">
			<p class="ui-state-default ui-corner-all ui-helper-clearfix" style="padding:4px;">
				<span class="ui-icon ui-icon-person" style="float:left; margin:0 5px 0 0;"></span>
				<xsl:value-of select="@u_name"/>
			</p>
			<div id="user_{@u_user}" style="margin:10px">
				<xsl:apply-templates select="r_result" />
				<xsl:if test="count(NodeName) > 1"> 
					<button class="add-test-result">Допустить к повторному тестированию</button>
				</xsl:if>
				<xsl:apply-templates select="results" />
			</div>
		</xsl:template>
		<xsl:template match="r_result[@r_ended_timestamp!='']">
			<button class="get-test-result" id="result_{@r_result}">Результат тестирования</button>
		</xsl:template>
		<xsl:template match="r_result[@r_ended_timestamp='']">
			<button class="del-test-result">Остановить тестирование</button>
		</xsl:template>
		<xsl:template match="r_result[@r_result='']">
			<button class="add-test-result">Допустить к тестированию</button>
		</xsl:template>
		<xsl:template match="testing">
			<button class="testing" style="width:427px;margin:10px;" href="index.php?action=run&amp;id={@e_test}&amp;limit={@e_limit}">
				<xsl:value-of select="@e_test_name"/>
			</button>
		</xsl:template>
		<xsl:template match="//page[@group='9'][@action=''][count(//testing)=0]">
			Для вас тестов нет
		</xsl:template>
		
		<!--questions.xsl-->
		<xsl:template match="questions">
			<div id="modify">
			 <ul theme='{@id}'>
				<xsl:for-each select="q_question">
					<li><a href="#tab_{@q_question}"><xsl:value-of select="position()"/></a></li>
				</xsl:for-each>
				<li><a href="#tab-default" theme='{@id}' id="tab-add">+</a></li>
			 </ul>
			 <div id="tab-default">Добавьте первый вопрос в эту тему</div>
			 <xsl:apply-templates />
			</div>
		</xsl:template>
		<xsl:template match="//page[@action='run']//questions">
			<ul theme='{@id}'>
				<xsl:for-each select="q_question">
					<li><a href="#tab_{@q_question}"><xsl:value-of select="position()"/></a></li>
				</xsl:for-each>
				<li><a href="#tab-default" id="tab-end">Конец</a></li>
			</ul>
			<div id="tab-default" theme='{@id}'>
				<button id="check">Проверить ответы</button>
			</div>
			<div id="run"><xsl:apply-templates /></div>
		</xsl:template>
		<xsl:template match="q_question">
			<div class="question" id="tab_{@q_question}">
				<div class="qtypes" selected="{@q_type}" style="display:inline-block;">
					<input type="radio" id="qtype_{@q_question}_1" name="qtype_{@q_question}" value="1" class="qtype qtype_1"/><label for="qtype_{@q_question}_1">1 вар.</label>
					<input type="radio" id="qtype_{@q_question}_2" name="qtype_{@q_question}" value="2" class="qtype qtype_2"/><label for="qtype_{@q_question}_2">N вар.</label>
					<input type="radio" id="qtype_{@q_question}_3" name="qtype_{@q_question}" value="3" class="qtype qtype_3"/><label for="qtype_{@q_question}_3">Сортировка</label>
					<input type="radio" id="qtype_{@q_question}_4" name="qtype_{@q_question}" value="4" class="qtype qtype_4"/><label for="qtype_{@q_question}_4">1 к 1</label>
					<input type="radio" id="qtype_{@q_question}_5" name="qtype_{@q_question}" value="5" class="qtype qtype_5"/><label for="qtype_{@q_question}_5">1 к N</label>
					<input type="radio" id="qtype_{@q_question}_6" name="qtype_{@q_question}" value="6" class="qtype qtype_6"/><label for="qtype_{@q_question}_6">N к M</label>
				</div>
				<button class="delete_question">Удалить вопрос</button>
				<div class="question_text ui-corner-all">
					<xsl:value-of select="@q_text"/>
				</div>
				<div class="question_answers">
					<xsl:apply-templates select="." mode="answers"/>
				</div>
			</div>
		</xsl:template>
		<xsl:template match="//page[@action='admin_modify_type']//q_question">
			<xsl:apply-templates select="." mode="answers"/>
		</xsl:template>
		<xsl:template match="//page[@action='run']//q_question">
			<div class="question" id="tab_{@q_question}">
				<div class="question_text ui-corner-all"><xsl:value-of select="@q_text"/></div>
				<div class="question_answers"><xsl:apply-templates select="." mode="answers"/></div>
				<q_question q_question="{@q_question}" q_type="{@q_type}"/>
			</div>
		</xsl:template>
		<xsl:template match="q_question[@q_type &lt; 4]" mode="answers">
			<div class="ui-widget ui-widget-content ui-helper-clearfix ui-corner-all"
				 style="padding: 0.3em;width:300px;margin:10px auto;">
				<div class="answers-sortable" q_type="{@q_type}" a_type="1" q_correct="{@q_correct_answer}"><xsl:apply-templates/></div>
				<div class="ui-corner-all answer-add" type="1" question="{@q_question}" q_type="{@q_type}"><i>Добавить ответ</i></div>
			</div>
		</xsl:template>
		<xsl:template match="q_question[@q_type &gt; 3]" mode="answers">
			<div class="ui-widget ui-widget-content ui-helper-clearfix ui-corner-all"
				 style="padding: 0.3em;width:180px;float:left;margin:10px;">
				<div class="answers-sortable" q_type="{@q_type}" a_type="1"><xsl:apply-templates select="a_answer[@a_type='1']"/></div>
				<div class="answer-add ui-widget-header ui-corner-all" type="1" question="{@q_question}" q_type="{@q_type}">
					<i style="font-weight: normal;">Добавить ответ</i>
				</div>
			</div>
			<div class="ui-widget ui-widget-content ui-helper-clearfix ui-corner-all"
				 style="padding: 0.3em;width:180px;float:left;margin:10px;">
				<div class="answers-sortable answers-draggable" q_type="{@q_type}" a_type="2" id="c{@q_question}_0" style="padding:0.4em;">
					<xsl:apply-templates select="a_answer[@a_type='2']"/>
				</div>
				<div class="ui-corner-all answer-add" type="2" question="{@q_question}" q_type="{@q_type}"><i>Добавить ответ</i></div>
			</div>
		</xsl:template>
		<xsl:template match="//*[@q_type='1']//a_answer[@a_type='1']">
			<div class="ui-corner-all answer" id="answer_{@a_answer}">
				<input type="radio" id="radio_{@a_answer}" name="sel_{../@q_question}" class="radio_answer"/>
				<label for="radio_{@a_answer}"><xsl:value-of select="@a_text" /></label>
				<a class='test-state-close ui-corner-all'><span class='ui-icon ui-icon-close'></span></a>
			</div>
		</xsl:template>
		<xsl:template match="//*[@q_type='2']//a_answer[@a_type='1']">
			<div class="ui-corner-all answer" id="answer_{@a_answer}">
				<input type="checkbox" id="check_{@a_answer}" name="sel_{@a_answer}" class="check_answer"/>
				<label for="check_{@a_answer}"><xsl:value-of select="@a_text" /></label>
				<a class='test-state-close ui-corner-all'><span class='ui-icon ui-icon-close'></span></a>
			</div>
		</xsl:template>
		<xsl:template match="//*[@q_type='3']//a_answer[@a_type='1']">
			<div class="ui-corner-all answer" id="answer_{@a_answer}">
				<span><xsl:value-of select="@a_text" /></span>
				<a class='test-state-close ui-corner-all'><span class='ui-icon ui-icon-close'></span></a>
			</div>
		</xsl:template>
		<xsl:template match="//*[@q_type='4']//a_answer[@a_type='1']">
			<div id="answer_{@a_answer}" class="answer ui-widget ui-widget-content ui-helper-clearfix ui-corner-all"
				 style="padding: 0.3em;">
					<div class="ui-widget-header ui-corner-all"><xsl:value-of select="@a_text"/>
						<a class='test-state-close ui-corner-all'><span class='ui-icon ui-icon-close'></span></a>
					</div>
					<div class="answers-draggable only-one-child" id="sort_{@a_answer}" style="padding:0.4em;height:21px;overflow:hidden;">
					</div>
			</div>
		</xsl:template>
		<xsl:template match="//*[@q_type &gt; 4]//a_answer[@a_type='1']">
			<div id="answer_{@a_answer}" class="answer ui-widget ui-widget-content ui-helper-clearfix ui-corner-all"
				 style="padding: 0.3em;">
					<div class="ui-widget-header ui-corner-all"><xsl:value-of select="@a_text"/>
						<a class='test-state-close ui-corner-all'><span class='ui-icon ui-icon-close'></span></a>
					</div>
					<div class="answers-draggable" id="sort_{@a_answer}" q_type="{@q_type}" style="padding:0.4em;">
					</div>
			</div>
		</xsl:template>
		<xsl:template match="//*[@q_type &gt; 3]//a_answer[@a_type='2']">
			<div class="ui-corner-all answer" id="answer_{@a_answer}" _id="answer_{@a_answer}">
				<span ><xsl:value-of select="@a_text" /></span>
				<a class='test-state-close ui-corner-all'><span class='ui-icon ui-icon-close'></span></a>
			</div>
		</xsl:template>
		<xsl:template match="//page[@action='run']//q_question[@q_type &lt; 4]" mode="answers">
			<div class="ui-widget ui-widget-content ui-helper-clearfix ui-corner-all"
				 style="padding: 0.3em;width:300px;margin:10px auto;">
				<div class="answers-sortable" q_type="{@q_type}" a_type="1"><xsl:apply-templates/></div>
			</div>
		</xsl:template>
		<xsl:template match="//page[@action='run']//q_question[@q_type &gt; 3]" mode="answers">
			<div class="ui-widget ui-widget-content ui-helper-clearfix ui-corner-all"
				 style="padding: 0.3em;width:180px;float:left;margin:10px;">
				<div class="answers-sortable" q_type="{@q_type}" a_type="1"><xsl:apply-templates select="a_answer[@a_type='1']"/></div>
			</div>
			<div class="ui-widget ui-widget-content ui-helper-clearfix ui-corner-all"
				 style="padding: 0.3em;width:180px;float:left;margin:10px;">
				<div class="answers-sortable answers-draggable" q_type="{@q_type}" a_type="2" id="c{@q_question}_0" style="padding:0.4em;">
					<xsl:apply-templates select="a_answer[@a_type='2']"/>
				</div>
			</div>
		</xsl:template>
		<xsl:template match="//page[@action='run']//q_question[@q_type='1']//a_answer[@a_type='1']">
			<div class="ui-corner-all answer" id="answer_{@a_answer}">
				<input type="radio" id="radio_{@a_answer}" name="sel_{../@q_question}" class="radio_answer"/>
				<label for="radio_{@a_answer}"><xsl:value-of select="@a_text" /></label>
			</div>
		</xsl:template>
		<xsl:template match="//page[@action='run']//q_question[@q_type='2']//a_answer[@a_type='1']">
			<div class="ui-corner-all answer" id="answer_{@a_answer}">
				<input type="checkbox" id="check_{@a_answer}" name="sel_{@a_answer}" class="check_answer"/>
				<label for="check_{@a_answer}"><xsl:value-of select="@a_text" /></label>
			</div>
		</xsl:template>
		<xsl:template match="//page[@action='run']//q_question[@q_type='3']//a_answer[@a_type='1']">
			<div class="ui-corner-all answer" id="answer_{@a_answer}"><xsl:value-of select="@a_text" /></div>
		</xsl:template>
		<xsl:template match="//page[@action='run']//q_question[@q_type='4']//a_answer[@a_type='1']">
			<div id="answer_{@a_answer}" class="ui-widget ui-widget-content ui-helper-clearfix ui-corner-all"
				 style="padding: 0.3em;">
					<div class="ui-widget-header ui-corner-all"><xsl:value-of select="@a_text"/></div>
					<div class="answers-draggable only-one-child" id="sort_{@a_answer}" style="padding:0.4em;height:21px;overflow:hidden;"></div>
			</div>
		</xsl:template>
		<xsl:template match="//page[@action='run']//q_question[@q_type &gt; 4]//a_answer[@a_type='1']">
			<div id="answer_{@a_answer}" class="ui-widget ui-widget-content ui-helper-clearfix ui-corner-all"
				 style="padding: 0.3em;">
					<div class="ui-widget-header ui-corner-all"><xsl:value-of select="@a_text"/></div>
					<div class="answers-draggable" id="sort_{@a_answer}" q_type="{@q_type}" style="padding:0.4em;"></div>
			</div>
		</xsl:template>
		<xsl:template match="//page[@action='run']//q_question[@q_type &gt; 3]//a_answer[@a_type='2']">
			<div class="ui-corner-all answer" id="answer_{@a_answer}" _id="answer_{@a_answer}"><xsl:value-of select="@a_text" /></div>
		</xsl:template>
		<xsl:template match="solutions">
			<xsl:copy-of select="."/>
		</xsl:template>
		
		<!--categories.xsl-->
		<xsl:template match="categories">
			<div class="menu">
				<button id="run">Начать</button>
				<div id="slider" style="width:40%;display:inline-block;margin: 0 10px;"></div>
				<div id="amount" style="border:0; color:#f6931f; font-weight:bold;display:inline-block;" >0</div>
			</div>
			<div style="width: 200px; float: left; padding: 10px;">
				<div id="cats-sortable">
					<xsl:apply-templates />
				</div>
				<div id="cat-add" class="ui-widget ui-widget-content ui-helper-clearfix ui-corner-all"
					 style="padding: 0.3em;">
					<div id="cat-add-header" class="ui-widget-header ui-corner-all"><i style="font-weight: normal;">Добавить предмет</i></div>
				</div>
			</div>
		</xsl:template>
		<xsl:template match="tests">
			<div style="width: 200px; float: left; padding: 10px;">
				<div class="ui-widget ui-widget-content ui-helper-clearfix ui-corner-all"
					 style="padding: 0.3em;">
					<div id="tests-sortable">
						<xsl:apply-templates />
					</div>
					<div class="ui-corner-all test-add"><i>Добавить тест</i></div>
				</div>
			</div>
		</xsl:template>
		<xsl:template match="c_category">
				<div id="cat_{@c_category}" class="ui-widget ui-widget-content ui-helper-clearfix ui-corner-all"
					 style="padding: 0.3em;">
					<div class="ui-widget-header ui-corner-all"><xsl:value-of select="@c_category_name"/><a class='test-state-close ui-corner-all'><span class='ui-icon ui-icon-close'></span></a></div>
					<div id="catcontent_{@c_category}" class="themes-sortable">
						<xsl:apply-templates />
					</div>
					<div class='ui-corner-all theme-add'><i>Добавить тему</i></div>
				</div>
		</xsl:template>
		<xsl:template match="t_theme[@t_theme!='']">
			<div class="ui-corner-all theme" id="theme_{@t_theme}">
				<input type="checkbox" id="check_{@t_theme}" name="check_{@t_theme}" class="check_theme" style="float:left;" count="{@t_count}"/>
				<label for="check_{@t_theme}" style="float:left;"><xsl:value-of select="@t_theme_name" /></label>
				<a class='test-state-close ui-corner-all'><span class='ui-icon ui-icon-close'></span></a>
				<a class='test-state-modify ui-corner-all'><span class='ui-icon ui-icon-wrench'></span></a>
			</div>
		</xsl:template>
		<xsl:template match="t_theme[@tt_theme!='']" mode="quiet">
			<theme theme="{@tt_theme}" link_id="{@tt_id}" test="{@tt_test}"/>
		</xsl:template>
		<xsl:template match="e_test">
			<div class="ui-corner-all test" id="test_{@e_test}">
				<input type="radio" name="current_test" id="radio_{@e_test}" class="radio_theme" style="float:left;" limit="{@e_limit}"/>
				<label for="radio_{@e_test}" style="float:left;"><xsl:value-of select="@e_test_name" /></label>
				<a class="test-state-close ui-corner-all"><span class='ui-icon ui-icon-close'></span></a>
				<a class='test-state-stat ui-corner-all'><span class='ui-icon ui-icon-contact'></span></a>
				<xsl:apply-templates mode="quiet"/>
			</div>
		</xsl:template>
		
		<xsl:template match="error">
			<div class="ui-state-error ui-corner-all" style="width:60%; margin: 10px auto; padding:1px 4px;text-align:center;">Произошла ошибка при попытке входа</div>
		</xsl:template>
		<xsl:template match="message">
			<div class="ui-state-highlight ui-corner-all" style="width:60%; margin: 10px auto; padding:1px 4px;text-align:center;">Регистрация прошла успешно.<a href="index.php"> Список доступных тестов</a></div>
		</xsl:template>
		
		
</xsl:stylesheet>