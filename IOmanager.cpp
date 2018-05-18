//
// Created by aviha on 18/05/2018.
//

#include "IOmanager.h"
IOmanager::IOmanager(int argc,char* argv[]){
    if(argc < 2){
        //TODO create validation and throw exception
    }
    files = new fstream[argc-1];
}

IOmanager::~IOmanager(){
    delete [] files;
}