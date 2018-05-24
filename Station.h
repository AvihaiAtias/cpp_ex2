//
// Created by aviha on 18/05/2018.
//

#ifndef EX2_STATION_H
#define EX2_STATION_H
#include <iostream>
#include <list>
#include "Vehicle.h"
#include "TransportSystem.h"
#include <memory>

using namespace std;

typedef enum{intercity = 0,stad,centraal}location;
class Station {
public://TODO remove
    static const int NUM_OF_VEHICLES = 4;
    static size_t locationKey[3];
    static size_t IC_TRANSIT_TIME;
    static size_t STAD_TRANSIT_TIME;
    static size_t CS_TRANSIT_TIME;
    string name;
    location currLocation;
    shared_ptr<Vehicle> vehicles[NUM_OF_VEHICLES];
    list<Station*> adjacent;    //reached by me
    void init();
    friend class TransportSystem;
public:
    Station* findIfStationExistInList(const string &StationName); //TODO AND ADD TO AVIHAI
    Station(string name,indexOfVehicle index,size_t weight);//TODO AND ADD TO AVIHAI
    Station(string name);
    static size_t getIC_TRANSIT_TIME() {
        return IC_TRANSIT_TIME;
    }

    static void setIC_TRANSIT_TIME(size_t IC_TRANSIT_TIME) {
        Station::IC_TRANSIT_TIME = IC_TRANSIT_TIME;
    }

    static size_t getSTAD_TRANSIT_TIME() {
        return STAD_TRANSIT_TIME;
    }

    static void setSTAD_TRANSIT_TIME(size_t STAD_TRANSIT_TIME) {
        Station::STAD_TRANSIT_TIME = STAD_TRANSIT_TIME;
    }

    static size_t getCS_TRANSIT_TIME() {
        return CS_TRANSIT_TIME;
    }

    static void setCS_TRANSIT_TIME(size_t CS_TRANSIT_TIME) {
        Station::CS_TRANSIT_TIME = CS_TRANSIT_TIME;
    }

    const string &getName() const {
        return name;
    }

    location getCurrLocation() const {
        return currLocation;
    }
    size_t getcurrTransitTime()const;

    shared_ptr<Vehicle> getVehicles(){
        return *vehicles;
    }

};


#endif //EX2_STATION_H