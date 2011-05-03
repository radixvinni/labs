&& Пример создание двухуровнего FOX-меню

&& Горизонтальные
DECLARE g_menu[3,2]
g_menu[1,1]="Выборка"
g_menu[2,1]="Выстроить по..."
g_menu[3,1]="В\<ыход"
g_menu[1,2]="Вывод записей удволетворяющих условию"
g_menu[2,2]="Сортировка записей по заданному полю"
g_menu[3,2]="Выход"

&& Вертикальные
DECLARE v_menu1[2],v_menu2[3]
v_menu1[1]="Вывод отечественные автомобили"
v_menu1[2]="Вывод инномарок"
v_menu2[1]="Выстроить по названию"
v_menu2[2]="Выстроить по марке"
v_menu2[3]="Выстроить по цене"
*v_2[4]="Сортировать по зарплате"

&& Активация меню
MENU BAR g_menu,3
MENU 1,v_menu1,2
MENU 2,v_menu2,3

&& Цикл меню
DO WHILE .T.
	READ MENU BAR TO i,j SAVE
	DO CASE
		
		CASE i=1
			DO CASE
			  CASE j=1		
               SELECT a.title AS "Название",a.firm AS "Марка",b.country AS "Страна_производитель";
               FROM table1 a,table4 b WHERE ((a.firm=b.firm)and(Upper(b.country)="RUSSIA"));
               ORDER BY a.title
			  CASE j=2
               SELECT a.title AS "Название",a.firm AS "Марка",b.country AS "Страна_производитель";
               FROM table1 a,table4 b WHERE ((a.firm=b.firm)and(Upper(b.country)!="RUSSIA"));
               ORDER BY a.title
			ENDCASE
		
		CASE i=2
			DO CASE
			  CASE j=1		
				SELECT * FROM table1 ORDER BY title
			  CASE j=2
			 	SELECT * FROM table1 ORDER BY firm
			  CASE j=3		
				SELECT * FROM table1 ORDER BY cena
			ENDCASE

		CASE i=3			
			EXIT
	ENDCASE
ENDDO
