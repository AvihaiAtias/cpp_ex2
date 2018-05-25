//
// Created by aviha on 18/05/2018.
//
/**
 * object extends the vehicle and overriding the method
 */
#ifndef EX2_BUS_H
#define EX2_BUS_H

#include "Vehicle.h"

class Bus : public Vehicle{
    static int BusStopTime;

public:
    Bus():Vehicle{}{}
    Bus(size_t weight):Vehicle{weight}{}
    virtual int getStopTime(){return BusStopTime;}
    static void setStopTime(int stop){BusStopTime = stop;}

};

#endif //EX2_BUS_H
