CLEAR
SET DEFA TO H:\FOX1\БД1

&& 1 Выберем игрушки, с ценой между 500 и 1800 рублями
SELECT izdelie AS "Изделие",firm_name AS "фирма", price AS "цена" FROM main;
WHERE price BETWEEN 500 AND 1800 ORDER BY izdelie

&& 2 Выпишем все фирмы и количество их игрушек, сгруппировав по фирмам 
SELECT firm.firm_name, firm.firm_adr, Sum(firm.assortiment),;
tip.tip FROM firm, tip;
WHERE firm.izdelie_kl=firm.izdelie_kl AND firm.izdelie_kl=tip.izdelie_kl;
GROUP BY firm.firm_name;
ORDER BY firm.firm_name ASC


&& 3 Используем атрибут HAVING, выберем информацию о раменских фирмах
SELECT main.izdelie AS "Изделие", main.firm_name AS "Фирма",;
COUNT(main.assortiment) AS "Количество игрушек",  firm.firm_adr AS "г.Раменское" FROM main, firm;
WHERE main.izdelie_kl = firm.izdelie_kl;
GROUP BY  main.izdelie;
HAVING firm.firm_adr = "г.Раменское" 

 

&& 4 Используем атрибут DISTINCT
SELECT DISTINCT firm.firm_name AS "Фирмы" FROM  firm, tip;
WHERE firm.izdelie_kl = tip.izdelie_kl ORDER BY firm.firm_name DESC

&& 5 Считаем средние значения
SELECT firm.firm_name AS "фирма",Sum(firm.assortiment) AS "количество";
FROM firm  WHERE firm.assortiment > (SELECT AVG(main.assortiment);
FROM main) ORDER BY firm.firm_name DESC

&& 6 Выведем данные в новую таблицу
SELECT a.firm_name, b.izdelie, c.firm_adr FROM;
main a, izdelie b, firm c WHERE a.izdelie_kl = b.izdelie_kl;
AND b.izdelie_kl = c.izdelie_kl INTO DBF NewTable ORDER BY c.firm_adr DESC
CLOSE DATABASES
SELECT * FROM NewTable

&&Создадим новую таблицу и заполним ее 
CREATE DBF TestBase( izdelie C(30), firm_name C(50),tip C(50))
INSERT INTO TestBase (izdelie, firm_name, tip);
VALUES ("Пазл","Nikki","настольные игры")
INSERT INTO TestBase (izdelie, firm_name, tip);
VALUES ("Шахматы","Hallmark","настольные игры")
INSERT INTO TestBase (izdelie, firm_name, tip);
VALUES ("Кукла","Sunny","куклы")
INSERT INTO TestBase (izdelie, firm_name, tip);
VALUES ("Танк","Hallmark","механические")
CLOSE DATABASES
SELECT * FROM TestBase ORDER BY izdelie
