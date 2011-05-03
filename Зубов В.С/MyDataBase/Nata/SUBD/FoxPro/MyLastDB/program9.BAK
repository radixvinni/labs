Set DEFA TO c:\ALANsProgs\work\FoxPro\MyLastDB\
clear

&& 1. Самый простой пример использования SELECT
&& Вывод автомобилей, цена которых >100000$
SELECT firm AS "Производитель",title AS "Название",cena AS "Цена"; 
FROM table1 a WHERE a.cena>100000;
ORDER BY cena,firm,title

&& 2. Чуть сложнее с использованием групировки полей(GROUP BY)
&& Групировка по производителю и вывод суммарной цены за автомобили этой фирмы
SELECT table1.firm,Sum(table1.cena),table4.phone FROM table1,table4 GROUP BY table1.firm ORDER BY cena
SELECT firm AS "Производитель",Sum(cena) AS "Цена_за_все" FROM table1 GROUP BY firm ORDER BY cena

&& 3. С использованием двух таблиц и атрибута HAVING
&& (который работает только с атрибутом GROUP BY).
&& Вывод только отечественных автомобилей.
SELECT a.firm AS "Производитель",Sum(a.cena) AS "Цена_за_все",Count(a.title) AS "Количество_моделей";
,b.country AS "Страна_производитель" FROM table1 a,table4 b GROUP BY a.firm;
WHERE a.firm=b.firm HAVING b.country="Russia";
ORDER BY a.firm,b.country

&& 4. С использованием атрибута DISTINCT 
&& (предотвращающего вывод двух одинаковых строк)
&& Вывод фирм, авто которых представлены в БД
SELECT DISTINCT a.firm AS "Производитель_авто";
FROM table1 a,table4 b WHERE a.firm=b.firm;
ORDER BY a.firm

&& 5. Объединение таблицы сотрудников имеющих детей и не имеющих детей
&&  и таблицы детей "по вертикале" 
*SELECT b.firm; 
*FROM table1 c,table4 b where empty(b.firm=c.firm)
*SELECT a.firm,a.title;
*FROM table1 a UNION ()
*ORDER BY a.firm

*UNION SELECT child_name,child_date,"Ребенок"; 
*FROM table_children;

*SELECT title,firm FROM table1 UNION SELECT motortype FROM table3


&& 6. С выводом в новую таблицу, используя данные из двух таблиц
SELECT a.title,a.firm,a.cena,b.country;
FROM table1 a, table4 b where a.firm=b.firm INTO DBF table5;
ORDER BY cena
CLOSE DATABASES
SELECT * FROM table5 ORDER BY cena

&& 7. Пример использования "коррелированных выборок"
&& Вывод автомобилей, которые стоят выше среднего
SELECT a.firm AS "Фирма",a.title AS "Название",a.cena AS "Цена";
FROM table1 a WHERE a.cena>(SELECT Avg(b.cena) FROM table1 b);
ORDER BY a.cena

&& 8. Пример использования "квантора существования"
&& Вывод фирм, авто которых нет в БД
SELECT a.firm AS "Фирма", a.phone AS "Телефон",a.country AS "Страна_производитель";
FROM table4 a ORDER BY a.firm ;
WHERE NOT EXISTS (SELECT * FROM table1 b WHERE a.firm=b.firm)
