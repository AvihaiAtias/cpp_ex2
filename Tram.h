//
// Created by aviha on 18/05/2018.
//
/**
 * object extends the vehicle and overriding the method
 */
#ifndef EX2_TRAM_H
#define EX2_TRAM_H


#include "Vehicle.h"

class Tram : public Vehicle{
    static int TramStopTime;

public:
    Tram():Vehicle{}{}
    Tram(size_t weight):Vehicle{weight}{}
    virtual int getStopTime(){return TramStopTime;}
    static void setStopTime(int stop){TramStopTime = stop;}
};
#endif //EX2_TRAM_H
