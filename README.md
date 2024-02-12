Projekt podzielony na dwa osobne, tzn. projekt do wysyłania i do odbierania

Projekt do wysyłania symuluje wysyłanie logów tak jak było by to na pociagu. Timestamp jest brany pod uwage.
Plik circumference i tooth sa to pliku ustawieniowe, to znaczy ze z tych plikow symulator bierze ustawienie dla ilosci zebow oraz obwodu kolo i modyfikuje log jesli te dane sie zmienily
Dzieki temu mamy reakcje na zywo na zmiane ustawien co było niezbedle

Zadaniem programu odbierajacego jest takie ustawienie wartosci w tych dwoch plikach aby predkosci dla odczytu z urzadzenia adam i gps pokrywały sie.


Do testowania uzywam danych z folderu testy, jest tam 200 rekordow oraz przygotowe dane idealne do calibracji, tzn predkosc od 20-40 rekordu rozni sie i jest jednostajna przez te 20 rekordow w obu plikach
