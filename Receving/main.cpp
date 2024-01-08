#include <iostream>
#include <unistd.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <thread>

#include "calibration.h"
#include "receving.h"
#include "structures.hpp"


using jsonf = nlohmann::json;


void runthreads (gps * gps_data){
     std::thread t1(start_receving() ,gps_data);
    // std::thread t2 ();
    // t1.join();
    // t2.join();
}

int32_t main(int argc, char *argv[]) {

    gps * gps_data = new gps;

    runthreads(gps_data)

}