//
// Created by aviha on 18/05/2018.
//

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
int Bus::BusStopTime = 2;

#endif //EX2_BUS_H
