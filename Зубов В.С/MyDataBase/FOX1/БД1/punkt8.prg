CLEAR
SET DEFA TO H:\FOX1\БД1

SELECT 1
USE main AGAIN ALIAS toys
INDEX ON UPPER(firm_name) TO firm_indx


key_s =UPPER ("Nikki")
SEEK key_s
IF Found()
	? izdelie,tip,firm_name
	WAIT WINDOW firm_name+izdelie
ELSE 
	? "Такой игрушки в базе нет!"
	WAIT WINDOW 'Такой игрушки в базе нет!'
ENDIF
