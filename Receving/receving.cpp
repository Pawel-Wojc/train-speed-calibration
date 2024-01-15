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
    gps.gps_speed = std::stoi(token) * 1.852;

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
            
            if (rLenght >= 90) {
                /* gps */
                gps_data.push_back(readgps(rBuffer));
            }else if (rLenght > 60 && rLenght < 70)
            {
                /* wheel */
                wheel_data.push_back(readwheel(rBuffer));              
            }
            
    }
}