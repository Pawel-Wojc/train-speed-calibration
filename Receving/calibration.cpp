#include "structures.hpp"
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <fstream>


void calibrate(std::vector<gps> gps_data,std::vector<wheel> wheel_data){
    float speed_from_gps_temporary = 0;
    double speed_from_wheel = 0;
    //licze srednia predkosc dla gps i wheel
    for (gps& element : gps_data){
        speed_from_gps_temporary += element.gps_speed;
    }
    double speed_from_gps = std::round (speed_from_gps_temporary / gps_data.size());

    for (wheel& element : wheel_data){
        speed_from_wheel += element.wheel_speed;
    }
    speed_from_wheel = speed_from_wheel / wheel_data.size();


    //jesli roznica w predkosc jest mniejsza niz 3 to nie zmieniam nic
    if (std::abs(speed_from_gps - speed_from_wheel) < 3){
        return;
    }else {
            std::cout << "calibrate "<<std::endl;
    }

    int current_tooth = wheel_data[0].wheel_tooth;
    double current_circumference = wheel_data[0].wheel_circumference;
    double speed_ratio = speed_from_gps/speed_from_wheel;
    double circumference_to_save = current_circumference * speed_ratio;

    //sprawdzam czy obwod do zmiany nie przekracza "norm"
    if (circumference_to_save<3000 && circumference_to_save >2000){
        //ok, zapisuje zmiany
        std::string circumference_file = "../Sending/circumference";
        std::ofstream outputFile(circumference_file);
        if (outputFile.is_open()) {
            outputFile << circumference_to_save;
            outputFile.close();
            std::cout<< "Calibration saved to file";
        }else {
            std::cout<< "Failed to save circumference";
        }

    }else { //jesli przekracza to zmieniam ilosc zebow
        int tooth_to_save = std::round (current_tooth*speed_ratio);
        //sprawdzam czy ilosc zebow do zmiany nie przekracza "norm"
        if (tooth_to_save<120 && tooth_to_save>50){
            //ok, zapisuje zmiany
            std::string circumference_file = "../Sending/tooth";
            std::ofstream outputFile(circumference_file);
            if (outputFile.is_open()) {
                outputFile << tooth_to_save;
                outputFile.close();
                std::cout<< "New value of tooth saved to file";
            }else {
                std::cout<< "Failed to save tooth";
            }
        }
        //nie ok, nie mozna skalibrowac
        std::cout << "ERROR!!!, unable to calibrate, wront tooth or circumferencje value" << std::endl;
    }
}

//kazda odebrana ramka tu trafia i jest sprawdzane czy predkosc jest taka jak w ramce poprzedniej, jesli tak to speed_strike++, jesli speed_strike > 60 to przechodzimy do kalibracji
void tocalibrate (std::vector<gps>& gps_data,std::vector<wheel>& wheel_data, int& speed_strike) {
    bool speed_strike_bool = gps_data[gps_data.size()-2].gps_speed == gps_data.back().gps_speed;
    if (speed_strike_bool){
        speed_strike = speed_strike +1;
    }else {
        if (speed_strike >= 19 ){
            calibrate(gps_data, wheel_data);
        }
        gps_data.clear();
        wheel_data.clear();
        speed_strike = 0;
    }
}

void dataparsing(std::vector<gps>& gps_data, std::vector<wheel>& wheel_data) {
    //jesli nic nie odebralismy to program czeka
    while (gps_data.empty()){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    int data_cout = gps_data.size();
    int speed_strike = 0 ;

    while (true){
        //jesli od poprzedniego razu lista sie nie zwiekszyla (program przeszedl szybciej niz odebralismy kolejna ramke to czekamy)
        if (data_cout == (int) gps_data.size()){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));      
        }else if (gps_data.size()>1) { //porownuje ostatni i przed ostatni wiec musza byc dwa elementy co najmniej
            tocalibrate (gps_data,wheel_data, speed_strike);
            data_cout = gps_data.size();
        }else {   
        }
    }

}