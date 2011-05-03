Set DEFA TO c:\ALANsProgs\work\FoxPro\MyLastDB\

U="table1"           && Макроподстановка для USE
L="car_firm"         && Макроподстановка для LIST
A1="car_param"
A2="&A1->motortype"  && Вложения макроподстановок

clear
&& Открываю 3 рабочие области, создаю связи 1:1 и 1:N и вывожу через LIST и BROUSE
select 1
use &U IN 1 AGAIN alias main                       && Макроподстановка для USE
SELECT 2
USE table4 IN 2 AGAIN alias car_firm
INDEX ON firm TO firm_ind
select 3
use table3 in 3 AGAIN alias car_param
INDEX ON number TO num_ind
select 1
SET RELATION TO firm INTO car_firm
SET RELATION TO number INTO car_param ADDITIVE

list title,Iif(Found("&L"),car_firm->firm,"Unknown") && Макроподстановка для LIST


BROWSE NOEDIT TITLE "Машины" PARTITION 45 LEDIT;
FIELDS title:H="Название",cena:H="Цена",;
&A2:H="Тип двигателя",car_firm->firm:H="Производитель",; && Используем вложение макроподстоновокздесь
car_firm->phone:H="Телефон диллера"
&& Макроподстановки в выражниях
SET DATE TO BRITISH
D="Date()+7"
? Dow(&D)				