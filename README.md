# Описание
Практическая работа по курсу "Архитектура информационных систем". Разработка встраиваемой системы
## Вариант 2 
Робот, который будет закрашивать/мыть стены и пол
## Задание 1
Разработана перечень use-case и сформирован баклог. Определены приоритеты. Разработана схема комплекса технических средств. Разработана концептуальную модель. Разработана диаграмма последовательности для прецедентов. Разработан минимальный прототип – программа, которая может читать видео с камеры и показывать на экран при помощи opencv.
- [Use-case diagram](https://github.com/amirovmir/paintRobot/blob/main/doc/Images/use-case.png)
- [Backlog](https://github.com/amirovmir/paintRobot/blob/main/doc/Images/Backlog.jpg)
- [Концептуальная модель](https://github.com/amirovmir/paintRobot/blob/main/doc/Images/conceptual-diagram.png)
- [opencv](https://github.com/amirovmir/paintRobot/tree/main/opencv)
- [Диаграмма классов](https://github.com/amirovmir/paintRobot/blob/main/doc/Images/class-diagram.png)
## Задание 2
Разработаны диаграммы классов и последовательностей.
- [Диаграмма классов](https://github.com/amirovmir/paintRobot/blob/main/doc/Images/class-diagram.png)
- [Диаграмма последовательностей](https://github.com/amirovmir/paintRobot/blob/main/doc/Images/sequence-diagram.png)
## Задание 3
Собран прототип программы в Docker.
- [Dockerfile](https://github.com/amirovmir/paintRobot/blob/main/src/Dockerfile)
## Задание 4
Спроектирован конечный автомат и нарисована диграмма состояний в UML. Конечный автомат добавлен в макет программы.
- [Конечный автомат](https://github.com/amirovmir/paintRobot/blob/main/doc/Images/state-diagram.png)
## Задание 5
Реализовано сетевое взаимодействие между камерой и роботом по протоколу UDP. 
- [Серверная часть](https://github.com/amirovmir/paintRobot/blob/main/src/code/server/server.cpp)
- [Клиентская часть](https://github.com/amirovmir/paintRobot/blob/main/src/code/client/client.cpp)
## Задание 6
Необходимо реализовать в виде программы для KOS управляющую программу
