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


void wheel_sending (std::ifstream& wheel_file, int64_t time_difference){
     std::string wheel_line;

    std::ifstream settings("settings.json");
    jsonf jsondata = jsonf::parse(settings);
    std::string iface = jsondata["interace"];
    std::string ipb = getIfBroadcastAddr(iface); 
    int32_t client = jsondata["client"];      
    int32_t port = jsondata["port"];

    while (std::getline(wheel_file, wheel_line)) {   
        
        std::int64_t wait = (getTimestamp(wheel_line)+time_difference)-getCurrentTimestamp();
        std::this_thread::sleep_for(std::chrono::milliseconds(wait));
        std::cout << wheel_line <<std::endl ;

        std::vector<char> sendframevec(wheel_line.begin(), wheel_line.end());
        sendUdpBroadcast (ipb,port,sendframevec);
        };
         
}