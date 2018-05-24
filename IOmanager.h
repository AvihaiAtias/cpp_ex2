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
    TransportSystem* graph;
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
    Station* returnStationIfExistByName(const string& name);
    void printMenu();
    void arrangeTheInputFiles(int argc,char* argv[]);
    void run(int argc,char* argv[]);
    void buildTheGraphFromTheInputFiles();
    void loadFilePrepare(const string& fileName);
    void disributionFunction(const int& choose);
public:
    IOmanager(int argc,char* argv[]);
    void arrangeTheConfigAndOutput(int argc,char* argv[]);
    void takeTheConfigFile(string filename);
    void takeTheOutputFile(string filename);
    void takeTheInputFile();
    virtual ~IOmanager();
    void load(const string& fileName);//TODO checks and valids of lines and create the stations after
    void outboundCommandActivated(const string &station);
    void inboundCommandActivated(const string &station);
    void uniExpressCommandActivated(const string& source,const string& target);
    void multiExpressCommandActivated(const string& source,const string& target);
};


#endif //EX2_IOMANAGER_H
