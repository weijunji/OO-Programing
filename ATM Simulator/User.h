#ifndef USER_H
#define USER_H

#define USER_NAME_MAX 20
#define BALANCE_MAX 1000000000
#define ONCE_LIMIT 10000
#define ONE_DAY_LIMIT 100000

#include <iostream>
#include <ctime>

using namespace std;

class User{
    private:
        unsigned int balance;
        string userName;
        string account;
        string id;
        unsigned int password;
        int wrongTime;

        string date;
        int limit;

        string getBalanceStr() const;
        string getUserNameStr() const;
        string getLimitStr() const;
        string getPwdStr() const;

        string getDate() const;

    public:
        User(string account, unsigned int password, unsigned int balance, string userName, string id, int wrongTime, string date, int limit);

        unsigned int getBalance() const;
        string getUserName() const;
        string getAccount() const;

        int saveMoney(int money);
        int takeMoney(int money, bool transfer = false);

        int checkPWD(int password);
        
        void changePWD(unsigned int password);

        friend ostream& operator << (ostream& os, User user);
};

#endif 
