//
// Created by aviha on 18/05/2018.
//
/**
 * class with all static method that make some checks
 * (explaination is extend in the cpp file)
 */
#ifndef EX2_VALIDATIONS_H
#define EX2_VALIDATIONS_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include "Exceptions.h"
#include "TransportSystem.h"

using namespace std;
class Validations {
    static const int MAX_LENGTH_OF_STATION = 16;
    static bool isTabsCountCorrect(const string& line);
    static bool isCorrectNumberOfArgs(int argc){return argc >= 2;}
    static bool isTimeWeightCorrect(const string& number);

public:
    static void isNameStartWithVehicle(const string& name);
    static void isThereFileExist(int argc, char* argv[]);
    static void returnLineIfCorrect(const string& line,vector<string>& sepLine);
    static void isNamelengthCorrect(const string& name);
};

#endif //EX2_VALIDATIONS_H
