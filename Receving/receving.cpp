#include "structures.hpp"
#include <vector>
#include <fstream>
#include "netfunctions.h"

#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

gps readgps(char *rBuffer){
    gps gps;
    gps.gps_timestamp = std::stoll(std::string(rBuffer, 13)) ;

    std::string dataString = std::string(rBuffer + 13);
    
    std::istringstream stream(dataString);
    std::string token;

    std::getline(stream, token, '=');
    std::getline(stream, token, '|');
    gps.gps_speed = std::stoi(token);

    std::getline(stream, token, 'N');
    gps.gps_n = std::stof(token);

    std::getline(stream, token, '|');
    std::getline(stream, token, 'E');
    gps.gps_e = std::stof(token);

    std::getline(stream, token, '|');
    std::getline(stream, token, '|');
    std::getline(stream, token, '|');
    gps.gps_distance = std::stoi(token);

    return gps;
    }

wheel readwheel(char *rBuffer){
    wheel wheel;
    wheel.wheel_timestamp = std::stoll(std::string(rBuffer, 13));

    std::string dataString = std::string(rBuffer + 13);
    
    std::istringstream stream(dataString);
    std::string token;

    std::getline(stream, token, '|');
    // Pobierz wartości oddzielone znakiem |
    std::getline(stream, token, '|');
    wheel.wheel_frequency = std::stod(token);

    std::getline(stream, token, '|');
    wheel.wheel_speed = std::stoi(token);

    std::getline(stream, token, '|');
    wheel.wheel_impulsce_count = std::stol(token);

    std::getline(stream, token, '|');
    wheel.wheel_distance = std::stol(token);

    std::getline(stream, token, '|');
    wheel.wheel_circumference = std::stod(token);

    std::getline(stream, token, '|');
    wheel.wheel_tooth = std::stoi(token);

   
    return wheel;
    }

void start_receving(std::vector<gps>& gps_data, std::vector<wheel>& wheel_data) {



    std::ifstream settings("settings.json");
    jsonf jsondata = jsonf::parse(settings);
    std::string iface = jsondata["interace"];
    std::string ipb = getIfBroadcastAddr(iface); 
    int32_t client = jsondata["client"];      
    int32_t port = jsondata["port"];


    

startReceiving (client,ipb, port);
while (true){

 #define DATA_BUFF_SIZE 20000 
        char *rBuffer = new char [DATA_BUFF_SIZE+1];
        struct sockaddr_in resp;
        memset((char *)&resp, 0 , sizeof(sockaddr_in));
        socklen_t slen = 0 ;
        int32_t rLenght = recvfrom (client, rBuffer, DATA_BUFF_SIZE , 0 , (struct sockaddr *)& resp, &slen);
        //std::cout << "Odebrnano dlugosc : " << rLenght << " Wiadomosc: "<< rBuffer ;
        //std::cout << std::endl; 
                    // int rLenght = 69;
                    // //const char* input = "1701624000192 LOG=01|910.123456|118|14296573|514148|2733.185609|76|";
                    // const char* input = "1701624000193	POS=63|52.423230 N|18.597110 E|2023-12-03 18:20:04|7211991|2023-11-29 17:49:09|;";
                
                    // // Alokacja pamięci dla rBuffer i kopiowanie zawartości input
                    // char* rBuffer = new char[strlen(input) + 1];
                    // strcpy(rBuffer, input);
        if (rLenght == 95) {
            /* gps */
            gps_data.push_back(readgps(rBuffer));
        }else if (rLenght == 63)
        {
            /* wheel */
            wheel_data.push_back(readwheel(rBuffer));
            
        }
        
}
}