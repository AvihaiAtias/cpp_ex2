//
// Created by aviha on 18/05/2018.
//

#ifndef EX2_IOMANAGER_H
#define EX2_IOMANAGER_H
#include <iostream>
#include <fstream>
#include <map>
#include "Validations.h"
#include "TransportSystem.h"
#include "Vehicle.h"

using namespace std;

class IOmanager {
    TransportSystem graph;
    map<string,fstream*> inputfiles;
    fstream* configFile;
    fstream* outputFile;
    fstream* loadFile;
    size_t busWait;
    size_t tramWait;
    size_t sprinterWait;
    size_t railWait;
    size_t ICTransit;
    size_t CSTransit;
    size_t StadTransit;
    void parseTheConfigFile();
    void parseTheDataFromFile(fstream* fin,const string& filename);
    void waitForMoreInstructions();
    indexOfVehicle whichTypeOfVehicle(const string& filename);
public:
    IOmanager(int argc,char* argv[]);
    void arrangeTheConfigAndOutput(int argc,char* argv[]);
    void takeTheConfigFile(string filename);
    void takeTheOutputFile(string filename);
    void takeTheInputFile();
    virtual ~IOmanager();
    void load(const string& fileName);//TODO checks and valids of lines and create the stations after
};


#endif //EX2_IOMANAGER_H
