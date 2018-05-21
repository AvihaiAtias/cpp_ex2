//
// Created by aviha on 18/05/2018.
//

#ifndef EX2_VALIDATIONS_H
#define EX2_VALIDATIONS_H
//#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include "Exceptions.h"

using namespace std;
class Validations {
    static const int MAX_LENGTH_OF_STATION = 16;
    static bool isTabsCountCorrect(const string& line);
    static bool isCorrectNumberOfArgs(int argc){return argc > 2;}
    static bool isTimeWeightCorrect(const string& number);
    static void isNameStartWithVehicle(const string& name);
public:
    static void inputFilesArrangment(int argc, char* argv[],map<string,fstream*>& files);
    static void returnLineIfCorrect(const string& line,vector<string>& sepLine);
    static void isNamelengthCorrect(const string& name);
    static void filesFilter(int argc, char* argv[],map<string,fstream*>& files);

};

#endif //EX2_VALIDATIONS_H
