    clear
    ? "Введите название таблицы которую вы бы хотели посмотреть"
    accept"a,b,c,d,e,f,g - " to tb
    use maintable IN a again
    use authortable IN b again
    use writingtable IN c again
    use publishingtable IN d again
    use genretable IN e again
    use imprinttowntable IN f again
    use placetable IN g again
    do case
    case tb == "a"
    select a
    case tb == "b" 
    select b
    case tb == "c"
    select c
    case tb == "d"
    select b
    case tb == "e"
    select e
    case tb == "f"
    select f
    case tb == "g"
    select g 
    otherwise
    ?"Неправельный ввод таблицы"
    endcase
    list all
    accept "Ведите название книги о которой выхотите получить информацию : " to naz
    ?"инфориация о книге:"
   select a
   LOCATE for book_name = naz
   ?"Название книги: ",book_name
   select c
   LOCATE for book_cod == a.mbook_cod  
   x=author_cod
   select b
   LOCATE for autor_cod == x
   ?"Авторы :", author
   select d
   LOCATE for publ_cod == a.publ_cod
   ?"Издательство:" ,publishing
   select a
   LOCATE for book_name = naz
   ?"дата издания:",imprintdat
   select f
   LOCATE for town_cod == a.town_cod
   ?"город где издана:",town
   select e
   LOCATE for genre_cod == a.genre_cod
   ?"жанр:",genre
   select a
   LOCATE for book_name = naz
   ?"чило томов:",numtoms
   ?"номер тома:",tom
   ?"количество таких книг:",copies
   select g 
    LOCATE for place_cod == a.place_cod
   ?"Где хранится:"
   ?"номер комнаты:",room
   ?"номер шкафа:"  ,bookcase
   ?"номер полки:"  ,bookshelf




