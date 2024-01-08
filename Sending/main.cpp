#include <iostream>
#include <unistd.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <thread>

#include "gps_sending.h"
#include "wheel_sending.h"
#include "time_provider.h"

void runthreads (std::ifstream& gps_file, std::ifstream& wheel_file, int64_t roznica){
    std::cout << "uruchomiono, roznica: "<< roznica << std::endl ;
    std::thread t1(gps_sending, std::ref(gps_file), roznica);
    t1.join();
}

int32_t main(int argc, char *argv[]) {


    // bierzemy pierwsza linie z obu plikow
    std::ifstream gps_file("2023-12-03_adamlog_short");
    std::string gps_line;
    std::getline(gps_file, gps_line);

    std::ifstream wheel_file("2023-12-03_pos");
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

    














    // std::int64_t start_timestamp = getCurrentTimestamp();
    // std::cout << "start_timestamp: " << start_timestamp << std::endl;
    // std::ifstream gps_file("2023-12-03_adamlog_short");
    // std::string gps_line;
    // std::getline(gps_file, gps_line);
    // std::int64_t time_difference = start_timestamp-getTimestamp(gps_line);
    // std::cout << "time_difference: " << time_difference << std::endl;
    
    // std::cout <<getCurrentTimestamp()<<"spie sekunda" <<std::endl;
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // std::cout <<getCurrentTimestamp()<<"spie -0.02s" <<std::endl;
    //  std::this_thread::sleep_for(std::chrono::milliseconds(-2));
    //  std::cout <<getCurrentTimestamp()<<"koniec" <<std::endl;
    
    //synchronization two files of logs






}

    