clear
? "Введите название таблицы, которую вы хотели бы посмотреть "
accept "a,b,c,d  - " to tb
use main IN a again 
use regeser_info IN b again 
use acter IN c again
use video IN d again
do case 
case tb=="a"
select a
case tb=="b"
select b
case tb=="c"
select c
case tb=="d"
select d
otherwise 
? "Неправильный ввод таблицы"
endcase
list all 
accept "Введите название фильма о которой вы бы хотели получить информацию :  " to naz
select b
LOCATE for nazvanie=naz
? "Информация о фильме: "
? "режессер : ", regesser
? "кинокомпания :", cinema 
? "продолжительность :", vremya 
SELECT a
LOCATE FOR reg==d.reg
? "фильм :",nazvanie
