SET DEFA TO D:\6sem\MyDataBase\lab1
&& Главное меню
DECLARE MainMenu[3,2]
MainMenu[1,1]="Техника"
MainMenu[2,1]="Фирма"
MainMenu[3,1]="Выход"
MainMenu[1,2]="Выбор продукции"
MainMenu[2,2]="Вывод продукции заданной фирмы"
MainMenu[3,2]="Выход"

&& "Подменю"
DECLARE Menu1[3], Menu2[3]
Menu1[1]="Вывод телевизоров"
Menu1[2]="Вывод видеокамер"
Menu1[3]="Вывод музыкальных центров"
Menu2[1]="Sony"
Menu2[2]="Panasonic"
Menu2[3]="JVC"

MENU BAR MainMenu,3
MENU 1,Menu1,3
MENU 2,Menu2,3

DO WHILE .T.
	READ MENU BAR TO i,j SAVE
	DO CASE
		CASE i=1
			DO CASE
			  CASE j=1		
               SELECT mname AS "Название", tipe AS "Тип", quantity AS "Количество", price AS "Цена", firm AS "Фирма", address AS "Адрес";
               FROM models, firms WHERE id_firm=f_id AND mname="Телевизор";
               ORDER BY firm
			  CASE j=2
               SELECT mname AS "Название", tipe AS "Тип", quantity AS "Количество", price AS "Цена", firm AS "Фирма", address AS "Адрес";
               FROM models, firms WHERE id_firm=f_id AND mname="Видеокамера";
               ORDER BY firm
              CASE j=3
               SELECT mname AS "Название", tipe AS "Тип", quantity AS "Количество", price AS "Цена", firm AS "Фирма", address AS "Адрес";
               FROM models, firms WHERE id_firm=f_id AND mname="Музыкальный центр";
               ORDER BY firm
			ENDCASE
		
		CASE i=2
			DO CASE
			  CASE j=1		
			   SELECT mname AS "Название", tipe AS "Тип", quantity AS "Количество", price AS "Цена";
               FROM models WHERE firm="Sony";
               ORDER BY mname
			  CASE j=2
			   SELECT mname AS "Название", tipe AS "Тип", quantity AS "Количество", price AS "Цена";
               FROM models WHERE firm="Panasonic";
               ORDER BY mname
			  CASE j=3
			   SELECT mname AS "Название", tipe AS "Тип", quantity AS "Количество", price AS "Цена";
               FROM models WHERE firm="JVC";
               ORDER BY mname
			ENDCASE
		CASE i=3			
			EXIT
	ENDCASE
ENDDO