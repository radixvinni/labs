<?php
	if(empty($_REQUEST['p'])){
		print file_get_contents('html.html');
		?><hr/><form>13. Поменять местами 2-ю и 4-ю строки таблицы, выделив текст полужирным и установив в новой 2-й строке желтый фон, а в 4-й - зеленый<br/><input type="submit" name="p" value="Преобразовать"/></form><?
	}
	else
	{
		$f=file_get_contents('html.html');
		//13. Поменять местами 2-ю и 4-ю строки таблицы, выделив текст полужирным и установив в новой 2-й строке желтый фон, а в 4-й - зеленый
		print preg_replace('/(<table[^>]*>[\n\r\s\S]*?<tr[^>]*>[\n\r\s\S]*?<\/tr>[\n\r\s\S]*?)<tr([^>]*>[\n\r\s\S]*?<\/tr>)([\n\r\s\S]*?<tr[^>]*>[\n\r\s\S]*?<\/tr>[\n\r\s\S]*?)<tr([^>]*>[\n\r\s\S]*?<\/tr>)/i','$1<tr style="font-weight:bold;background-color:yellow;" $4$3<tr style="font-weight:bold;background-color:green;" $2',$f);
		?><hr/><form><input type="submit" name="l" value="Назад"/></form><?
	}
?>