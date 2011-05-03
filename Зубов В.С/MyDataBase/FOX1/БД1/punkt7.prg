SET DEFA TO H:\FOX1\БД1

CLEAR
SELECT 1

WAIT WINDOW 'Индексируем по полям тип и цена'
Use main AGAIN ALIAS toys
INDEX ON tip+STR(price) TO compos_indx

BROWSE TITLE "Фильмы отсортированы по типу и цене"

SET ORDER TO

WAIT WINDOW 'Реализуем переключение индексов'

INDEX ON tip TO type_indx
INDEX ON STR(price) TO price_indx
INDEX ON izdelie TO izd_indx
USE main AGAIN ALIAS toys INDEX type_indx,price_indx,izd_indx

WAIT WINDOW 'Сортируем по типу'
SET ORDER TO 1
? "Текущая запись при индексировании по типу",Recno(),izdelie
BROWSE TITLE "Игрушки, проиндексированные по типу"

SET ORDER TO 2
? "Текущая запись при индексировании по цене",Recno(),izdelie
BROWSE TITLE "Игрушки, проиндексированные по цене"

SET ORDER TO 3
? "Текущая запись при индексировании по названию",Recno(),izdelie
BROWSE TITLE "Игрушки, проиндексированные по названию"

WAIT WINDOW 'Выполним быстрый поиск игрушки с названием кубик-рубик'
?
? "Выполним быстрый поиск фильма с названием кубик-рубик"
key_= "Кубик-рубик"
SEEK key_
IF Found()
	? izdelie ,firm_name,tip
	WAIT WINDOW izdelie+firm_name
ELSE 
	? "Такой игрушки  в базе нет!"
	WAIT WINDOW 'Такой игрушки в базе нет!'
ENDIF