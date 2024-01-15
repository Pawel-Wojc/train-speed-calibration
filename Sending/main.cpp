#include <iostream>
#include <unistd.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <thread>

#include "gps_sending.h"
#include "wheel_sending.h"
#include "time_provider.h"

using jsonf = nlohmann::json;

void runthreads (std::ifstream& gps_file, std::ifstream& wheel_file, int64_t roznica){
    std::cout << "uruchomiono, roznica: "<< roznica << std::endl ;
    std::thread t1(gps_sending, std::ref(gps_file), roznica);
    std::thread t2 (wheel_sending, std::ref(wheel_file), roznica);
    t1.join();
    t2.join();
}

int32_t main(int argc, char *argv[]) {


    std::ifstream settings("settings.json");
    jsonf jsondata = jsonf::parse(settings);

    std::string gps_log_path = jsondata["gps_log"];
    // bierzemy pierwsza linie z obu plikow
    std::ifstream gps_file(gps_log_path);
    std::string gps_line;
    std::getline(gps_file, gps_line);

    //std::ifstream wheel_file("2023-12-03_pos");
    std::string wheel_log_path = jsondata["wheel_log"];  
    std::ifstream wheel_file(wheel_log_path);  
    std::string wheel_line;
    std::getline(wheel_file, wheel_line);

    // odczytuje timestamp z tych lini 

    int64_t gps_start_timestamp = getTimestamp (gps_line);
    int64_t wheel_start_timestamp = getTimestamp (wheel_line);
    int64_t absolute_time_difference ;
    if (gps_start_timestamp < wheel_start_timestamp){ //pierwszy jest sygnał z gps
            absolute_time_difference = getCurrentTimestamp()-gps_start_timestamp;
            runthreads (gps_file,wheel_file, absolute_time_difference);
    }else{
            absolute_time_difference = getCurrentTimestamp()-wheel_start_timestamp;
            runthreads (gps_file,wheel_file, absolute_time_difference);
    }
}

    