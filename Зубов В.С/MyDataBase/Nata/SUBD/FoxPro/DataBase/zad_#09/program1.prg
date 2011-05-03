&& 1. Самый простой пример использования SELECT
&& Вывод сотрудников с заработной платой > 20000
SELECT family_name,name_,otchestvo,pay; 
FROM table_employee a WHERE a.pay>1500;
ORDER BY family_name,name_,otchestvo

&& 2. Чуть сложнее с использованием групировки полей(GROUP BY)
&& Групировка по должностям и вывод суммарных заработных плат
SELECT post,Sum(pay) FROM table_employee GROUP BY post ORDER BY post

&& 3. С использованием двух таблиц и атрибута HAVING
&& (который работает только с атрибутом GROUP BY).
&& Вывод сотрудников: Ф.И.О., число детей данного сотрудника
SELECT family_name AS "Фамилия",name_ AS "Имя",otchestvo AS "Отчество";
,Count(child_name) AS "Количество_детей";
FROM table_employee a,table_children b GROUP BY a.birthday;
WHERE a.parent_=b.parent_ HAVING Count(child_name)>=2;
ORDER BY family_name,name_,otchestvo

&& 4. С использованием атрибута DISTINCT 
&& (предотвращающего вывод двух одинаковых строк)
&& Вывод сотрудников имеющих детей без повторения фамилий сотрудников
SELECT DISTINCT family_name AS "Фамилия";
FROM table_employee a,table_children b WHERE a.parent_=b.parent_;
ORDER BY family_name

&& 5. С использованием атрибута UNION
&& Объединение таблицы сотрудников имеющих детей и не имеющих детей
&&  и таблицы детей "по вертикале" 
SELECT name_,birthday,Iif(parent_>0,"Родитель  ","Неродитель");
FROM table_employee UNION SELECT child_name,child_date,"Ребенок"; 
FROM table_children;
ORDER BY 3 DESC,2,1

&& 6. С выводом в новую таблицу
&& Тот же пример 5
SELECT name_,birthday,Iif(parent_>0,"Родитель  ","Неродитель") AS "Статус";
FROM table_employee UNION SELECT child_name,child_date,"Ребенок"; 
FROM table_children INTO DBF table1;
ORDER BY 3 Desc,2,1
CLOSE DATABASES
SELECT * FROM table1 ORDER BY Статус DESC, birthday, name_

&& 7. Пример использования "коррелированных выборок"
&& Вывод Ф., даты рождения, должности и зарплаты сотрудников,
&& которые получают выше среднего для своей должности.
SELECT family_name AS "Фамилия",birthday AS "Дата_рождения",post AS "Должность",;
pay AS "Зарплата" FROM table_employee a WHERE pay>(SELECT Avg(pay) ;
FROM table_employee b WHERE a.post=b.post);
ORDER BY post,pay,family_name,birthday

&& 8. Пример использования "квантора существования"
&& Вывод Ф. и дат рождения бездетных сотрудников
SELECT family_name AS "Фамилия",birthday AS "Дата_рождения" ;
FROM table_employee a ORDER BY birthday,family_name ;
WHERE NOT EXISTS (SELECT * FROM table_children b WHERE a.parent_=b.parent_)

&& 9. Пример использования "подзапросов с множественным результатом" (ALL)
&& Вывод Ф. и дат рождения мужчин промоутеров получающих больше женьщин
SELECT family_name AS "Фамилия",birthday AS "Дата_рождения" ;
FROM table_employee a ORDER BY birthday WHERE Upper(sex)="М" AND post="промоутер";
AND pay> ALL(SELECT pay FROM table_employee b WHERE Upper(sex)="Ж") 

&& 10. Пример использования "подзапросов с множественным результатом" (ANY)
&& Получение оставшихся промоутеров мужчин из примера 9.
SELECT family_name AS "Фамилия",birthday AS "Дата_рождения" ;
FROM table_employee a ORDER BY birthday WHERE Upper(sex)="М" AND post="промоутер";
AND pay<= ANY(SELECT pay FROM table_employee b WHERE Upper(sex)="Ж") 

&& 11. Пример с использованием "функций пользователя" в SELECT
&& Выведем зарплаты сотрудников с премией равной 10% от з.п.
SELECT family_name,birthday,pay,F(pay) AS "З_п_с_премией" FROM table_employee
FUNCTION F
	PARAM pay,pay_next
	pay_next=pay+0.1*pay
RETURN pay_next