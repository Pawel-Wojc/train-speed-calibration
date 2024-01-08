#include <iostream>
#include <time.h>
#include <unistd.h>
#include "netfunctions.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <inttypes.h>
#include <thread>
#include <sstream>

using jsonf = nlohmann::json;



std::vector<std::string> pokaz (std::string &inputString) {
    const char* charArray = "POL=";
    std::vector<std::string> tokens;
    // Zmienna pomocnicza do przechowywania jednej wartości
    std::string token;
    // Iterujemy przez każdy znak w stringu
    for (char ch : inputString) {
        // Jeśli znak to '|', dodajemy dotychczasowy token do wektora i zerujemy token

        if (ch == '|' || ch =='S' || ch == 'G') {
            tokens.push_back(token);
            token.clear();      
        } else {
            // W przeciwnym razie dodajemy znak do aktualnego tokena
            if (strchr(charArray, ch)){continue;}
            token += ch;
        }
    }
    // Dodajemy ostatni token, który może być na końcu stringa
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
    }

int32_t main(int argc, char *argv[]) {

    std::ifstream myfile("settings.json");
    jsonf jsondata = jsonf::parse(myfile);


    //reading position
    std::ifstream position_file(jsondata["position_file"]);


    std::string line;
    std::getline(position_file, line);

    //std::cout << line<< std::endl;

    //std::vector<std::string> tokens = pokaz(line);
    
    
    //for (int i =0;i< tokens.size(); i++){

        //std::cout <<i<< " : " << tokens[i] << std::endl;

   // }

    //std::string iface = "ens33";
    std::string iface = jsondata["interace"];
    std::string ipb = getIfBroadcastAddr(iface);
    //int32_t client = 1;    
    int32_t client = jsondata["client"];      
    //int32_t port = 30100;
    int32_t port = jsondata["port"];
    
    std::cout <<"Interfejs: " << iface << " Ip Broadcast: "<< ipb << "Port:  " << port << std::endl;
    startReceiving (client,ipb, port);



    while (true){   
        std::string line;
        std::getline(position_file, line);
        std::string sendframe = line;

        std::cout << "Wyslano: "<< sendframe<<  std::endl;


        std::vector<char> sendframevec(sendframe.begin(), sendframe.end());
        sendUdpBroadcast (ipb,port,sendframevec); //int32_t sendUdpBroadcast(std::string addr, int32_t port, std::vector<char> data)
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout<< std::endl;
    }
    
    return 0;


}

    