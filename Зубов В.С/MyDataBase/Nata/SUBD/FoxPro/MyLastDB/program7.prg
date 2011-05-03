clear
*? "Вбор автомовилей, которые заслужили популярность у уличных гонщиков"
*? "т.е. поиск в memo-поле comments по подстроке "STREET RAC"
*? "и вывод марок этих автомобилей."

Set DEFA TO c:\ALANsProgs\work\FoxPro\MyLastDB\
select 1
USE table1 AGAIN ALIAS main

&& Вывод
BROWSE NOEDIT TITLE "Undeground CARS";
FIELDS firm:H="Производитель",title:H="Марка",cena:H="Цена",;
massa:H="Масса авто",;
comments:H="Заметки" FOR Like("*STREET RAC*",Upper(comments))
&& Возврат к старой таблице
BROWSE
