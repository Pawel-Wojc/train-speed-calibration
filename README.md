Projekt podzielony na dwa osobne, tzn. projekt do wysyłania i do odbierania

Projekt do wysyłania symuluje wysyłanie logów tak jak było by to na pociagu. Timestamp jest brany pod uwage (tzn jesli ktorys log jest opozniony lub np brakuje paru ramek to i tak zostanie wyslany on zgodnie z timestampem).
Plik circumference i tooth sa to pliku ustawieniowe, to znaczy ze z tych plikow symulator bierze ustawienie dla ilosci zebow oraz obwodu kolo i modyfikuje log jesli te dane sie zmienily
Dzieki temu mamy reakcje na zywo na zmiane ustawien co było niezbędne

Zadaniem programu odbierajacego jest takie ustawienie wartosci w tych dwoch plikach aby predkosci dla odczytu z urzadzenia adam i gps były zbliżone (margines mozna ustawic ja ustawilem 3km/h).
Na poczatku zmieniamy jest obwod koła i jesli jego wartosc bedzie za duzo to zmienia sie ilosc zebow.
Program mozna przetestowac na podstawie logow z folderu testy, w tym logu predkosc w całym zakresie dla urzadzenia 
adam została zwiekszona o 10% (skrypt python).