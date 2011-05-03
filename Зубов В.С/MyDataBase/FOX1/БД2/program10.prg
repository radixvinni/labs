SET DEFA TO C:\Documents and Settings\Елена\Рабочий стол\учеба\FOX1\БД2

CLEAR
SELECT 1

USE main AGAIN ALIAS films
DEFINE WINDOW New FROM 1,1 TO 30,100 SYSTEM CLOSE FLOAT GROW MINIMIZE ZOOM
SHOW WINDOW New

&& Пример использования EDIT
EDIT FIELDS nazvanie:20:R:H="Название",regesser:10:R:H="режиссер";
FOR regesser="Бессон";
FONT 'Verdana',10 STYLE 'B' PARTITION 40 LEDIT TITLE "Фильмы Бессона" IN New

&& Пример использования BROWSE
BROWSE FIELDS nazvanie:20:R:H="Название",god:10:R:H="Год",;
regesser:10:R:H="Режиссер" FOR god=2005;
STYLE 'B' Title "Фильмы 2005 года" IN New

HIDE WINDOW New
BROWSE
