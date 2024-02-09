#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <sstream>



struct gps {
    long long gps_timestamp;
    float gps_speed; //pos (predkosc wezly)
    float gps_n;
    float gps_e;
    int gps_distance; 
};

struct wheel {
    long wheel_timestamp;
    double wheel_frequency; 
    int wheel_speed;
    long wheel_impulsce_count;
    long wheel_distance;
    double wheel_circumference;
    int wheel_tooth;
};

gps readgps(const std::string& rBuffer);
std::vector<gps> wypelnij (std::string filename);
void findmaxstrikespeedingpsdata(std::string filename);

void calibrate(std::vector<gps> gps_data,std::vector<wheel> wheel_data);

std::vector<wheel> adamdump(std::vector<gps> &gps_data){
    std::vector<wheel> wheel_data;
    for (int i =0;i< gps_data.size(); i++){
        wheel_data[i].wheel_timestamp=gps_data[i].gps_timestamp;
        
    }

}

int main (){
    std::vector<gps> gps_data = wypelnij("strike");
    
    std::vector<wheel> wheel_data = adamdump (gps_data);
    


    std::cout<< gps_data.size()<<std::endl;
    for (int i =0;i< gps_data.size(); i++){
        std::cout << gps_data[i].gps_timestamp;
    }

    return 0;
}




std::vector<gps> wypelnij (std::string filename){
    std::vector<gps> gps_data;
    std:: ifstream gps_file(filename);
    std::string line;
    while (std::getline(gps_file, line))
    {
       gps_data.push_back(readgps(line));
    }
}

gps readgps(const std::string& rBuffer) {
    gps gps;
    gps.gps_timestamp = std::stoll(rBuffer.substr(0, 13));

    std::istringstream stream(rBuffer.substr(13));
    std::string token;

    std::getline(stream, token, '=');
    std::getline(stream, token, '|');
    gps.gps_speed = std::stoi(token) * 1.852;

    std::getline(stream, token, 'N');
    gps.gps_n = std::stof(token);

    std::getline(stream, token, '|');
    std::getline(stream, token, 'E');
    gps.gps_e = std::stof(token);

    std::getline(stream, token, '|');
    std::getline(stream, token, '|');
    std::getline(stream, token, '|');
    gps.gps_distance = std::stoi(token) * 0,521; //wartosc oszacowana

    return gps;
}

void findmaxstrikespeedingpsdata (std::string filename){
    std::vector<gps> gps_data = wypelnij(filename); //zmien nazwe pliku w jakim chcesz znalezc dane
    int currentstrike = 0;
    int maxstrike = 0;
    int strikebegin = 0;

    for (int i = 0 ;i<gps_data.size();i++){
        if (gps_data[i].gps_speed == gps_data[i+1].gps_speed){
            if (gps_data[i].gps_speed != 0){
                currentstrike ++;
            }    
        }else{
            if (maxstrike<currentstrike){
                maxstrike=currentstrike;
                strikebegin = i - maxstrike;                 
            }
            currentstrike = 0;
        }
    }
    std::cout<< "strike: "<<maxstrike<<" range: " << strikebegin << " - " << strikebegin +maxstrike << std::endl;
}