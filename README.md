ENG
The project is divided into two separate ones, i.e. a sending project and a receiving project

The sending project simulates sending logs as it would be on a train. The timestamp is taken into account (i.e. if a log is delayed or, for example, a few frames are missing, it will still be sent according to the timestamp). The circumference and tooth files are setting files, which means that from these files the simulator takes the settings for the number of teeth and wheel circumference and modifies the log if these data have changed. Thanks to this, we have live reactions to changes in settings, which was necessary

The task of the receiving program is to set the values in these two files so that the speeds for reading from the Adam and GPS devices are similar (the margin can be set - I set it to 3 km/h). First, we change the wheel circumference and if its value is too large, the number of teeth changes. The program can be tested based on the logs from the tests folder, in this log the speed in the entire range for the Adam device has been increased by 10% (python script).

PL
Projekt podzielony na dwa osobne, tzn. projekt do wysyłania i do odbierania

Projekt do wysyłania symuluje wysyłanie logów tak jak było by to na pociagu. Timestamp jest brany pod uwage (tzn jesli ktorys log jest opozniony lub np brakuje paru ramek to i tak zostanie wyslany on zgodnie z timestampem).
Plik circumference i tooth sa to pliku ustawieniowe, to znaczy ze z tych plikow symulator bierze ustawienie dla ilosci zebow oraz obwodu kolo i modyfikuje log jesli te dane sie zmienily
Dzieki temu mamy reakcje na zywo na zmiane ustawien co było niezbędne

Zadaniem programu odbierajacego jest takie ustawienie wartosci w tych dwoch plikach aby predkosci dla odczytu z urzadzenia adam i gps były zbliżone (margines mozna ustawic ja ustawilem 3km/h).
Na poczatku zmieniamy jest obwod koła i jesli jego wartosc bedzie za duzo to zmienia sie ilosc zebow.
Program mozna przetestowac na podstawie logow z folderu testy, w tym logu predkosc w całym zakresie dla urzadzenia 
adam została zwiekszona o 10% (skrypt python).
