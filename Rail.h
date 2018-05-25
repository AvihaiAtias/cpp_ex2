//
// Created by aviha on 18/05/2018.
//
/**
 * object extends the vehicle and overriding the method
 */
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

#endif //EX2_RAIL_H
