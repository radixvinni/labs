SET DEFA TO H:\FOX1\БД2

CLEAR
SELECT 1

WAIT WINDOW 'Индексируем по полям кинокомпанием и годам выпуска'
Use main AGAIN ALIAS films
INDEX ON cinema+STR(god) TO compos_indx

BROWSE TITLE "Фильмы отсортированы по кинокомпаниям и годам выпуска"

SET ORDER TO

WAIT WINDOW 'Реализуем переключение индексов'

INDEX ON cinema TO cin_indx
INDEX ON STR(god) TO god_indx
INDEX ON nazvanie TO naz_indx
USE main AGAIN ALIAS films INDEX cin_indx,god_indx,naz_indx

WAIT WINDOW 'Сортируем по кинокомпаниям'
SET ORDER TO 1
? "Текущая запись при индексировании по кинокомпании",Recno(),nazvanie
BROWSE TITLE "Фильмы, проиндексированные по кинокомпании"

SET ORDER TO 2
? "Текущая запись при индексировании по году выпуска",Recno(),nazvanie
BROWSE TITLE "Фильмы, проиндексированные по году издания"

SET ORDER TO 3
? "Текущая запись при индексировании по названию",Recno(),nazvanie
BROWSE TITLE "Фильмы, проиндексированные по названию"

WAIT WINDOW 'Выполним быстрый поиск фильма с названием "Жесть"'
?
? "Выполним быстрый поиск фильма с названием Жесть"
key_= "Жесть"
SEEK key_
IF Found()
	? nazvanie ,regesser,cinema
	WAIT WINDOW nazvanie+regesser
ELSE 
	? "Такого фильма в базе нет!"
	WAIT WINDOW 'Такого фильма в базе нет!'
ENDIF