  CLEAR
  SET DEFA TO "D:\���� �� FoxPro"
  Select 1
  USE writingtable Again ALIAS wtable
  DEFINE WINDOW NEW FROM 1,1 TO 30,80 SYSTEM CLOSE FLOAT GROW MINIMIZE ZOOM
  SHOW WINDOW NEW

  && ������ ������������� EDIT book_cod:4:R:H="��� �����"
  EDIT Fields name1:40:R:H="������������",translat:20:R:H="�������";
  For translat="�.�������";
  FONT 'Vardana',10 STYLE 'B' PARTITION 40 LEDIT TITLE "������������ ������������ �.��������" IN NEW

  &&������ ������������� BROWSE
  BROWSE FIELDS name1:40:R:H="������������",translat:20:R:H="�������";
  For author_cod=4;
  STYLE 'B' TITLE "������������ ��������" IN NEW
  HIDE WINDOW NEW
  BROWSE
