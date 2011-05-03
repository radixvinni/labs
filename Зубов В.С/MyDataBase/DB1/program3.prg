&& Пункт 10
CLEAR
SET DEFA TO D:\6sem\MyDataBase\lab1\

USE models

CLEAR
DEFINE WINDOW Okno1 FROM 1,3 TO 50,110 TITLE "Товары (Edit)" SYSTEM CLOSE FLOAT GROW MINIMIZE ZOOM
SHOW WINDOW Okno1
&&DEFINE WINDOW Okno2 FROM 1,3 TO 50,110 TITLE "Товары (Browse)" SYSTEM CLOSE FLOAT GROW MINIMIZE ZOOM
&&SHOW WINDOW Okno2

EDIT FIELDS mname:20:H="Модель", firm:15:H="Фирма", tipe:15:H="Тип";
FOR mname="Видеокамера";
FONT 'Courier New',10 TITLE "Видеокамеры" IN Okno1

BROWSE FIELDS mname:20:H="Модель", firm:15:H="Фирма", tipe:15:H="Тип";
FOR firm="Sony";
FONT 'Courier New',10 TITLE "Товары фирмы Sony" IN Okno1

BROWSE NOEDIT TITLE "Техника" ;
PARTITION 60    LEDIT     FIELDS mname:20:H="Модель",;
firm:15:H="Фирма", tipe:15:H="Тип", quantity:H="Количество на складе",;
price:H="Цена", opinion:H="Мнение"

HIDE WINDOW Okno1