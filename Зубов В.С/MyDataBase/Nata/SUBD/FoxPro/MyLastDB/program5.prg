&& точный поиск в таблице по символьному аргументу
Set DEFA TO c:\ALANsProgs\work\FoxPro\MyLastDB\
clear
select 1

use table1 IN 1 AGAIN alias main
*INDEX ON number TO main_indx            && проиндексируем по имени

SELECT 2
USE table3 AGAIN alias car_param1

SELECT 3
USE table4 AGAIN alias car_firm
INDEX ON firm TO firm_ind

&& Вариант 1
key_=Padr("AZLK",Len(firm))	&& ключ поиска
SEEK key_								&& поиск
IF Found()
	 ?Recno(),firm,main->title,car_param1->motortype
ELSE 
	?"  Нет c машин с AZLK"
ENDIF

&& Вариант 2
SET EXACT ON
key_=Padr("Nissan",Len(firm))	&& ключ поиска
SEEK key_								&& поиск
DO WHILE (firm=key_)
	 ?Recno(),firm,main->title,car_param1->motortype
	 SKIP
ENDDO