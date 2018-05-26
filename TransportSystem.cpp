//
// Created by aviha on 18/05/2018.
//

#include "TransportSystem.h"
#include "Station.h"
#include "Bus.h"
#include "Tram.h"
#include "Sprinter.h"
#include "Rail.h"
#include <limits>

/*function that get source station, target station and weight and create new edge*/

TransportSystem::TransportSystem(size_t bus1,size_t tram1,size_t sprinter1,size_t rail1,
        size_t ICTransit1,size_t StadTransit1,size_t CSTransit1){
        Bus::setStopTime(bus1);
        Tram::setStopTime(tram1);
        Sprinter::setStopTime(sprinter1);
        Rail::setStopTime(rail1);

        Station::CS_TRANSIT_TIME = CSTransit1;
        Station::IC_TRANSIT_TIME = ICTransit1;
        Station::STAD_TRANSIT_TIME = StadTransit1;
}
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
    if(StationInList->vehicles[Index]->getTime_Weight() == 0 ){
        StationInList->vehicles[Index]->setTime_Weight(weight);
    }
    else if(StationInList->vehicles[Index]->getTime_Weight()>weight && StationInList->vehicles[Index]->getTime_Weight()!=0)
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
        }
    }
    return newGraph; //return the new graph
}
/*function that create new graph with same vertexs from the original graph*/
TransportSystem* TransportSystem::createGraphWithSameVertex(){
    list<Station*>::iterator begin = graph.begin();
    list<Station*>::iterator end = graph.end();
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
    list<Station *>::const_iterator begin = graph.begin();
    list<Station *>::const_iterator end = graph.end();
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
void TransportSystem::dijkstraAlgorithm(TransportSystem *graph2,Station *source) {
    makeAllInf(graph2);//initialization all the station in infinite
    for(int i = 0; i < 4 ; i++)source->vehicles[i]->time_Weight = 0;
    dijkstraSupport(graph2,source,bus); //dijkstra in bus graph
    dijkstraSupport(graph2,source,tram);
    dijkstraSupport(graph2,source,sprinter);
    dijkstraSupport(graph2,source,rail);
}
/*function that get list of station and name of station and find single station in the list*/
Station* TransportSystem::findStationList(list<Station*>& stlist,const string& stationName){
    list<Station*>::iterator begin = stlist.begin();
    list<Station*>::iterator end = stlist.end();

    for(;begin != end; begin++){
        if((*begin)->getName() == stationName){ //equal station in list with the string name that she get
            return *begin;
        }
    }
    return nullptr;
}
/*function that get station and index of vehicle and do dijkstra on the graph*/
void TransportSystem::dijkstraSupport(TransportSystem *graph2,Station* source,indexOfVehicle index){

    size_t currWeight = 0;
    Station* point2Station = source;
    Station* point2MainVertex = nullptr;
    Station* minAdjacent = nullptr;
    list<Station*>::iterator beginIn;
    list<Station*>::iterator endIn;

    list<Station*> stlist(graph2->graph.begin(),graph2->graph.end());

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

            point2MainVertex = graph2->findStationIfExist((*beginIn)->name);
            if(point2MainVertex->vehicles[index]->time_Weight > currWeight && point2MainVertex->vehicles[index]->time_Weight != 0){
                point2MainVertex->vehicles[index]->time_Weight = currWeight;
                point2MainVertex->vehicles[index]->parent = point2Station;
            }
        }
        stlist.remove(point2Station);
        if(minAdjacent){
            point2Station = findStationList(stlist,minAdjacent->getName());
            if(!point2Station)
                point2Station=giveMinVertexByIndex(stlist,index);
        }
        else
            point2Station = giveMinVertexByIndex(stlist,index);
        minAdjacent = nullptr;
    }
}
/*function that get station pointer and index and return the station that the station */
Station* TransportSystem::giveMinVertexByIndex(list<Station*> slist,indexOfVehicle index){
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
    makeAllInf(this);
    for(int i = 0; i < 4 ; i++)source->vehicles[i]->time_Weight = 0;
    Station* Point2Station = source;
    Station *edgeToVertex = nullptr;
    size_t* elaborateWeightArray;
    list<Station*>::iterator beginIn;
    list<Station*>::iterator endIn;
    int MinIndex = -1;

    list<Station*> stlist(graph.begin(),graph.end());
    while(!stlist.empty()){
        beginIn = Point2Station->adjacent.begin();
        endIn = Point2Station->adjacent.end();
        for(;beginIn!=endIn;beginIn++){
            elaborateWeightArray = edgeWeightTotalCalculation(Point2Station,*beginIn);
            if(elaborateWeightArray == nullptr){return;}
            for(int i=0;i<4;i++){
                if(MinIndex == -1 && elaborateWeightArray[i] != -1)
                    MinIndex=i;
                else if(MinIndex != -1 && elaborateWeightArray[i]<elaborateWeightArray[MinIndex] )
                    MinIndex = i;
            }
            edgeToVertex = findStationIfExist((*beginIn)->name);
            if(!edgeToVertex){
                cout<<"somthing wrong!!!!"<<endl;
                exit(1);
            }
            for(int i=0;i<4;i++){
                if(edgeToVertex->vehicles[i]->time_Weight == numeric_limits<int>::max()&&i!=MinIndex)
                    continue;
                else if(edgeToVertex->vehicles[i]->time_Weight>elaborateWeightArray[MinIndex]&&i!=MinIndex){
                    edgeToVertex->vehicles[i]->time_Weight= numeric_limits<int>::max();
                }
                else if(edgeToVertex->vehicles[i]->time_Weight>elaborateWeightArray[MinIndex]&&i==MinIndex){
                    edgeToVertex->vehicles[i]->time_Weight= elaborateWeightArray[MinIndex];
                    edgeToVertex->vehicles[i]->parent=Point2Station;
                }
            }
        }
        stlist.remove(Point2Station);
        Point2Station = giveMinVertex(stlist);
        if(!Point2Station)
            return;
    }
}
void TransportSystem::makeAllInf(TransportSystem *graph2){
    int inf = numeric_limits<int>::max();
    list<Station*>::iterator begin = graph2->graph.begin();
    list<Station*>::iterator end = graph2->graph.end();
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
    size_t* elaborateWeightArray = new size_t[4];
    int i = 0;
    bool roadExistFlag = false;
    for(i = 0 ; i < 4 ; i++){
        if(source->vehicles[i]->time_Weight != numeric_limits<int>::max()){
            roadExistFlag = true;
            break;
        }
    }
    if(!roadExistFlag){//there are no ways to the target station
        return nullptr;
    }
    for(int j = 0 ; j < 4 ; j++){
        if(target->vehicles[j]->time_Weight == 0){
            elaborateWeightArray[j] = -1;
            continue;
        }
        if(j != i && source->vehicles[i]->time_Weight != 0){ /*-------------------*/
            elaborateWeightArray[j] = source->vehicles[i]->time_Weight+target->vehicles[j]->time_Weight+target->vehicles[j]->getStopTime()+(source->locationKey[source->currLocation]);
            continue;
        }
        elaborateWeightArray[j] = source->vehicles[i]->time_Weight + target->vehicles[j]->time_Weight+target->vehicles[j]->getStopTime();
    }
    return elaborateWeightArray;
}
Station* TransportSystem::giveMinVertex(list<Station*> slist){
    list<Station*>::iterator begin;
    list<Station*>::iterator end = slist.end();
    Station* minStation = nullptr;
    int indexMin = -1;
    for(begin = slist.begin(); begin != end; begin++){
        for(int i=0;i<4;i++){
            if(minStation == nullptr && (*begin)->vehicles[i]->time_Weight!=numeric_limits<int>::max()){
                minStation = (*begin);
                indexMin = i;
                break;
            }
            else if(minStation != nullptr&&minStation->vehicles[indexMin]->time_Weight>(*begin)->vehicles[i]->time_Weight){
                minStation = (*begin);
                indexMin = i;
                break;
            }
        }

    }
    return minStation;
}
void TransportSystem::uniExpress(Station* source,Station* target){
    dijkstraAlgorithm(this,source); //call dijkstra algorithm
    for(int i=0;i<4;i++){
        if(target->vehicles[i]->time_Weight != numeric_limits<int>::max())
            cout<<getNameByIndex(static_cast<indexOfVehicle>(i))<<": "<<target->vehicles[i]->time_Weight<<endl;
        else
            cout<<getNameByIndex(static_cast<indexOfVehicle>(i))<<": route unavailable"<<endl;
    }
}
string TransportSystem::getNameByIndex(indexOfVehicle index){
    switch (index) {
        case bus:
            return "bus";
            break;
        case rail:
            return "rail";
            break;
        case sprinter:
            return "sprinter";
            break;
        case tram:
            return "tram";
            break;
        default:
            break;
    }
}
void TransportSystem::printAllTheStationWithTravle(const list<Station*> *graph2,Station* source,const string& NoTravleMessage){
    bool ifOneStationAtLeast=false;
    list<Station *>::const_iterator begin;
    list<Station *>::const_iterator end;
    for(int i=0;i<4;i++){
        begin= graph2->begin();
        end= graph2->end();
        for(;begin!=end;begin++){
            if((*begin)->name == source->name)continue;
            if((*begin)->vehicles[i]->time_Weight!=numeric_limits<int>::max()){
                ifOneStationAtLeast=true;
                break;
            }
        }
        cout<<getNameByIndex(static_cast<indexOfVehicle>(i))<<": ";
        if(ifOneStationAtLeast){
            ifOneStationAtLeast=false;
            begin=graph2->begin();
            end=graph2->end();
            for(;begin!=end;begin++){
                if((*begin)->name == source->name)continue;
                if((*begin)->vehicles[i]->time_Weight!=numeric_limits<int>::max())
                    cout<<(*begin)->name<<" ";
            }
            cout<<endl;
        }
        else
            cout<<NoTravleMessage<<endl;
    }
}
void TransportSystem::outbound(Station* source){
    dijkstraAlgorithm((this),source);
    printAllTheStationWithTravle(&graph, source, "no outbound travel");

}
void TransportSystem::inbound(const string& source){
    TransportSystem *reversGraph = reverseEdges();
    dijkstraAlgorithm(reversGraph,reversGraph->findStationIfExist(source));
    printAllTheStationWithTravle(&(reversGraph->graph), reversGraph->findStationIfExist(source), "no inbound travel");
}
void TransportSystem::multiExpress(Station *source,Station* target){
    bool ifEdgeExist=false;
    dijkstraPremiumAlgorithm(source);
    int j;
    for(j=0;j<4;j++)
        if(target->vehicles[j]->parent!=nullptr){ifEdgeExist=true;break;}
    if(!ifEdgeExist){cout<<"Travle not exist!"<<endl;return;}
    cout<<"Source Station: "<<source->name;
    recursiveMultiExpress(target);
    cout<<" (the travele time is "<<target->vehicles[j]->time_Weight<<")"<<endl;
}
void TransportSystem::recursiveMultiExpress(Station *Vertex){
    int i;
    if(Vertex->vehicles[0]->parent==nullptr&&Vertex->vehicles[1]->parent==nullptr&&Vertex->vehicles[2]->parent==nullptr&&Vertex->vehicles[3]->parent==nullptr)return;
    for(i=0;i<4;i++)
        if(Vertex->vehicles[i]->parent!=nullptr){recursiveMultiExpress(Vertex->vehicles[i]->parent);break;}
    cout<<" -> ["<<this->getNameByIndex(static_cast<indexOfVehicle>(i))<<"]"<<" -> "<<Vertex->name;
}