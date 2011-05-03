SET DATE TO BRITISH 									 && Установка даты DD/MM/YY
&& Имется 4 таблицы: Рабочие, Адреса, Дети, Садик
&& Выведем Рабочих дети которых ходят в садик, их 
&& адреса и имена этих детей в окно BROWSE
SELECT 2
USE table_address IN 2 AGAIN ALIAS addr          		 && Откроем таблицу адресов во 2 обл.
INDEX ON association_adr TO ass_adr             		 && Теперь проиндексируем табл. адресов

SELECT 3
USE table_sadik IN 3 AGAIN ALIAS sadik			 		 && Откроем таблицу садик в 3 обл.
INDEX ON association_sadik TO ass_sadik          		 && Теперь проиндексируем табл. садик

SELECT 4
USE table_children IN 4 AGAIN ALIAS child        		 && Откроем таблицу детей во 4 обл.
INDEX ON association_child TO ass_child          		 && Теперь проиндексируем табл. детей

SELECT 1										 		 && Перейдем в 1 рабочую обл.
USE table_employee AGAIN					 		 	 && Откроем табл. рабочих в 1 обл.
SET RELATION TO association_adr INTO addr		         && Свяжем табл. рабочих с табл. адресов
SET RELATION TO association_child INTO child ADDITIVE	 && Свяжем табл. рабочих с табл. детей
SET RELATION TO association_sadik INTO sadik ADDITIVE	 && Свяжем табл. рабочих с табл. садик

SET FILTER TO (association_sadik!=0)

BROWSE TITLE "Рабочие" FIELDS family_name:H="Фамилия",;
name_:H="Имя",addr->cite=Iif(addr->cite!=" ",addr->cite,;
"Не прописан"):H="Город",addr->street:H="Улица",;
addr->house:H="Дом",child->children_1=Iif(sadik->;
child_1_insert,child->children_1+" ходит",;
"Неходит"):23:H="1-ый ребенок",child->children_2=;
Iif(sadik->child_2_insert,child->children_2;
+" ходит","Неходит"):23:H="2-ой ребенок",child->;
children_3=Iif(sadik->child_3_insert,child->children_3;
+" ходит","Неходит"):23:H="3-ий ребенок"

