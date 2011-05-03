&& Создадим Б.Д. автомобили с полями фирма, название, цена, владелец, номер
CREATE DBF table_auto(firm C(10), title c(10), cena I(10), owner c(10), number c(6))

&& Добавим записи в созданную Б.Д.
INSERT INTO table_auto(firm,title,cena,owner,number) VALUES("Mitsubisy","Land Rover",;
238456,"Пахан","mm001m")
INSERT INTO table_auto(firm,title,cena,owner,number) VALUES("Pejo","206",;
35000,"Иванов","нт254в")
INSERT INTO table_auto(firm,title,cena,owner,number) VALUES("Жигули","21041",;
7000,"Сидоров","т485ет")
INSERT INTO table_auto(firm,title,cena,owner,number) VALUES("БЕЛАЗ","Самосвал",;
190000,"Петрович","кр2323ут")

CLOSE DATABASES
&& Выведем таблицу
SELECT * FROM table_auto ORDER BY title