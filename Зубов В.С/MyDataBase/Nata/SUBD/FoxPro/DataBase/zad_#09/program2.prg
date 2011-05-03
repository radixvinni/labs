&& Установка нормальной даты
SET DATE TO BRITISH

&& Создадим Б.Д. рабочие с полями Фамилия, дата рождения, Проект, Зарплата
CREATE DBF table_job(jobs C(10), date_ D, project_ C(10), pay N(10,0))

&& Добавим записи в созданную Б.Д.
INSERT INTO table_job(jobs,date_,project_,pay) VALUES("Иванов",{^1960/12/01},;
"Сарай",30000)
INSERT INTO table_job(jobs,date_,project_,pay) VALUES("Петров",{^1966/11/02},;
"Дом",55000)
INSERT INTO table_job(jobs,date_,project_,pay) VALUES("Сидоров",{^1969/02/17},;
"Дом",50000)
INSERT INTO table_job(jobs,date_,project_,pay) VALUES("Корин",{^1971/08/29},;
"Гараж",40000)
INSERT INTO table_job(jobs,date_,project_,pay) VALUES("Антончук",{^1955/01/09},;
"Дом",60000)
INSERT INTO table_job(jobs,date_,project_,pay) VALUES("Бирин",{^1964/04/26},;
"Гараж",45000)
CLOSE DATABASES
&& Выведем таблицу
SELECT * FROM table_job ORDER BY project_,jobs