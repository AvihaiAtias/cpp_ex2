//
// Created by aviha on 18/05/2018.
//

#ifndef EX2_EXCEPTIONS_H
#define EX2_EXCEPTIONS_H

#include <iostream>
using namespace std;
class NoSuchFileExist:public exception{
public:
    NoSuchFileExist(){}
    NoSuchFileExist(const string& msg){cerr << msg << endl;}
};
class ArgumentsAmountError:public exception{
public:
    ArgumentsAmountError(){}
    ArgumentsAmountError(const string& msg){cerr << msg << endl;}
};
class NameFileIsUnCorrect:public exception{
public:
    NameFileIsUnCorrect(){}
    NameFileIsUnCorrect(const string& msg){cerr << msg << endl;}
};
class NameIsTooLong:public exception{
public:
    NameIsTooLong(){}
    NameIsTooLong(const string& msg){cerr << msg << endl;}
};
class LineInputUnCorrect:public exception{
public:
    LineInputUnCorrect(){}
    LineInputUnCorrect(const string& msg){cerr << msg << endl;}
};
class FileNotOpenException:public exception{
public:
    FileNotOpenException(){}
    FileNotOpenException(const string& msg){cerr << msg << endl;}
};
class LoadedFileException:public exception{
public:
    LoadedFileException(){}
    LoadedFileException(const string& msg){cerr << msg << endl;}
};
class IllegalStation:public exception{
public:
    IllegalStation(){}
    IllegalStation(const string& msg){cerr << msg << endl;}
};
#endif //EX2_EXCEPTIONS_H
