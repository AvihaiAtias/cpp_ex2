//
// Created by aviha on 18/05/2018.
//

#include "IOmanager.h"
#include "Exceptions.h"
#include <string>
#include <vector>

//TODO match the station file for this constructor.
IOmanager::IOmanager(int argc,char* argv[]):inputfiles{},configFile{new fstream()},loadFile{new fstream()},
                    outputFile{new fstream()},busWait{2},tramWait{3},sprinterWait{4},railWait{5},
                    ICTransit{15},CSTransit{5},StadTransit{10}{
    run(argc,argv);
}
void IOmanager::run(int argc,char* argv[]){
    try{
        Validations::isThereFileExist(argc,argv);
        arrangeTheInputFiles(argc,argv);
        arrangeTheConfigAndOutput(argc,argv);
        graph = new TransportSystem(busWait,tramWait,sprinterWait,railWait,ICTransit,StadTransit,CSTransit);
        buildTheGraphFromTheInputFiles();
        waitForMoreInstructions();
    }catch(NoSuchFileExist e){
        exit(1);
    }catch(ArgumentsAmountError e){
        exit(1);
    }
}
void IOmanager::buildTheGraphFromTheInputFiles(){
    map<string,fstream*>::iterator begin = inputfiles.begin();
    map<string,fstream*>::iterator last = inputfiles.end();

    while(begin != last){
        parseTheDataFromFile(begin->second,begin->first);
        ++begin;
    }
}
void IOmanager::arrangeTheInputFiles(int argc,char* argv[]){
    string str;
    for (int i = 1; i < argc; i++) {
        str = argv[i];
        if(str == "-c" || str == "-o") {
            ++i;
            continue;
        }
        try{
            Validations::isNameStartWithVehicle(str);
        }catch (NameFileIsUnCorrect e) {
            continue;
        }
        fstream* fin = new fstream(argv[i], ios_base::in);
        if (fin) {
            inputfiles.insert(std::pair<string,fstream*>(argv[i],fin));
            fin->close();
            continue;
        }else{ //unCorrect file was found and will be ignored
            try{
                stringstream ss;
                ss << " the file: '" << argv[i] << "' is uncorrect and will be ignored";
                throw FileNotOpenException(ss.str());
            }catch (FileNotOpenException e){
                continue;
            }
        }
    }
}
void IOmanager::loadFilePrepare(const string& fileName){
    try{
        Validations::isNameStartWithVehicle(fileName);
        load(fileName);
    }catch (exception e){
        throw LoadedFileException(e.what());
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
void IOmanager::outboundCommandActivated(const string& station){
    Station* temp = graph->findStationIfExist(station);
    if(temp  == nullptr)
        throw IllegalStation("station source doesn`t exist");

    graph->outbound(temp);
}
void IOmanager::inboundCommandActivated(const string& station){
    Station* temp = graph->findStationIfExist(station);
    if(temp  == nullptr)
        throw IllegalStation("station target doesn`t exist");

    graph->inbound(temp);
}
void IOmanager::uniExpressCommandActivated(const string& source,const string& target){
    Station* sourceStation = graph->findStationIfExist(source);
    Station* targetStation = graph->findStationIfExist(target);
    if(sourceStation  == nullptr)
        throw IllegalStation("station source doesn`t exist");
    if(targetStation  == nullptr)
        throw IllegalStation("station target doesn`t exist");
    graph->uniExpress(sourceStation,targetStation);
}
void IOmanager::multiExpressCommandActivated(const string& source,const string& target){
    Station* sourceStation = graph->findStationIfExist(source);
    Station* targetStation = graph->findStationIfExist(target);
    if(sourceStation  == nullptr)
        throw IllegalStation("station source doesn`t exist");
    if(targetStation  == nullptr)
        throw IllegalStation("station target doesn`t exist");
    graph->multiExpress(sourceStation,targetStation);
}
void IOmanager::waitForMoreInstructions(){
    string inst;
    stringstream instruction;
    string command = "";
    string srcStation = "";
    string tgtStation = "";
    while(true){
        printMenu();
        cin >> inst;
        instruction << inst;
        instruction >> command;
        try{
            if(command == "print"){
                graph->print();
            }else if(command == "QUIT"){
                return;
            }
            else if(command == "outbound"){
                instruction >> srcStation;
                outboundCommandActivated(srcStation);
            }else if(command == "inbound"){
                instruction >> srcStation;
                inboundCommandActivated(srcStation);
            }else if(command == "uniExpress"){
                instruction >> tgtStation;
                uniExpressCommandActivated(srcStation,tgtStation);
            }else if(command == "multiExpress"){
                instruction >> tgtStation;
                multiExpressCommandActivated(srcStation,tgtStation);
            }else if(command == "load"){
                loadFilePrepare(srcStation);
            }
        }catch (IllegalStation e){
            continue;
        }catch (LoadedFileException e){
            continue;
        }
    }
}
void IOmanager::printMenu(){
    cout << "~~~~~~~~~ MENU ~~~~~~~~~~" << endl;
    cout << "1. Load File " << endl;
    cout << "2. uniExpress " << endl;
    cout << "3. multiExpress " << endl;
    cout << "4. inbound " << endl;
    cout << "5. outbound " << endl;
    cout << "6. exit" << endl;
}

Station* IOmanager::returnStationIfExistByName(const string& name){
    Station* station = nullptr;
    if((station = graph->findStationIfExist(name)) == nullptr)
        throw IllegalStation("this station doesn`t exist!");
    return station;
}
void IOmanager::takeTheInputFile(){
    map<string,fstream*>::iterator it;
    fstream* currfile;
    for(it = inputfiles.begin();it != inputfiles.end(); it++){
        parseTheDataFromFile(it->second,it->first);
    }

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

        graph->addStation(lineData[0],lineData[1],weight,type);

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