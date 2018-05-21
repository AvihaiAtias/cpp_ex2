#include <iostream>
#include <sstream>
#include "Station.h"
#include "Validations.h"
#include "IOmanager.h"
#include "TransportSystem.h"
#include "Station.h"

using namespace std;
int main(int argc,char* argv[]){
   // IOmanager iOmanager(argc,argv);
    TransportSystem *g = new TransportSystem();
    g->addStation("1","4",1,bus);
    g->addStation("2","3",2,bus);
    g->addStation("1","3",7,bus);
    g->addStation("2","4",8,bus);
    g->addStation("4","1",2,bus);
    g->addStation("4","3",1,bus);
    g->addStation("1","2",5,bus);
    g->print();
    g->dijkstraAlgorithm(g->findStationIfExist("1"));
    cout<<g->findStationIfExist("3")->vehicles[bus]->parent->getName()<<endl;
    cout<<g->findStationIfExist("3")->vehicles[bus]->time_Weight<<endl;
}