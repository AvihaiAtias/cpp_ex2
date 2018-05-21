//
// Created by aviha on 18/05/2018.
//

#include "IOmanager.h"
#include "Exceptions.h"
#include <string>
#include <vector>

//TODO match the station file for this constructor.
IOmanager::IOmanager(int argc,char* argv[]):graph{},inputfiles{},configFile{new fstream()},loadFile{new fstream()},
                    outputFile{new fstream()},busWait{2},tramWait{3},sprinterWait{4},railWait{5},
                    ICTransit{15},CSTransit{5},StadTransit{10}{
    try{
        Validations::inputFilesArrangment(argc,argv,inputfiles);
        Validations::filesFilter(argc,argv,inputfiles);
        arrangeTheConfigAndOutput(argc,argv);

        //TODO build the graph here

        waitForMoreInstructions();
    }catch(NoSuchFileExist e){
        exit(1);
    }

}
void IOmanager::waitForMoreInstructions(){
    string temp = "";
    string loadCommand = "";
    string fileName = "";
    do{
        cin >> temp;
    }while(temp != "");

    stringstream ss(temp);
    ss >> loadCommand >> fileName;

    if(loadCommand != "load")
        throw LoadedFileException("ERROR opening the specified file.");

    load(fileName);

}
void IOmanager::takeTheInputFile(){
    map<string,fstream*>::iterator it;
    fstream* currfile;
    for(it = inputfiles.begin();it != inputfiles.end(); it++){
        parseTheDataFromFile(it->second,it->first);
    }

}
void IOmanager::load(const string& fileName) {
    loadFile->open(fileName,ios_base::in);
    if(!loadFile->is_open())
        throw LoadedFileException("ERROR opening the specified file.");

    parseTheDataFromFile(loadFile,fileName);
    loadFile->close();
    cout << "Update was successful.";

}
indexOfVehicle IOmanager::whichTypeOfVehicle(const string& filename){
    string temp = filename;
    if(temp.find_first_not_of("bus") == 3) return bus;
    else if(temp.find_first_not_of("tram") == 4) return tram;
    else if(temp.find_first_not_of("sprinter") == 8) return sprinter;
    else if(temp.find_first_not_of("rail") == 4)return rail;
}
void IOmanager::parseTheDataFromFile(fstream* fin,const string& filename){
    string line = "";
    indexOfVehicle type = whichTypeOfVehicle(filename);
    size_t weight;
    vector<string> lineData;
    while(!fin->eof()){
        getline(*fin,line,'\n');
        Validations::returnLineIfCorrect(line,lineData);
        stringstream ss(lineData[2]);
        ss >> weight;

        graph.addStation(lineData[0],lineData[1],weight,type);

        lineData.clear();
    }

}
void IOmanager::arrangeTheConfigAndOutput(int argc,char* argv[]){
    string outputFile = "";
    string configFile = "";
    for(int i = 1;i<argc ; i++){
        if(argv[i] == "-c") configFile = argv[i+1];
        else if(argv[i] == "-o") outputFile = argv[i+1];
    }
    if(outputFile == "")outputFile = "output.dat";
    if(configFile != "") takeTheConfigFile(configFile);
    takeTheOutputFile(outputFile);
}
void IOmanager::takeTheConfigFile(string filename){
    try{
        configFile->open(filename,ios_base::in);
        if(!configFile)throw FileNotOpenException("problem with the config file - set the default definitions");
    }catch (FileNotOpenException e){return;}

    parseTheConfigFile();
    configFile->close();
}
void IOmanager::parseTheConfigFile(){
    string type;
    int value;
    while(!configFile->eof()){
      char buffer[20] = {0};
      configFile->getline(buffer,20,'\n');
      stringstream ss(buffer);
      ss >> type >> value;
      if(type == "bus") busWait = value;
      else if(type == "tram") tramWait = value;
      else if(type == "sprinter") sprinterWait = value;
      else if(type == "rail") railWait = value;
      else if(type == "intercity") ICTransit = value;
      else if(type == "stad") StadTransit = value;
      else if(type == "centraal") CSTransit = value;
    }
}
void IOmanager::takeTheOutputFile(string filename){
    try{
        outputFile->open(filename,ios_base::app);
        if(!outputFile)throw FileNotOpenException("problem with the output file");
    }catch (FileNotOpenException e){exit(1);}
}

IOmanager::~IOmanager(){
    delete configFile;
    delete outputFile;
    delete loadFile;
}