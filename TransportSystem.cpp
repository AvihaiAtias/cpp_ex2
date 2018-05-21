//
// Created by aviha on 18/05/2018.
//

#include "TransportSystem.h"
#include <limits>

/*function that get source station, target station and weight and create new edge*/



void TransportSystem::addStation(const string& sourceName,const string& targetName,size_t weight,indexOfVehicle Index){
    Station *SourceStation = findStationIfExist(sourceName); //check if source station exist
    Station *TargetStation = findStationIfExist(targetName);//check if target station exist
    if(!SourceStation){ //if source station not exist them create
        graph.push_back(new Station(sourceName));
        SourceStation = findStationIfExist(sourceName);
    }
    if(!TargetStation)//if target station not exist then create
        graph.push_back(new Station(targetName));
    Station *StationInList = SourceStation->findIfStationExistInList(targetName); //find if edge exist
    if(!StationInList){ //if edge not exist then create
        SourceStation->adjacent.push_back(new Station(targetName,Index,weight));
        return;
    }
    else if(StationInList->vehicles[Index]->getTime_Weight()>weight &&StationInList->vehicles[Index]->getTime_Weight()!=0)
        StationInList->vehicles[Index]->setTime_Weight(weight);
    //check if the new weight is soft more then previous weight
    return;
}
/*function that create new graph with revers edge*/
TransportSystem* TransportSystem::reverseEdges(){
    TransportSystem *newGraph = createGraphWithSameVertex(); //create new graph with same vertex
    list<Station*>::iterator begin=graph.begin();
    list<Station*>::iterator end=graph.end();
    for(;begin!=end;begin++){ //while that Passing all the vertex in the original graph
        string name = (*begin)->getName();
        list<Station*>::iterator beginIn = (*begin)->adjacent.begin();
        list<Station*>::iterator endIn = (*begin)->adjacent.end();
        for(;beginIn!=endIn;beginIn++){//while that Passing all the edge in the vertex and create revers edge in the new graph
            newGraph->addStation((*beginIn)->getName(), name,(*beginIn)->vehicles[bus]->getTime_Weight(), bus);
            newGraph->addStation((*beginIn)->getName(), name,(*beginIn)->vehicles[rail]->getTime_Weight(), rail);
            newGraph->addStation((*beginIn)->getName(), name,(*beginIn)->vehicles[tram]->getTime_Weight(), tram);
            newGraph->addStation((*beginIn)->getName(), name,(*beginIn)->vehicles[sprinter]->getTime_Weight(), sprinter);
        }//TODO *******
    }
    return newGraph; //return the new graph
}
/*function that create new graph with same vertexs from the original graph*/
TransportSystem* TransportSystem::createGraphWithSameVertex(){
    list<Station*>::iterator begin=graph.begin();
    list<Station*>::iterator end=graph.end();
    TransportSystem* newGraph = new TransportSystem(); //create new graph
    for(;begin!=end;begin++) //while that Passing all the vertex in the original graph
        newGraph->graph.push_back(new Station((*begin)->getName())); //add the vertex in the new graph
    return newGraph;
}
/*function that get source name station and return pointer its. if not exist return null pointer*/
Station* TransportSystem::findStationIfExist(const string& sourceName){
    list<Station*>::iterator begin=graph.begin();
    list<Station*>::iterator end=graph.end();
    for(;begin!=end;begin++){//while that Passing all the vertex in the original graph
        if((*begin)->getName() == sourceName)
            return *begin;
    }
    return nullptr;
}
/*function that print the graph*/
void TransportSystem::print() {
    list<Station *>::iterator begin = graph.begin();
    list<Station *>::iterator end = graph.end();
    for (; begin != end; begin++) {
        list<Station *>::iterator beginIn = (*begin)->adjacent.begin();
        list<Station *>::iterator endIn = (*begin)->adjacent.end();
        for (; beginIn != endIn; beginIn++) {
            cout << (*begin)->getName() << "->(bus:" << (*beginIn)->vehicles[bus]->getTime_Weight() << ")";
            cout << "->(rail:" << (*beginIn)->vehicles[rail]->getTime_Weight() << ")";
            cout << "->(tram:" << (*beginIn)->vehicles[tram]->getTime_Weight() << ")";
            cout << "->(sprinter:" << (*beginIn)->vehicles[sprinter]->getTime_Weight() << ")->" << (*beginIn)->getName() << endl;
        }
    }
}

void TransportSystem::dijkstraAlgorithm(Station *source) {
    makeAllInf();
    for(int i = 0; i < 4 ; i++)source->vehicles[i]->time_Weight = 0;
    dijkstraSupport(source,bus);
    dijkstraSupport(source,tram);
    dijkstraSupport(source,sprinter);
    dijkstraSupport(source,rail);
}

Station* TransportSystem::findStationList(list<Station*>& stlist,const string& stationName){
    list<Station*>::iterator begin = stlist.begin();
    list<Station*>::iterator end = stlist.end();

    for(;begin != end; begin++){
        if((*begin)->getName() == stationName){
            return *begin;
        }
    }
    return nullptr;
}

void TransportSystem::dijkstraSupport(Station* source,indexOfVehicle index){

    size_t currWeight = 0;
    Station* point2Station = source;
    Station* point2MainVertex = nullptr;
    Station* minAdjacent = nullptr;
    list<Station*>::iterator beginIn;
    list<Station*>::iterator endIn;

    list<Station*> stlist(graph.begin(),graph.end());

    while(!stlist.empty()){
        beginIn = point2Station->adjacent.begin();
        endIn = point2Station->adjacent.end();
        for(;beginIn != endIn ; beginIn++){
            if((*beginIn)->vehicles[index]->time_Weight == 0) continue;
            if(minAdjacent == nullptr || minAdjacent->vehicles[index]->time_Weight > (*beginIn)->vehicles[index]->time_Weight ){
                minAdjacent = *beginIn;
            }

            currWeight = point2Station->vehicles[index]->time_Weight +
                         (*beginIn)->vehicles[index]->time_Weight +
                         (*beginIn)->vehicles[index]->getStopTime();

            point2MainVertex = findStationIfExist((*beginIn)->name);
            //TODO DELETE in the end
            if(!point2MainVertex){
                cout << "Disaster!!" << endl;
                exit(1);
            }
            if(point2MainVertex->vehicles[index]->time_Weight > currWeight && point2MainVertex->vehicles[index]->time_Weight != 0){
                point2MainVertex->vehicles[index]->time_Weight = currWeight;
                point2MainVertex->vehicles[index]->parent = point2Station;
            }
        }
        stlist.remove(point2Station);
        if(minAdjacent)
            point2Station = findStationList(stlist,minAdjacent->getName());
        else
            point2Station = giveMinVertex(stlist,index);
        minAdjacent = nullptr;
    }
}
Station* TransportSystem::giveMinVertex(list<Station*> slist,indexOfVehicle index){
    list<Station*>::iterator begin;
    list<Station*>::iterator end = slist.end();
    Station* minStation = nullptr;
    for(begin = slist.begin(); begin != end; begin++){
        if(!minStation || minStation->vehicles[index]->time_Weight > (*begin)->vehicles[index]->time_Weight){
            minStation = *begin;
        }
    }
    return minStation;
}
void TransportSystem::dijkstraPremiumAlgorithm(Station* source){

}
indexOfVehicle TransportSystem::getOptVehicle(Station* source,Station* target){
    indexOfVehicle vehicleTypeOfSource;


}

void TransportSystem::makeAllInf(){
    int inf = numeric_limits<int>::max();
    list<Station*>::iterator begin = graph.begin();
    list<Station*>::iterator end = graph.end();
    for(;begin != end;begin++){
        (*begin)->vehicles[bus]->time_Weight = inf;
        (*begin)->vehicles[tram]->time_Weight = inf;
        (*begin)->vehicles[sprinter]->time_Weight = inf;
        (*begin)->vehicles[rail]->time_Weight = inf;

        (*begin)->vehicles[bus]->parent = nullptr;
        (*begin)->vehicles[tram]->parent = nullptr;
        (*begin)->vehicles[sprinter]->parent = nullptr;
        (*begin)->vehicles[rail]->parent = nullptr;
    }
}
size_t * TransportSystem::edgeWeightTotalCalculation(Station* source,Station* target){
    size_t* ArraySum = new size_t[4];
    int i = 0;
    bool flag = false;
    for(i = 0 ; i < 4 ; i++){
        if(source->vehicles[i]->time_Weight!=std::numeric_limits<int>::max()){
            flag = true;
            break;
        }
    }
    if(!flag){
        cout<<"somthing wrong!!"<<endl;
        return nullptr;
    }
    for(int j = 0 ; j < 4 ; j++){
        if(j != i){
            ArraySum[j] = source->vehicles[i]->time_Weight+target->vehicles[j]->time_Weight+target->vehicles[j]->getStopTime()+ source->locationKey[source->currLocation];
            continue;
        }
        ArraySum[j] = source->vehicles[i]->time_Weight + target->vehicles[j]->time_Weight+target->vehicles[j]->getStopTime();
    }
    return ArraySum;
}