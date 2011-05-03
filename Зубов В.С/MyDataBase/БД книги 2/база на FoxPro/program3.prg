    clear
    use placetable IN g again
    select g 
    LOCATE for room=2 and bookcase=1 and bookshelf=1
    x=place_cod
SET DEFA TO "D:\база на FoxPro"
use maintable AGAIN ALIAS main 
SET TEXTMERGE ON TO iform.txt WINDOW SHOW
\   книги хран€щиес€ в 2-й комнате в 1-м шкафу на 1-й полке
\
SCAN FOR place_cod==x
\ название книги <<book_name>>
\число томов <<numtoms>>,номер тома <<tom>>, число копий <<copies>> 
\
ENDSCAN
SET TEXTMERGE TO

             