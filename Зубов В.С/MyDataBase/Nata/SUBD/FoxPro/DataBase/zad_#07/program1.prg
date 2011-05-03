&& Выбор сотрудников мужчин занятых в первом проекте
&& т.е. поиск в memo-поле curent_works по подстроке "1-"?,
&& и вывод посещенных ими командировок.
USE table_employee AGAIN

SET FILTER TO (sex="м")				&& Установка фильтра мужчины

&& Вывод
BROWSE TITLE "Рабочие занятые в первом проекте";
FIELDS family_name:H="Фамилия",name_:H="Имя",;
otchestvo:H="Отчество",birthday:H="Дата рождения",;
missions:H="Командировки" FOR Like("*1-*",curent_works)
&& Возврат к старой таблице
BROWSE
