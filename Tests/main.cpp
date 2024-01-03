#include <iostream>
#include <time.h>
#include <unistd.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <thread>

#include "gps_sending.h"
#include "wheel_sending.h"



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

    int64_t getCurrentTimestamp() {
      // Pobieramy aktualny czas
    auto currentTime = std::chrono::system_clock::now();

    // Zamieniamy na milisekundy od epoki
    auto timestampMillis = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count();

    return timestampMillis;
}

int32_t main(int argc, char *argv[]) {

    std::int64_t start_timestamp = getCurrentTimestamp();
    std::cout << "start_timestamp: " << start_timestamp << std::endl;

    //reading position
    std::ifstream gps_file("2023-12-03_adamlog_short");


    std::string gps_line;
    std::getline(gps_file, gps_line);





    std::int64_t time_difference = start_timestamp-getTimestamp(gps_line);
    std::cout << "time_difference: " << time_difference << std::endl;
    
    // std::cout <<getCurrentTimestamp()<<"spie sekunda" <<std::endl;
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // std::cout <<getCurrentTimestamp()<<"spie -0.02s" <<std::endl;
    //  std::this_thread::sleep_for(std::chrono::milliseconds(-2));
    //  std::cout <<getCurrentTimestamp()<<"koniec" <<std::endl;
    
    //synchronization two files of logs




    while (std::getline(gps_file, gps_line)) {   
        
       


        std::int64_t wait = (getTimestamp(gps_line)+time_difference)-getCurrentTimestamp();
        std::cout <<"wait:"<<wait << "    ";
        std::this_thread::sleep_for(std::chrono::milliseconds(wait));
        std::cout << gps_line<< (getTimestamp(gps_line)+time_difference)-getCurrentTimestamp()<<std::endl;
            
         };
         
         //std::cout << "Wyslano: "<< sendframe<<  std::endl;
         //std::cout << getTimestamp(sendframe)<<std::endl;
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
     
    
    return 0;


}

    