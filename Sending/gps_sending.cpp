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


void gps_sending (std::ifstream& gps_file, int64_t time_difference){
    std::string gps_line;
   
    std::ifstream settings("settings.json");
    jsonf jsondata = jsonf::parse(settings);
    std::string iface = jsondata["interace"];
    std::string ipb = getIfBroadcastAddr(iface); 
    int32_t client = jsondata["client"];      
    int32_t port = jsondata["port"];

    
    while (std::getline(gps_file, gps_line)) {   
        
        std::int64_t wait = (getTimestamp(gps_line)+time_difference)-getCurrentTimestamp();
        //std::cout <<"wait:"<<wait << "    " << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(wait));
        //std::cout << "DIFF: "<< (getTimestamp(gps_line)+time_difference)-getCurrentTimestamp()<<std::endl;
        //std::cout << gps_line <<std::endl ;




        std::vector<char> sendframevec(gps_line.begin(), gps_line.end());
        sendUdpBroadcast (ipb,port,sendframevec);




        };

}