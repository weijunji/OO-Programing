#ifndef ATM_H
#define ATM_H

#include "User.h"
#include "Interface.h"
#include "Data.h"

class ATM{
    private:
        Interface interface;
        User* user;
        Data* data;

        int start();
        int enterAccount();
        int checkPwd();

        int userMenu();

        void takeMoney();
        void saveMoney();
        void transfer();

        void changePwd();
        void createUser();

        int checkAccount(string a);
        bool checkId(string id);

        int powerOff();

    public:
        ATM();
        ATM(string data_file);

        void powerOn();
};

#endif
