//
// Created by aviha on 18/05/2018.
//
/**
 * object extends the vehicle and overriding the method
 */
#ifndef EX2_SPRINTER_H
#define EX2_SPRINTER_H


#include "Vehicle.h"

class Sprinter : public Vehicle {
    static int SprinterStopTime;
public:
    Sprinter():Vehicle{}{}
    Sprinter(size_t weight):Vehicle{weight}{}

    virtual int getStopTime(){return SprinterStopTime;}
    static void setStopTime(int stop){SprinterStopTime = stop;}
};


#endif //EX2_SPRINTER_H
