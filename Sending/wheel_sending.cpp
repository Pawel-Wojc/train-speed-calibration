#include <iostream>
#include <time.h>
#include <unistd.h>
#include <fstream>
#include <thread>
#include <nlohmann/json.hpp>

#include "netfunctions.h"
#include "gps_sending.h"
#include "time_provider.h"
using jsonf = nlohmann::json;


struct wheel {
    long long wheel_timestamp;
    double wheel_frequency; 
    int wheel_speed;
    long wheel_impulse_count;
    long wheel_distance;
    double wheel_circumference;
    int wheel_tooth;
};

wheel string_to_wheel_obj (std::string string);
double readfile(std::string filePath);
std::string wheel_obj_to_string (wheel wheel);
void recalibrate_tooth(std::vector<wheel>& wheel_vector, int tooth);
void recalibrate_circumference(std::vector<wheel>& wheel_vector, double circumference);


//funkcja glowna wysyłajaca
void wheel_sending (std::ifstream& wheel_file, int64_t time_difference){
     std::string wheel_line;

    std::ifstream settings("settings.json");
    jsonf jsondata = jsonf::parse(settings);
    std::string iface = jsondata["interace"];
    std::string ipb = getIfBroadcastAddr(iface); 
    int32_t client = jsondata["client"];      
    int32_t port = jsondata["port"];

    //zapisujemy wszystkie dane z loga
    std::vector<wheel> wheel_data;
    while (std::getline(wheel_file, wheel_line)) {   
        wheel_data.push_back(string_to_wheel_obj(wheel_line));
    }

    //po całym logu 
    for (wheel item : wheel_data){

        //tutaj okreslamy timestamp, zeby log nie byl wysylany randomowa a zgodnie z czasem ktory w nim jest
        std::int64_t wait = (item.wheel_timestamp+time_difference)-getCurrentTimestamp();
        std::this_thread::sleep_for(std::chrono::milliseconds(wait));

        //sprawdzamy czy ustawienie zebow sie zmienilo czy nie
        //jesli tak to przeliczamy predkosc z dalszej czesci loga, tak samo dla obwodu
        int tooth = static_cast<int>(readfile("tooth"));
        if (item.wheel_tooth != tooth){
            if (tooth < 120 && tooth > 50){ // sprawdzam czy zeby sa pomiedzy 50 i 120
                recalibrate_tooth(wheel_data, tooth);
            }else {
                std::cout << "BLAD!!! ZEBY POZA ZAKRESEM (50;120)";
            }
            
        }
        double circumference = readfile("circumference");
        if (item.wheel_circumference != circumference){
            if (circumference < 3000 && circumference > 2000){
                recalibrate_circumference(wheel_data,circumference);
            }else {
                std::cout << "BLAD!!! OBWOD POZA ZAKRESEM (2000;3000)";
            }
            
        }

        //wysyłamy      
        std::string wheel_line = wheel_obj_to_string(item);
        std::cout << wheel_line<< std::endl;
        std::vector<char> sendframevec(wheel_line.begin(), wheel_line.end());
        sendUdpBroadcast (ipb,port,sendframevec);

    }    
}



wheel string_to_wheel_obj (std::string string){ 
    wheel wheel;
    
    wheel.wheel_timestamp = std::stoll(string.substr(0, 13));
    
    std::istringstream stream(string.substr(21));
    std::string token;

    std::getline(stream, token, '|');
    wheel.wheel_frequency = std::stod(token);

    std::getline(stream, token, '|');
    wheel.wheel_speed = std::stoi(token);

    std::getline(stream, token, '|');
    wheel.wheel_impulse_count = std::stol(token);

    std::getline(stream, token, '|');
    wheel.wheel_distance = std::stol(token);

    std::getline(stream, token, '|');
    wheel.wheel_circumference = std::stod(token);

    std::getline(stream, token, '|');
    wheel.wheel_tooth = std::stoi(token);

    return wheel;
}

double readfile(std::string filePath){
std::ifstream inputFile(filePath);
if (inputFile.is_open()) {
        double number;
        inputFile >> number;
        if (inputFile.fail()) {
            inputFile.close();
            return 0;
        } else {
            inputFile.close();
            return number;
        }      
    } else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
}

std::string wheel_obj_to_string (wheel wheel){

    std::ostringstream resultStream ;
    resultStream << std::fixed << std::setprecision(6);
    resultStream << wheel.wheel_timestamp << "   LOG=01|"
                 << wheel.wheel_frequency << '|'
                 << wheel.wheel_speed << '|'
                 << wheel.wheel_impulse_count << '|'
                 << wheel.wheel_distance << '|'
                 << wheel.wheel_circumference << '|'
                 << wheel.wheel_tooth << "|;";
    return resultStream.str();
}

//tooth jest double bo przy dzieleniu int/int wynik to int wiec 2/1 to 0 ale 2.0/1 to juz 0.5
void recalibrate_tooth(std::vector<wheel>& wheel_vector, int tooth){
    //roznica tego co jest w logu a tego co chcemy miec

    double tooth_difference = static_cast<double>(tooth)/wheel_vector.at(0).wheel_tooth;

    //obliczem srednice kolo dla jednego zebo w metrach, dziele na 1000 bo obwód koła jest w milimetrach
    //double distance_for_one_slice = wheel_vector[0].wheel_circumference/wheel_vector[0].wheel_tooth/1000;

    //potrzebujemy przeliczyc predkosc, oraz zmienic wartosc ilosci zebow
    // czestotliwosci nie zmieniam
    for (int i = 0 ; i< wheel_vector.size()-1;i++){
        
        wheel_vector[i].wheel_speed = wheel_vector[i].wheel_speed*tooth_difference;
        wheel_vector[i].wheel_tooth = tooth;
    }
    //obliczam w ten sposob predkosc poniewaz jesli wciagu tego samego czasu dystans zmiejszymy lub zwiekszymi np dwukrotnie to predkosc rowniez urosnie dwukrotnie

}

void recalibrate_circumference(std::vector<wheel>& wheel_vector, double circumference){
    double circumference_difference = circumference/wheel_vector.at(0).wheel_circumference;
    for (int i = 0 ; i< wheel_vector.size()-1;i++){
        wheel_vector[i].wheel_speed = wheel_vector[i].wheel_speed*circumference_difference;
        wheel_vector[i].wheel_circumference = circumference;
    }



}

