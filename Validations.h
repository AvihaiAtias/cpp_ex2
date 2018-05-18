//
// Created by aviha on 18/05/2018.
//

#ifndef EX2_VALIDATIONS_H
#define EX2_VALIDATIONS_H
#include <iostream>
#include <fstream>
using namespace std;

class Validations {
    static const int MAX_LENGTH_OF_STATION = 16;
    static bool isCorrectNumberOfArgs(int argc){return argc > 2;}
    static bool isThereExistFile(int argc, char* argv[]);
    static bool isNameStartWithVehicle(char* name);
    static bool isLineCorrect(const string& line);
    static bool isNamelengthCorrect(const string& name){return name.length() > MAX_LENGTH_OF_STATION;}

};


#endif //EX2_VALIDATIONS_H
