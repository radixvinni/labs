&& Пример создание двухуровнего FOX-меню (PULLDOWN)
&& Пункты меню

&& Горизонтальные
DECLARE g_punct[3,2]
g_punct[1,1]="Вывод"
g_punct[2,1]="Сортировка"
g_punct[3,1]="Выход"
g_punct[1,2]="Вывод записей удволетворяющих условию"
g_punct[2,2]="Сортировка записей по заданному полю"
g_punct[3,2]="Выход"

&& Вертикальные
DECLARE v_1[2],v_2[4]
v_1[1]="Вывод мужчин"
v_1[2]="Вывод женщин"
v_2[1]="Сортировать по фамилии"
v_2[2]="Сортировать по дате рождения"
v_2[3]="Сортировать по должности"
v_2[4]="Сортировать по зарплате"

&& Активация меню
MENU BAR g_punct,3
MENU 1,v_1,2
MENU 2,v_2,4

&& Цикл меню
DO WHILE .T.
	READ MENU BAR TO i,j SAVE
	DO CASE
		
		CASE i=1
			DO CASE
			  CASE j=1		
				SELECT family_name AS "Фамилии",post AS "Должность";
				FROM table_employee a WHERE Upper(a.sex)="М";
				ORDER BY family_name
			  CASE j=2
			 	SELECT family_name AS "Фамилии",post AS "Должность";
				FROM table_employee a WHERE Upper(a.sex)="Ж";
				ORDER BY family_name,post
			ENDCASE
		
		CASE i=2
			DO CASE
			  CASE j=1		
				SELECT * FROM table_employee ORDER BY family_name
			  CASE j=2
			 	SELECT * FROM table_employee ORDER BY birthday
			  CASE j=3		
				SELECT * FROM table_employee ORDER BY post
			  CASE j=4
			 	SELECT * FROM table_employee ORDER BY pay			
			ENDCASE

		CASE i=3			
			EXIT
	ENDCASE
ENDDO
