//
// Created by aviha on 18/05/2018.
//
#include "Validations.h"
    bool Validations::isThereExistFile(int argc, char* argv[]) {
        if (isCorrectNumberOfArgs(argc) == false)return false;
        fstream fin;
        for (int i = 1; i < argc; i++) {
            fin.open(argv[i], ios_base::in);
            if (fin) return true;
        }
        return false;
    }
    bool Validations::isNameStartWithVehicle(char* name){

    }//arguments TODO
    bool isLineCorrect(const string& line){

    }//in the files TODO
}