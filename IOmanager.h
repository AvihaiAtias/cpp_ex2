//
// Created by aviha on 18/05/2018.
//

#ifndef EX2_IOMANAGER_H
#define EX2_IOMANAGER_H
#include <iostream>
#include <fstream>
using namespace std;

class IOmanager {
    fstream* files;
public:
    IOmanager(int argc,char* argv[]);
    virtual ~IOmanager();

    void load(const fstream& fin);//TODO checks and valids of lines and create the stations after
};


#endif //EX2_IOMANAGER_H
