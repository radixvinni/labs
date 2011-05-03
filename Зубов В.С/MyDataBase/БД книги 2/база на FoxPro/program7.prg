  CLEAR
  SET DEFA TO "D:\база на FoxPro"
  && Выберем книги изданные с 2000 по 2007 годы
  SELECT book_name ,imprintdat  ;
  from maintable ;
  where imprintdat BETWEEN 2000 AND 2007 ORDER BY imprintdat
  &&AS"Год издания"AS "Название книги"

  && Выберем все произаедения, с группировав по авторам.
  SELECT writingtable.book_cod,writingtable.name1,writingtable.translat,genretable.genre,;
  authortable.author;
  FROM  writingtable,genretable,authortable;
  WHERE writingtable.genre_cod=genretable.genre_cod ;
  AND authortable.autor_cod=writingtable.author_cod;
  GROUP BY authortable.author;
  ORDER BY writingtable.book_cod ASC

  && Используем атрибут HAVING,выберем информацию о  Московских издательств.
  SELECT publishingtable.publishing,imprinttowntable.town;
  FROM  maintable,publishingtable,imprinttowntable;
  WHERE maintable.town_cod=imprinttowntable.town_cod ;
  AND maintable.publ_cod=publishingtable.publ_cod;
  GROUP BY publishingtable.publishing;
  HAVING imprinttowntable.town="Москва"

  && Используем атрибут DISTINCT
  SELECT DISTINCT maintable.book_name From maintable,placetable;
  WHERE maintable.place_cod=placetable.place_cod;
  ORDER BY maintable.book_name DESC

  && Создадим новую таблицу и заполним ее
  CREATE TABLE NewTable(book_name C(40),publishing C(20),town C(20),dat n)
  INSERT INTO NewTable(book_name,publishing,town,dat);
  VALUES ("Функциональный анализ","Наука","Москва",1989)
  INSERT INTO NewTable(book_name,publishing,town,dat);
  VALUES ("Теория вероятности","МИР","Москва",2001)
  INSERT INTO NewTable(book_name,publishing,town,dat);
  VALUES ("Ортогональные ряды","АФЦ","Москва",1999)
  INSERT INTO NewTable(book_name,publishing,town,dat);
  VALUES ("Вейвлеты в обработке сигналов","Мир","Москва",2005)
  CLOSE DATABASES
  Select* From NewTable 
