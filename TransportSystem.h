//
// Created by aviha on 18/05/2018.
//

#ifndef EX2_TRASPORTSYSTEM_H
#define EX2_TRASPORTSYSTEM_H

#include <iostream>
#include <list>
#include "Station.h"

using namespace std;

class TransportSystem {
    list<Station*> graph;
    Station* findStationIfExist(const string& sourceName);
    list<Station*>& dijkstraAlgorithm(Station& source,indexOfVehicle);
    list<Station*>& dijkstraPremiumAlgorithm(Station& source);
public:
    void addStation(const string& sourceName,const string& targetName,int weight);
    TransportSystem& reverseEdges();//return the graph after reverse all edges
    TransportSystem(const TransportSystem& rhs);
    TransportSystem& operator=(const TransportSystem& rhs);
    void uniExpress(Station& source,Station& target);
    void print()const;

};


#endif //EX2_TRASPORTSYSTEM_H
