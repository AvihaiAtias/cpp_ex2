//
// Created by aviha on 18/05/2018.
//

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
int Sprinter::SprinterStopTime = 4;

#endif //EX2_SPRINTER_H
