//
// Created by aviha on 18/05/2018.
//

#ifndef EX2_IOMANAGER_H
#define EX2_IOMANAGER_H
class Vaidations;
#include <iostream>
#include <map>
#include "TransportSystem.h"

using namespace std;

class IOmanager {
    TransportSystem* graph;
    map<string,ifstream*> inputfiles;
    ifstream* configFile;
    ofstream* outputFile;
    ifstream* loadFile;
    size_t busWait;
    size_t tramWait;
    size_t sprinterWait;
    size_t railWait;
    size_t ICTransit;
    size_t CSTransit;
    size_t StadTransit;

    void parseTheConfigFile();
    void parseTheDataFromFile(ifstream* fin,const string& filename);
    void waitForMoreInstructions();
    indexOfVehicle whichTypeOfVehicle(const string& filename);
    void arrangeTheInputFiles(int argc,char* argv[]);
    void run(int argc,char* argv[]);
    void buildTheGraphFromTheInputFiles();
    void loadFilePrepare(const string& fileName);
    void takeTheConfigFile(string filename);
    void takeTheOutputFile(string filename);
    Station* returnStationIfExistByName(const string& name);
public:
    IOmanager(int argc,char* argv[]);
    void arrangeTheConfigAndOutput(int argc,char* argv[]);
    virtual ~IOmanager();
    void load(const string& fileName);
    void outboundCommandActivated(const string &station);
    void inboundCommandActivated(const string &station);
    void uniExpressCommandActivated(const string& source,const string& target);
    void multiExpressCommandActivated(const string& source,const string& target);
};


#endif //EX2_IOMANAGER_H
