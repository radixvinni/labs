Set DEFA TO c:\ALANsProgs\work\FoxPro\MyLastDB\
&& Пример создание вертикального FOX-меню
DECLARE munu1[5]

munu1[1]=" Выбрать \<отечественные автомобили "
munu1[2]=" Выбрать \<инномарки "
munu1[3]=" Выбрать \<все "
munu1[4]="\-"
munu1[5]=" В\<ыход"

@ 0,0 MENU munu1,5 TITLE "Вертикальное меню" 

DO WHILE .T.
	READ MENU TO n SAVE
	DO CASE
		CASE n=1
			SELECT a.title AS "Название",a.firm AS "Марка",b.country AS "Страна_производитель";
			FROM table1 a,table4 b WHERE ((a.firm=b.firm)and(Upper(b.country)="RUSSIA"));
			ORDER BY a.title
		CASE n=2
			SELECT a.title AS "Название",a.firm AS "Марка",b.country AS "Страна_производитель";
			FROM table1 a,table4 b WHERE ((a.firm=b.firm)and(Upper(b.country)!="RUSSIA"));
			ORDER BY a.title
		CASE n=3
			SELECT a.title AS "Название",a.firm AS "Марка",b.country AS "Страна_производитель";
			FROM table1 a,table4 b WHERE (a.firm=b.firm);
			ORDER BY a.title
		CASE n=5
			EXIT
	ENDCASE
ENDDO