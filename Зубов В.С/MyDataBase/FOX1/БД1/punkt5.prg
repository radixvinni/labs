SET DEFA TO H:\FOX1\БД1

USE main AGAIN ALIAS toys
SET TEXTMERGE ON TO Report_toys.txt WINDOW SHOW
INDEX ON izdelie_kl TO B_rege_ind
\     Игрушки пупсы
\
SCAN FOR izdelie="Пупс"
\Фирма <<RTRIM(firm_name)>>, тип <<tip>>
ENDSCAN
SET TEXTMERGE TO 