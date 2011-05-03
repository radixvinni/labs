&& Примеры макроподстановок:

&& Макроподстановка в тексте
A="ЦСКА"
? "&A вперед!" 
? "&A вперед!"
? "Ла-Ла-Ла, &A!"

&& Макроподстановки в командах: 
&& в команде USE, LIST, SET FILTER TO, ERASE
E="table_employee"					&& Макроподстановка для USE
O="otchestvo"						&& Макроподстановка для LIST
C="table_children"					&& Макроподстановка для USE
F="(childr->children_2!=' ')"		&& Макроподстановка для SET TO FILTER TO
FIL="1.txt"							&& Макроподстановка для ERASE
USE &E AGAIN
USE &C IN 2 AGAIN ALIAS childr
SELECT 2
INDEX ON association_child TO ass_childr
SELECT 1
SET RELATION TO association_child INTO childr
SET FILTER TO &F
LIST family_name,name_,&O
ERASE $FIL

&& Макроподстановки в выражниях
SET DATE TO BRITISH
D="Date()+7"
? Dow(&D)				

&& Вложения макроподстановок
nn="Date()"
mm="&nn+2"
? &mm
? "&mm"