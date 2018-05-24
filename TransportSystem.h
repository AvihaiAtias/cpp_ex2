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
#include "Bus.h"
#include "Tram.h"
#include "Sprinter.h"
#include "Rail.h"
using namespace std;
class TransportSystem {
public:
    void recursiveMultiExpress(Station *Vertex);
    list<Station*> graph;
    TransportSystem* createGraphWithSameVertex();
    void dijkstraSupport(TransportSystem *graph2,Station* source,indexOfVehicle index);
    string getNameByIndex(indexOfVehicle index);
    void makeAllInf(TransportSystem *graph2);
    void printAllTheStationWithTravle(const list<Station*> *graph2,Station* source,const string& NoTravleMessage);
    indexOfVehicle getOptVehicle(Station* source,Station* target);
    Station* findStationList(list<Station*>& stlist,const string& stationName);
    Station* giveMinVertexByIndex(list<Station*> slist,indexOfVehicle index);
    size_t* edgeWeightTotalCalculation(Station* source,Station* target);
    Station* giveMinVertex(list<Station*> slist);
    void inboundSupport(const list<Station*> *graph2,Station *source);

public:
    void multiExpress(Station *source,Station* target);
    void inbound(Station* source);
    void outbound(Station* source);
    void dijkstraPremiumAlgorithm(Station* source);
    void dijkstraAlgorithm(TransportSystem *graph2,Station *source);
    Station* findStationIfExist(const string& sourceName); //return to private
    TransportSystem(){}
    TransportSystem(size_t bus,size_t tram,size_t sprinter,size_t rail,
                    size_t ICTransit,size_t StadTransit,size_t CSTransit);

    void addStation(const string& sourceName,const string& targetName,size_t weight,indexOfVehicle Index);//update avihai about index (DONE)
    TransportSystem* reverseEdges();//return the graph after reverse all edges (DONE)
    TransportSystem(const TransportSystem& rhs);
    TransportSystem& operator=(const TransportSystem& rhs);
    TransportSystem(TransportSystem&& rhs);
    TransportSystem&& operator=(TransportSystem&& rhs);
    void uniExpress(Station* source,Station* target);
    void print();
};


#endif //EX2_TRASPORTSYSTEM_H