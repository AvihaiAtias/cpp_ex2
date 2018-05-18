//
// Created by aviha on 18/05/2018.
//

#ifndef EX2_VEHICLE_H
#define EX2_VEHICLE_H
#include <iostream>
#include "Station.h"

using namespace std;

class Vehicle{
    size_t time_Weight;
    Station* parent;
public:
    Vehicle():time_Weight{0}{}
    Vehicle(size_t time):time_Weight{time}{}

    virtual int getStopTime() = 0;

    size_t getTime_Weight() const {
        return time_Weight;
    }

    void setTime_Weight(size_t time_Weight) {
        Vehicle::time_Weight = time_Weight;
    }
};


#endif //EX2_VEHICLE_H
