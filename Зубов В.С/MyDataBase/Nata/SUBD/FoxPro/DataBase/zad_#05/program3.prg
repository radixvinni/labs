&& точный поиск в таблице по символьному аргументу
? " "
USE table_employee AGAIN
INDEX ON family_name TO f_name 			&& проиндексируем по имени

&& Вариант 1
key_=Padr("Хмырь",Len(family_name))	&& ключ поиска
SEEK key_								&& поиск
IF Found()
	 ?Recno(),family_name,name_,otchestvo
ELSE 
	?"  Нету c фамилией Хмырь"
ENDIF

&& Вариант 2
SET EXACT ON
key_="Иванов"
SEEK key_								&& поиск
DO WHILE (family_name=key_)
	 ?Recno(),family_name,name_,otchestvo
	 SKIP
ENDDO