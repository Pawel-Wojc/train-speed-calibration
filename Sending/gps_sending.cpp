#include <iostream>
#include <time.h>
#include <unistd.h>
#include <fstream>

#include <thread>

#include "gps_sending.h"
#include "time_provider.h"



void gps_sending (std::ifstream& gps_file, int64_t roznica){
    // std::int64_t start_timestamp = getCurrentTimestamp();   

     std::string gps_line;
    // std::getline(gps_file, gps_line);

    // std::int64_t time_difference = start_timestamp-getTimestamp(gps_line);
    // std::cout << "time_difference: " << time_difference << std::endl;

    // std::cout << "start_timestamp: " << start_timestamp << std::endl;

   
    std::int64_t time_difference = roznica;

    
    while (std::getline(gps_file, gps_line)) {   
        
        std::int64_t wait = (getTimestamp(gps_line)+time_difference)-getCurrentTimestamp();
        //std::cout <<"wait:"<<wait << "    " << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(wait));
        //std::cout << "DIFF: "<< (getTimestamp(gps_line)+time_difference)-getCurrentTimestamp()<<std::endl;
        std::cout << gps_line <<std::endl ;
        };
         
         //std::cout << "Wyslano: "<< sendframe<<  std::endl;
         //std::cout << getTimestamp(sendframe)<<std::endl;
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}