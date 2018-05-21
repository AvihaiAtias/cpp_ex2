//
// Created by aviha on 18/05/2018.
//

#ifndef EX2_TRASPORTSYSTEM_H
#define EX2_TRASPORTSYSTEM_H

#include <iostream>
#include <list>
#include <vector>
#include "Station.h"
#include "Vehicle.h"
using namespace std;
class TransportSystem {
    list<Station*> graph;
    TransportSystem* createGraphWithSameVertex();
    void dijkstraSupport(Station* source,indexOfVehicle index);
    void dijkstraPremiumAlgorithm(Station* source);
    void makeAllInf();
    indexOfVehicle getOptVehicle(Station* source,Station* target);
    Station* findStationList(list<Station*>& stlist,const string& stationName);
    Station* giveMinVertex(list<Station*> slist,indexOfVehicle index);
    size_t* edgeWeightTotalCalculation(Station* source,Station* target);
    public:
    void dijkstraAlgorithm(Station* source); //return to private
    Station* findStationIfExist(const string& sourceName); //return to private
    TransportSystem(){} //update avihai
    void addStation(const string& sourceName,const string& targetName,size_t weight,indexOfVehicle Index);//update avihai about index (DONE)
    TransportSystem* reverseEdges();//return the graph after reverse all edges (DONE)
    TransportSystem(const TransportSystem& rhs);
    TransportSystem& operator=(const TransportSystem& rhs);
    TransportSystem(TransportSystem&& rhs);
    TransportSystem&& operator=(TransportSystem&& rhs);
    void uniExpress(Station& source,Station& target);
    void print(); //(DONE)
};


#endif //EX2_TRASPORTSYSTEM_H
