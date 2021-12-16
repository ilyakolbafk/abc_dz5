# Вариант 13
## Колб Илья БПИ205
### Домашнее задание №5

#### Построение многопоточных приложение

#### Задание:

В гостинице 10 номеров рассчитаны на одного человека и 15 номеров рассчитаны на двух человек. В гостиницу приходят
клиенты дамы и клиенты джентльмены, и конечно они могут провести ночь в номере только с представителем своего пола. Если
для клиента не находится подходящего номера, он уходит искать ночлег в другое место. Создать многопоточное приложение,
моделирующее работу гостиницы

#### Решение:
Для выполнения данного задания была выбрана модель
построения многопоточных приложений "Взаимодействующие
равные". Клиенты гостиницы - потоки. При попытке заселиться
в отель, они обращаются к методу reception. <br>

#### Запуск:
Для запуска программы необходимо запустить консольное приложение. И вписать неотрицательное число посетителей гостиницы<br>
В консоль будет выведено n строк, в которых должен быть
описан каждый посетитель и его действие: <br>
1. Пол: Gentleman (M); Lady (W);
2. Категория комнаты: double (2); single(1);
3. Номер команты;
4. id потока

Затем выведена информация о заполнении номеров в отеле

Последняя строка - количество посетителей, который не смогли попасть в отель 
