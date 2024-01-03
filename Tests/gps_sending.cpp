#include <iostream>
#include <cstdint>

#include "gps_sending.h"

int64_t getTimestamp(const std::string& tekst) {
    // Pobieramy pierwsze 13 znaków z tekstu
    std::string str = tekst.substr(0, 13);

    // Konwertujemy ciąg znaków na int64_t
    int64_t timestamp;
    try {
       // std::cout<<str<<std::endl;
        timestamp = std::stoll(str);

    } catch (const std::exception& e) {
        // Obsługa błędu konwersji (np. ciąg znaków nie zawiera liczby)
        std::cerr << "Błąd konwersji: " <<e.what() << std::endl;
        timestamp = 0; // Domyślna wartość w przypadku błędu
    }

    return timestamp;
}