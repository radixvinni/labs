&& Пример создание вертикального FOX-меню (POPUP)
&& Пункты меню
DECLARE puncts[5]
puncts[1]="Выбрать \<инженеров"
puncts[2]="Выбрать \<другие спецальности(кроме инженеров)"
puncts[3]="Выбрать \<всех"
puncts[4]="\-"
puncts[5]="В\<ыход"

&& Активация меню
@ 0,0 MENU puncts,5 TITLE "POPUP меню" 

&& Цикл меню
DO WHILE .T.
	READ MENU TO n SAVE
	DO CASE
		CASE n=1
			SELECT family_name AS "Фамилии",post AS "Должность";
			FROM table_employee a WHERE Upper(a.post)="ИНЖЕНЕР";
			ORDER BY family_name
		CASE n=2
			SELECT family_name AS "Фамилии",post AS "Должность";
			FROM table_employee a WHERE Upper(a.post)!="ИНЖЕНЕР";
			ORDER BY family_name,post
		CASE n=3
			SELECT family_name AS "Фамилии",post AS "Должность";
			FROM table_employee ORDER BY family_name,post
		CASE n=5
			EXIT
	ENDCASE
ENDDO