CLEAR
SET DEFA TO "D:\база на FoxPro"
SELECT 1

WAIT WINDOW 'Индексируем по полям год издания и число копий'
USE maintable Again
INDEX ON STR((imprintdat)+(copies) ) TO first_indx ASCENDING 
&&STR (<ВырN > [,<ВырN > [,<Кол-во>]]) 
&&INDEX ON STR(imprintdat)+copies TO first_indx
BROWSE TITLE "КНИГИ ОТСОРТИРОВАННЫ ПО ГОДУ ИЗДАНИЯ И ЧИСЛУ КОПИЙ "
SET ORDER TO

WAIT WINDOW 'Ркализуем переключение индексов'

INDEX ON STR(imprintdat)TO printdat_indx
INDEX ON copies TO copi_indx
INDEX ON book_name TO name_indx
USE maintable AGAIN INDEX printdat_indx,copi_indx,name_indx

WAIT WINDOW 'Сортируем по дате издания'
SET ORDER TO 1
?"Текущая запись при индексированиии по дате издания",Recno(),book_name
BROWSE TITLE "Книги, индексированные по дате издания"

SET ORDER TO 2
?"Текущая запись при индексированиии по числу копий",Recno(),book_name
BROWSE TITLE "Книги, индексированные по числу копий"

SET ORDER TO 3
?"Текущая запись при индексированиии по названию книги",Recno(),book_name
BROWSE TITLE "Книги, индексированные по названию книги"


 