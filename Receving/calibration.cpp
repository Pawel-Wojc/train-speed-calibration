#include "structures.hpp"
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

void calibrate(std::vector<gps> gps_data){
    std::cout << "calibrate "<<std::endl;

}

void tocalibrate (std::vector<gps>& gps_data, int& speed_strike) {
    std::cout<< std::endl<<  " rozmiar: "<<gps_data.size()<<" czas: "<<gps_data.back().gps_timestamp  << " speed: " << gps_data.back().gps_speed<< std::endl;
bool speed_strike_bool = gps_data[gps_data.size()-2].gps_speed == gps_data.back().gps_speed;
    if (speed_strike_bool){
        speed_strike = speed_strike +1;
    }else {
        std::cout<<"speed strike:" << speed_strike << std::endl;
        if (speed_strike == 60 ){
            calibrate(gps_data);
        }
        gps_data.clear();
        speed_strike = 0;
    }

}

void dataparsing(std::vector<gps>& gps_data, std::vector<wheel>& wheel_data) {
while (gps_data.empty()){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


int data_cout = gps_data.size();

int speed_strike = 0 ;

while (true){
    if (data_cout == (int) gps_data.size()){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
    }else if (gps_data.size()>1) { //porownuje ostatni i przed ostatni wiec musza byc dwa elementy co najmniej
        tocalibrate (gps_data, speed_strike);
        data_cout = gps_data.size();
    }else {
       
    }
}

// for (const auto& element : gps_data) {
//         std::cout << element.gps_distance <<" "<< element.gps_e<<" "<< element.gps_n<< " ";
//     }

}