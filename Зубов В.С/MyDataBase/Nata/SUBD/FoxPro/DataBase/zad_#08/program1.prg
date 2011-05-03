&& Создаем сложные индекс файл, например, Фамилия + дата рождения
SET DATE BRITISH
USE table_employee AGAIN
INDEX ON Upper(family_name)+Dtoc(birthday) TO fdate
BROWSE TITLE "Сотрудники отсортированные по индексу;
 Фамилия+дата(число) рождения"
SET ORDER TO												&& снять индексацию

&& Реализуем переключение индексов
INDEX ON Upper(family_name) TO fam
INDEX ON Upper(name_) TO nam
INDEX ON Upper(otchestvo) TO otc
USE table_employee AGAIN INDEX fam,nam,otc
SET ORDER TO 1
? "Текущая запись при индексировании по фамилии",Recno(),family_name
BROWSE TITLE "Сотрудники проиндексированные по Фамилии"

SET ORDER TO 2
? "Текущая запись при индексировании по имени",Recno(),family_name
BROWSE TITLE "Сотрудники проиндексированные по Имени"

SET ORDER TO 3
? "Текущая запись при индексировании по отчеству",Recno(),family_name
BROWSE TITLE "Сотрудники проиндексированные по Отчеству"

&& Выполним быстрый поиск сотрудника с отчеством Петрович
key_=Upper("Петрович")
SEEK key_
IF Found()
	? family_name,name_,otchestvo
ELSE 
	? "С отчеством Петрович записи не существует"
ENDIF
BROWSE