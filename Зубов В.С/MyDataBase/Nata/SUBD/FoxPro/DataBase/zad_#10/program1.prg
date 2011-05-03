&& Определение 1-ого окна (Самостоятельного)
DEFINE WINDOW Ok1 FROM 1,2 TO 10,40 TITLE "Окно 1" SYSTEM;
CLOSE FLOAT GROW MINIMIZE ZOOM

&& Определение 2-ого окна (Самостоятельного)
DEFINE WINDOW Ok2 FROM 5,70 TO 40,140 TITLE "Окно 2" SYSTEM;
CLOSE FLOAT GROW MINIMIZE ZOOM 

&& Определение 3-eго окна (Вложенного в окно 2)
DEFINE WINDOW Ok3 FROM 0,0 TO 20,40 TITLE "Окно 3" IN Ok2 SYSTEM;
CLOSE FLOAT GROW MINIMIZE ZOOM

WAIT WINDOW 'Делаем активным 1-ое окно и печатаем в него(нажмите клавишу)'
&& Активация 1-ого окна 
ACTIVATE WINDOW Ok1
&& Печать в первое окно
?"Print into first window"

WAIT WINDOW 'Делаем активным 2-ое окно и печатаем в него(нажмите клавишу)'
&& Активация 2-ого окна 
ACTIVATE WINDOW Ok2
&& Печать во второе окно
?"Print into second window"

WAIT WINDOW 'Делаем активным 3-ое окно определенное во 2-ом и печатаем в него(нажмите клавишу)'
&& Активация 3-ого окна в окне 2
ACTIVATE WINDOW Ok3 IN Ok2
&& Печать в третье окно
?"Print into third window"

WAIT WINDOW 'Скрываем окно 1 и производим печать в него(нажмите клавишу)'
&& скроем окно 1 сделав его окном выдачи (пусть даже скрытым)
HIDE WINDOW Ok1
ACTIVATE WINDOW Ok1 NOSHOW
&& и выполним скрытую печать в окно 1
?"Into first window Noshow"

WAIT WINDOW 'Перемещаем окно 1(нажмите клавишу)' 
&& Перемистим окно 1 (1-ый способ)
ACTIVATE WINDOW Ok1
MOVE WINDOW Ok1 TO 5,6

WAIT WINDOW 'Перемещаем окно 3(нажмите клавишу)'
&& Переместим окно 3 (2-ой способ)
ACTIVATE WINDOW Ok3
MOVE WINDOW Ok3 BY 5,5

WAIT WINDOW 'Изменяем размеры 2-ого окна(нажмите клавишу)'
&& Изменим размеры 2-ого окна
ZOOM WINDOW Ok2 NORM FROM 5,70 TO 35,150

WAIT WINDOW 'Минимизируем 3-е окно(нажмите клавишу)'
&& Изменим размеры 3-его окна(Минимизируем)
ZOOM WINDOW Ok3 MIN
ACTIVATE WINDOW Ok2

WAIT WINDOW 'Удаляем все окна(нажмите клавишу)'
CLEAR WINDOWS