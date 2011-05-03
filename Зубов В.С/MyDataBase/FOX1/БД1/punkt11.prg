SET DEFA TO H:\FOX1\БД1
&& Создадим вертикальное FOX-меню

DECLARE MyMenu[5]
MyMenu[1] = " Выбрать не московские фирмы "
MyMenu[2] = " Выбрать московские фирмы "
MyMenu[3] = " Выбрать все фирмы "
MyMenu[4] = "\-"
MyMenu[5] = " В\<ыход "

@ 0,0 MENU MyMenu,5 TITLE "Вертикальное меню" 

DO WHILE .T.  && т.е. пока не нажмем "Выход"
	READ MENU TO n SAVE
	DO CASE
		CASE n=1
			SELECT a.izdelie AS "Изделие", a.tip AS "тип",b.firm_name AS "Фирма";
			FROM main a, firm b WHERE ((a.izdelie_kl=b.izdelie_kl) AND NOT (b.firm_adr = "г.Москва"));
			ORDER BY a.izdelie 
		CASE n=2
			SELECT a.izdelie  AS "Изделие", a.tip AS "тип", b.firm_name AS "Фирма";
			FROM main a, firm b WHERE ((a.izdelie_kl=b.izdelie_kl) AND (b.firm_adr = "г.Москва"));
			ORDER BY a.izdelie
		CASE n=3
			SELECT a.izdelie AS "Изделие",a.tip AS "тип",b.firm_name AS "Фирма";
			FROM main a, firm b WHERE a.izdelie_kl=b.izdelie_kl;
			ORDER BY a.izdelie
		CASE n=5
			EXIT
	ENDCASE
ENDDO
