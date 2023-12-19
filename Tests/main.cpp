#include <iostream>
 #include <time.h>
 #include <unistd.h>
 #include <fstream>
 #include <nlohmann/json.hpp>
#include <thread>


int64_t getTimestamp(const std::string& tekst) {
    // Pobieramy pierwsze 13 znaków z tekstu
    std::string str = tekst.substr(0, 13);

    // Konwertujemy ciąg znaków na int64_t
    int64_t timestamp;
    try {
        timestamp = std::stoll(str);
    } catch (const std::exception& e) {
        // Obsługa błędu konwersji (np. ciąg znaków nie zawiera liczby)
        std::cerr << "Błąd konwersji: " << e.what() << std::endl;
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
    std::cout << "Aktualny timestamp: " << start_timestamp << std::endl;

    // //reading position
     std::ifstream position_file("2023-12-03_adamlog_short");


     std::string line;
     std::getline(position_file, line);

    std::int64_t time_difference = start_timestamp-getTimestamp(line);

    

    for (int i=0; i<200;i++) {   
         std::string line;
         std::getline(position_file, line);
         //std::string sendframe = line;

        // int64_t time_difference2 = start_timestamp-getTimestamp(line);
        // std::cout << "Roznica:"<< time_difference <<" Teraz roznica:" << start_timestamp-getTimestamp(line)<< std::endl;
        // std::cout << "Roznica2:"<< getCurrentTimestamp()-time_difference2 -getTimestamp(line)<<std::endl;
         
        // if (getCurrentTimestamp()-time_difference>start_timestamp-getTimestamp(line)){
           if (getTimestamp(line)<getCurrentTimestamp()-time_difference) {
           
            std::cout << "Roznica:"<< getCurrentTimestamp()-getTimestamp(line)<<std::endl;
            std::cout << "Start Timestamp:"<< getCurrentTimestamp()-time_difference<<std::endl;
            //std::cout << line;
         }else {
            
        //    int64_t difference =  getCurrentTimestamp()-time_difference<start_timestamp-getTimestamp(line);

        //     std::this_thread::sleep_for(std::chrono::milliseconds(difference));

        //     std::cout << line;
         }
         
         //std::cout << "Wyslano: "<< sendframe<<  std::endl;
         //std::cout << getTimestamp(sendframe)<<std::endl;
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
     };
    

    std::cin >> line;
    return 0;


}

    