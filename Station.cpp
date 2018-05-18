//
// Created by aviha on 18/05/2018.
//

#include "Station.h"
#include "Bus.h"
#include "Tram.h"
#include "Sprinter.h"
#include "Rail.h"

size_t Station::IC_TRANSIT_TIME = 15;
size_t Station::STAD_TRANSIT_TIME = 10;
size_t Station::CS_TRANSIT_TIME = 5;

Station::Station(string name):name{name},vehicles{new Vehicle*[4]}{
    init();
}
void Station::init() {
    vehicles[bus] = new Bus();
    vehicles[tram] = new Tram();
    vehicles[sprinter] = new Sprinter();
    vehicles[rail] = new Rail();

    if(name.find_first_not_of("IC") == 2) currLocation = intercity;
    else if(name.find_first_not_of("CS") == 2) currLocation = centraal;
    else currLocation = stad;
}
size_t Station::getcurrTransitTime()const{
    switch(currLocation){
        case intercity:
            return IC_TRANSIT_TIME;
        case stad:
            return STAD_TRANSIT_TIME;
        case centraal:
            return CS_TRANSIT_TIME;
    }
}