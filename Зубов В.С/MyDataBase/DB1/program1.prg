CLOSE DATABASES
SET PATH TO('D\Базы данных\lab1\')
OPEN DATABASE data1
USE table
CLEAR
P1="Телевизор"
P2="Модель &P1"+"a:"
SCAN FOR Mname="&P1"
  ? "&P2", tipe, firm
ENDSCAN
?
?
INDEX ON Tipe TO IndTipes
SEEK "GR"
DO WHILE tipe="GR"
  ? mname, tipe, firm
  SKIP
ENDDO
?

z=Padr("GR-D290 E", Len(tipe))
SEEK z
DO WHILE tipe==z
  ? mname, tipe, firm
  SKIP
ENDDO

INDEX ON Firm TO IndFirms
SET TEXTMERGE ON
SEEK "Sony"
\
\              Дорогой покупатель!
\
\ Мы рады сообщить Вам, что в нашем магазине
\ начинается распродажа с <<Date()>> на товары
\ фирмы <<Firm>>:
\
SCAN FOR FIRM="Sony"
\ Наименование: <<mname>>
\ Модель:            <<tipe>>
\ Цена:                <<price>>
\
ENDSCAN

&&USE table
&&DO WHILE .Not.EOF()
&&  ACCEPT "Введите отзыв о товаре"+Firm+Tipe TO S
&&  REPLACE Opinion WITH S ADDITIVE
&&  SKIP
&&ENDDO

BROWSE FIELDS mname :H='Наименование', tipe :H='Тип', firm :H='Фирма', opinion :H='Мнение' 
