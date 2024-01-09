#ifndef STRUCTURES_H
#define STRUCTURES_H

struct gps {
    long long gps_timestamp;
    int gps_speed; //pos (predkosc wezly)
    float gps_n;
    float gps_e;
    int gps_distance;

    //1701624000193	POS=63|52.423230 N|18.597110 E|2023-12-03 18:20:04|7211991|2023-11-29 17:49:09|;
};

struct wheel {
    long long wheel_timestamp;
    double wheel_frequency; //pos (predkosc wezly)
    int wheel_speed;
    long wheel_impulsce_count;
    long wheel_distance;
    double wheel_circumference;
    int wheel_tooth;
    //1701624000192	LOG=01|910.000000|118|14296573|514148|2733.185609|76|;
};

#endif 