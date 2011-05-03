SET DEFA TO H:\FOX1\БД2\
&& Создадим двухуровневое меню
&& "Горизонтальное" меню
DECLARE MainMenu[3,2]
MainMenu[1,1]="Выборка"
MainMenu[2,1]="Сортировать по..."
MainMenu[3,1]="В\<ыход"
MainMenu[1,2]="Вывод записей удовлетворяющих условию"
MainMenu[2,2]="Сортировка записей по заданному полю"
MainMenu[3,2]="Выход"

&& "Вертикальные меню"
DECLARE Menu1[2], Menu2[3]
Menu1[1]="Вывод российских книг"
Menu1[2]="Вывод книг зарубежных авторов"
Menu2[1]="Сортировать по названию"
Menu2[2]="Сортировать по режиссеру"
Menu2[3]="Сортировать по издательству"

&& Активация меню
MENU BAR MainMenu,3
MENU 1,Menu1,2
MENU 2,Menu2,3

&& Цикл меню
DO WHILE .T.
	READ MENU BAR TO i,j SAVE
	DO CASE
		
		CASE i=1
			DO CASE
			  CASE j=1		
               SELECT a.nazvanie AS "Название",a.regesser AS "режиссер", b.country AS "Страна";
               FROM main a, regeser_info b WHERE a.regesser_id=b.regesser_id AND b.country="Россия";
               ORDER BY a.nazvanie
			  CASE j=2
               SELECT a.nazvanie AS "Название",a.regesser AS "режиссер", b.country AS "Страна";
               FROM main a, regeser_info b WHERE ((a.regesser_id=b.regesser_id) AND NOT (b.country="Россия"));
               ORDER BY a.nazvanie
			ENDCASE
		
		CASE i=2
			DO CASE
			  CASE j=1		
				SELECT * FROM main ORDER BY nazvanie
			  CASE j=2
			 	SELECT * FROM main ORDER BY regesser
			  CASE j=3
			 	SELECT * FROM main ORDER BY cinema			 	
			ENDCASE

		CASE i=3			
			EXIT
	ENDCASE
ENDDO
