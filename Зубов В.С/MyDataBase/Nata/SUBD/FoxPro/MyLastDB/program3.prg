Set DEFA TO c:\ALANsProgs\work\FoxPro\MyLastDB\

use table1 again ALIAS main
set textmerge on to rep_car.txt window show
index on title to title_ind
\                Автомобили фирмы Nissan
\
scan for firm="Nissan"
\ Модель <<rtrim(title)>>, производитель <<>> firm
endscan
set textmerge to

