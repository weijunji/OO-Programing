#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <fstream>
#include <string>
#include "User.h"

using namespace std;

class Data{
    private:
        fstream file;
        string fileName;

        bool compare(string a, char* b);

    public:
        Data();
        Data(string);
        ~Data();
        User* getByAccount(string account);
        void save(User* user);
        void saveNew(User* user);
};

#endif
