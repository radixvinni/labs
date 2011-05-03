CLEAR
SET DEFA TO D:\Downloads\БДЭС\MyBD

SELECT 1
USE main AGAIN ALIAS Books
INDEX ON UPPER(Publisher) TO Publ_indx

&& Выполним поиск по неизвестным издательствам
key_s = UPPER("неизвестно")
SEEK key_s
IF Found()
	? Title,auth_surname,Publisher
	WAIT WINDOW Publisher+title
ELSE 
	? "Такой книги в базе нет!"
	WAIT WINDOW 'Такой книги в базе нет!'
ENDIF