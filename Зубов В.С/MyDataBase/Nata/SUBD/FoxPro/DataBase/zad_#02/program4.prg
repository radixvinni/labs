&& Связь 1:N с помощью BROWSE
&& В данном случае связь 1:3
USE table_address IN 1 AGAIN ALIAS addr
INDEX ON association1_1 TO ass1_1
SELECT 0
USE table_employee IN 0 AGAIN
SET RELATION TO association1_1 INTO addr

BROWSE NOEDIT TITLE "Рабочие" PARTITION 45 LEDIT;
FIELDS family_name:H="Фамилия",name_:H="Имя",;
otchestvo:H="Отчество",addr->cite:H="Город",;
addr->street:H="Улица",addr->house:H="Дом"