//
// Created by aviha on 18/05/2018.
//

#ifndef EX2_RAIL_H
#define EX2_RAIL_H


#include "Vehicle.h"

class Rail : public Vehicle {
    static int RailstopTime;

public:
    Rail():Vehicle{}{}
    Rail(size_t weight):Vehicle{weight}{}
    virtual int getStopTime(){return RailstopTime;}
    static void setStopTime(int stop){RailstopTime = stop;}
};

int Rail::RailstopTime = 5;

#endif //EX2_RAIL_H
