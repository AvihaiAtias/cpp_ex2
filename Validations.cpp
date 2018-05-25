//
// Created by aviha on 18/05/2018.
//
#include <vector>
#include "Validations.h"
/**
 * static method to check if there file exist
 * @param argc
 * @param argv
 */
    void Validations::isThereFileExist(int argc, char* argv[]) {
        string str;
        if (isCorrectNumberOfArgs(argc) == false)
            throw ArgumentsAmountError("there are not enough Arguments");
        for (int i = 1; i < argc; i++) {
            str = argv[i];
            if(str == "-c" || str == "-o"){
                ++i;
                continue;
            }
            fstream* fin = new fstream(argv[i], ios_base::in | ios_base::out | ios_base::app);
            if (fin) {
                fin->close();
                return; // mean that there is 1 input file correct at least;
            }
        }
        throw NoSuchFileExist("no such file exist"); //if there are no input files
    }
    /**
     * static method to check if the file name start with vehicle name
     * @param name
     */
    void Validations::isNameStartWithVehicle(const string& name){
        string temp = name;
        if(temp.find_first_not_of("bus") != 3 &&
           temp.find_first_not_of("tram") != 4 &&
           temp.find_first_not_of("sprinter") != 8 &&
           temp.find_first_not_of("rail") != 4) {

                stringstream ss;
                ss << "the file: " << name << " is illegal! should start with vehicle name";
                throw NameFileIsUnCorrect(ss.str());
        }
    }
    /**
     * static method that check line from file and check it, if correct
     * enter the line after separating the vertexes in the vector.
     * @param string line
     * @param sepLine - vector
     */
    void Validations::returnLineIfCorrect(const string& line,vector<string>& sepLine){
        stringstream ss;
        string source,dest,num;
        istringstream iss(line);
        iss >> source >> dest >> num;
        if(num == ""){
            ss << "this line is uncorrect - too few words" << endl << line;
            throw LineInputUnCorrect(ss.str());
        }
        if(!isTimeWeightCorrect(num)){
            ss << "line input uncorrect: " << num << " is not a number";
            throw LineInputUnCorrect(ss.str());
        }
        if(!isTabsCountCorrect(line))
            throw LineInputUnCorrect("you should separate the line only with 2 tabs");

        isNamelengthCorrect(source);//method that throw exception if the length bigger than 16
        isNamelengthCorrect(dest);
        isNamelengthCorrect(num);

        sepLine.push_back(source);
        sepLine.push_back(dest);
        sepLine.push_back(num);
    }
    /**
     * static method to check if the name length not too long (16 chars)
     * @param name
     */
    void Validations::isNamelengthCorrect(const string& name) {
        if(name.length() > MAX_LENGTH_OF_STATION){
            stringstream ss;
            ss <<"the name: "<< name << "is too Long" << endl;
            throw LineInputUnCorrect(ss.str());
        }
    }
    /**
     * method to count the tabs in every line inside the files
     * @param line
     * @return bool
     */
    bool Validations::isTabsCountCorrect(const string& line){
        int tabsCount = 0;
        char c;
        for(size_t i = 0;i<static_cast<size_t>(line.length());i++){
            if(line[i] == ' ')
                tabsCount++;
        }
        return(tabsCount == 2)?true:false;
    }
    /**
     * check if the weight its number for sure and also if its positive number
     * @param number
     * @return
     */
    bool Validations::isTimeWeightCorrect(const string& number){
        int num = atoi(number.c_str());
        if(num == 0 && number[0] != 0) return false;
        else if(num < 0) return false;
        return true;
    }