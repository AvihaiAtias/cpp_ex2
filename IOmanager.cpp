//
// Created by aviha on 18/05/2018.
//

#include "IOmanager.h"
#include "Validations.h"
#include <string>
#include <vector>
/**
 * c`tor initialized the all variables at the default values
 */
IOmanager::IOmanager(int argc,char* argv[]):inputfiles{},configFile{new ifstream()},loadFile{new ifstream()},
                    outputFile{new ofstream()},busWait{2},tramWait{3},sprinterWait{4},railWait{5},
                    ICTransit{15},CSTransit{5},StadTransit{10}{
    run(argc,argv);
}
/**
 * this function actually managed the all program from
 * opening and start the graph and to validations checks
 */
void IOmanager::run(int argc,char* argv[]){
    try{
        Validations::isThereFileExist(argc,argv);//check if there some one correct input file at least and the args amount
        arrangeTheInputFiles(argc,argv);//check the all inputfiles and keep the files in map <string filename,ifstream* file>
        arrangeTheConfigAndOutput(argc,argv);//check if there are config and output and match the values by it.
        graph = new TransportSystem(busWait,tramWait,sprinterWait,railWait,ICTransit,StadTransit,CSTransit); // create the graph
        buildTheGraphFromTheInputFiles(); //load all vertexes and edges by the correct files
        waitForMoreInstructions();//start listening to the user commands
    }catch(NoSuchFileExist e){
        exit(1);
    }catch(ArgumentsAmountError e){
        exit(1);
    }
}
/**
 * this method pass the all input files and send every file
 * to another method that parse the data
 */
void IOmanager::buildTheGraphFromTheInputFiles(){
    map<string,ifstream*>::iterator begin = inputfiles.begin();
    map<string,ifstream*>::iterator last = inputfiles.end();

    while(begin != last){
        parseTheDataFromFile(begin->second,begin->first);
        ++begin;
    }
}
/**
 * this method take every input file from the arguments -
 * check the name and the open correct, keep in map after the checks
 */
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
        ifstream* fin = new ifstream(argv[i]);
        if (fin) {
            inputfiles.insert(std::pair<string,ifstream*>(argv[i],fin));
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
/**
 * before loading the file(in running time) we checks
 * the name of the file that entered and load the file
 */
void IOmanager::loadFilePrepare(const string& fileName){
    try{
        Validations::isNameStartWithVehicle(fileName);
        load(fileName);
    }catch (exception e){
        throw LoadedFileException(e.what());
    }
}
/**
 * the load after checks
 */
void IOmanager::load(const string& fileName) {
    loadFile->open(fileName);
    if(!loadFile->is_open())
        throw LoadedFileException("ERROR opening the specified file.");

    parseTheDataFromFile(loadFile,fileName); //read the data from the file
    loadFile->close();
    cout << "Update was successful.";

}
/**
 * search the specific station and send it to the
 * outbound method after the foundation
 * @param station
 */
void IOmanager::outboundCommandActivated(const string& station){
    Station* temp = graph->findStationIfExist(station);
    if(temp  == nullptr)
        throw IllegalStation("station source doesn`t exist");

    graph->outbound(temp);
}
/**
 * same as outbound command
 */
void IOmanager::inboundCommandActivated(const string& station){
      Station* temp = graph->findStationIfExist(station);
      if(temp  == nullptr)
          throw IllegalStation("station target doesn`t exist");

        graph->inbound(station);

}
/**
 * prepare all conditions to start the uniExpress activation
 * we make sure that there are both legal stations
 * @param source name of vertex
 * @param target name of vertex
 */
void IOmanager::uniExpressCommandActivated(const string& source,const string& target){
    Station* sourceStation = graph->findStationIfExist(source);
    Station* targetStation = graph->findStationIfExist(target);
    if(sourceStation  == nullptr)
        throw IllegalStation("station source doesn`t exist");
    if(targetStation  == nullptr)
        throw IllegalStation("station target doesn`t exist");
    graph->uniExpress(sourceStation,targetStation);
}
/**
 * same as uniExpress
 */

void IOmanager::multiExpressCommandActivated(const string& source,const string& target){
    Station* sourceStation = graph->findStationIfExist(source);
    Station* targetStation = graph->findStationIfExist(target);
    if(sourceStation  == nullptr)
        throw IllegalStation("station source doesn`t exist");
    if(targetStation  == nullptr)
        throw IllegalStation("station target doesn`t exist");
    graph->multiExpress(sourceStation,targetStation);
}
/**
 * this method only listening to the user commands
 * and distribute every command to the right place
 */

void IOmanager::waitForMoreInstructions(){
    string inst;
    stringstream instruction;
    string command = "";
    string srcStation = "";
    string tgtStation = "";
    while(true){
        cin >> command;
        try{
            if(command == "print"){
                graph->print();
            }else if(command == "QUIT"){
                return;
            }
            else if(command == "outbound"){
                cin >> srcStation;
                outboundCommandActivated(srcStation);
            }else if(command == "inbound"){
                cin >> srcStation;
                inboundCommandActivated(srcStation);
            }else if(command == "uniExpress"){
                cin >> srcStation;
                cin >> tgtStation;
                uniExpressCommandActivated(srcStation,tgtStation);
            }else if(command == "multiExpress"){
                cin >> srcStation;
                cin >> tgtStation;
                multiExpressCommandActivated(srcStation,tgtStation);
            }else if(command == "load"){
                cin >> srcStation;
                loadFilePrepare(srcStation);
            }
        }catch (IllegalStation e){
            continue;
        }catch (LoadedFileException e){
            continue;
        }
    }
}
/**
 * this method take name and return the pointer to the relevant station
   from the graph
 * @param name - string name(of the station)
 * @return Station*
 */
Station* IOmanager::returnStationIfExistByName(const string& name){
    Station* station = nullptr;
    if((station = graph->findStationIfExist(name)) == nullptr)
        throw IllegalStation("this station doesn`t exist!");
    return station;
}
/**
 * this method get name of file that for sure start with vehicle type and return
 * the index identification of the type
 * @param filename - string name
 * @return indexOfVehicle (enum that defined)
 */
indexOfVehicle IOmanager::whichTypeOfVehicle(const string& filename){
    string temp = filename;
    if(temp.find_first_not_of("bus") == 3) return bus;
    else if(temp.find_first_not_of("tram") == 4) return tram;
    else if(temp.find_first_not_of("sprinter") == 8) return sprinter;
    else if(temp.find_first_not_of("rail") == 4)return rail;
}
/**
 * get the all data from the file
 * @param fin
 * @param filename
 */
void IOmanager::parseTheDataFromFile(ifstream* fin,const string& filename){
    string line = "";
    indexOfVehicle type = whichTypeOfVehicle(filename);
    size_t weight = 0;
    vector<string> lineData;
    if(!fin->is_open())
        fin->open(filename);
    if(!fin->is_open()) cout << "problem with the file opening" << endl;
    while(!fin->eof()){
        getline(*fin,line,'\n');
        if(line.size() < 5)continue;
        Validations::returnLineIfCorrect(line,lineData);
        stringstream ss(lineData[2]);
        ss >> weight;

        graph->addStation(lineData[0],lineData[1],weight,type);

        lineData.clear();
    }
}
/**
 * if there are config file or output file take the data and override the default
 * else - keep going by default
 * @param argc
 * @param argv
 */
void IOmanager::arrangeTheConfigAndOutput(int argc,char* argv[]){
    string outputFile = "";
    string configFile = "";
    string currArg = "";
    for(int i = 1;i<argc ; i++){
        if((currArg = argv[i]) == "-c")
            configFile = argv[i+1];
        else if(argv[i] == "-o") outputFile = argv[i+1];
    }
    if(outputFile == "")outputFile = "output.dat";
    if(configFile != "") takeTheConfigFile(configFile);
    takeTheOutputFile(outputFile);
}
/**
 * support method to take the config file data
 * @param filename
 */
void IOmanager::takeTheConfigFile(string filename){
    try{
        configFile->open(filename);
        if(!configFile)throw FileNotOpenException("problem with the config file - set the default definitions");
    }catch (FileNotOpenException e){return;}

    parseTheConfigFile();
    configFile->close();
}
/**
 * another supported method for the config
 * this method change the relevant values
 */
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
        outputFile->open(filename, ios_base::out | ios_base::app);
        if(!outputFile)throw FileNotOpenException("problem with the output file");
    }catch (FileNotOpenException e){exit(1);}
}

IOmanager::~IOmanager(){
    delete configFile;
    delete outputFile;
    delete loadFile;
}