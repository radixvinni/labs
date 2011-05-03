USE table_employee AGAIN

DEFINE WINDOW Okno FROM 2,2 TO 40,100 SYSTEM CLOSE FLOAT GROW MINIMIZE ZOOM
SHOW WINDOW Okno

&& Некоторый пример использования EDIT
EDIT FIELDS family_name:10:R:H="Фамилия",birthday:10:R:H="День_рождения",;
sex=Iif(Upper(sex)="М","мужчина","женщина"):10:H="Пол";
FOR Upper(post)="ПРОМОУТЕР";
FONT 'Courier',16 STYLE 'I' PARTITION 33 LEDIT TITLE "Рабочие" IN Okno

&& Некоторый пример использования BROWSE
BROWSE FIELDS name_:10:R:H="Имя",post:10:R:H="Должность";
FOR Upper(post)="ПРОМОУТЕР";
STYLE 'I' PARTITION 33 REDIT TITLE "Рабочие" IN Okno

BROWSE


 