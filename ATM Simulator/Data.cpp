#include "Data.h"

Data::Data(){
    fileName = "data.csv";
    file.open("data.csv", ios::in|ios::out);
    if(!file){
        cout << "Can not open data file";
    }
}

Data::Data(string fileName){
    this->fileName = fileName;
    file.open(fileName, ios::in|ios::out);
    if(!file){
        cout << "Can not open data file";
    }
}

bool Data::compare(string a, char* b){
    string::const_iterator it = a.begin();
    while(it != a.end()){
        if(*it != *b){
            return false;
        }
        it++;
        b++;
    }
    return true;
}

Data::~Data(){
    file.close();
}

User* Data::getByAccount(string account){
    if(account.size() != 19) return NULL;
    file.close();
    file.open(fileName, ios::in|ios::out);
    char buffer[98];
    while(!file.eof()){
        file.getline(buffer, 98);
        if(compare(account, buffer)){
            string s(buffer);
            string account = s.substr(0, 19);
            string password_s = s.substr(20, 6);
            int password = atoi(password_s.c_str());
            string balance_s = s.substr(27, 10);
            int balance = atoi(balance_s.c_str());
            string username = s.substr(38, USER_NAME_MAX);
            string id = s.substr(39 + USER_NAME_MAX, 18);
            string wrongTime_s = s.substr(58 + USER_NAME_MAX, 2);
            int wrongTime = atoi(wrongTime_s.c_str());
            string date = s.substr(60 + USER_NAME_MAX, 7);
            string limit_s = s.substr(68 + USER_NAME_MAX, 9);
            int limit = atoi(limit_s.c_str());
            User* user = new User(account, password, balance, username, id, wrongTime, date, limit);
            return user;
        }
    }
    return NULL;
}

void Data::save(User* user){
    file.seekp(-49, ios_base::cur);
    file.seekg(-49, ios_base::cur);
    cout << *user;
    file << *user << endl;
}

void Data::saveNew(User* user){
    file.close();
    file.open(fileName, ios::app);
    file << *user << endl;
    cout << *user << endl;
}
