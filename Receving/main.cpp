#include <iostream>
#include <unistd.h>
#include <fstream>
#include "nlohmann/json.hpp"
#include <thread>

#include "calibration.hpp"
#include "receving.hpp"
#include "structures.hpp"


using jsonf = nlohmann::json;


void runthreads (std::vector<gps>& gps_data, std::vector<wheel>& wheel_data){

     std::thread t1(start_receving , std::ref(gps_data), std::ref(wheel_data));
     std::thread t2(dataparsing , std::ref(gps_data), std::ref(wheel_data));
     t1.join();
     t2.join();
}

int32_t main(int argc, char *argv[]) {

    std::vector<gps> gps_data;
    std::vector<wheel> wheel_data;
    runthreads(gps_data, wheel_data);

}