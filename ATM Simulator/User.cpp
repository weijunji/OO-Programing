#include "User.h"
#include "others.h"

User::User(string account, unsigned int password, unsigned int balance, string userName, string id, int wrongTime, string date, int limit){
    this->account = account;
    this->password = password;
    this->balance = balance;
    int len = userName.size();
    size_t i = 0;
    while(i < len){
        if(userName[i] == '-')break;
        i++;
    }
    this->userName = userName.substr(0, i);
    this->id = id;
    this->wrongTime = wrongTime;
    this->date = getDate();
    if(this->date == date){
        this->limit = limit;
    }else{
        this->limit = ONE_DAY_LIMIT;
    }
}

string User::getDate() const{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string date;
    date = toString(ltm->tm_year);
    if(ltm->tm_mon < 10){
        date += "0";
        date += toString(ltm->tm_mon);
    }
    if(ltm->tm_mday < 10){
        date += "0";
        date += toString(ltm->tm_mday);
    }
    return date;
}

unsigned int User::getBalance() const{
    return balance;
}

int User::saveMoney(int money){
    if(money + balance >= BALANCE_MAX) {
        return -1;
    }
    balance += money;
    return balance;
}

int User::takeMoney(int money, bool transfer){
    // 0: success, -1: not enough, -2: limit once, -3: limit one day
    if(balance < money) {
        return -1;
    }
    if(money > ONCE_LIMIT && !transfer){
        return -2;
    }
    if(money > limit && !transfer){
        return -3;
    }
    balance -= money;
    if(!transfer) limit -= money;
    return 0;
}

string User::getUserName() const{
    return userName;
}

string User::getAccount() const{
    return account;
}

void User::changePWD(unsigned int password){
    this->password = password;
}

ostream& operator << (ostream& os, User user){
    os << user.account << "," << user.getPwdStr() << "," << user.getBalanceStr() << "," << user.getUserNameStr() << "," << user.id << "," << user.wrongTime << "," << user.date << "," << user.getLimitStr();
    return os;
}

string User::getBalanceStr() const{
    return toStringFormat(balance, 10);
    string str(10, '0');
    int balance = this->balance;
    for(int i = 9; i >= 0; i--){
        if(balance == 0){
            break;
        }
        str[i] = balance % 10 + '0';
        balance /= 10;
    }
    return str;
}

string User::getLimitStr() const{
    return toStringFormat(limit, 9);
    string str(9, '0');
    int limit = this->limit;
    for(int i = 8; i >= 0; i--){
        if(limit == 0){
            break;
        }
        str[i] = limit % 10 + '0';
        limit /= 10;
    }
    return str;
}

string User::getPwdStr() const{
    return toStringFormat(password, 6);
    string str(6, '0');
    int pwd = this->password;
    for(int i = 5; i >= 0; i--){
        if(pwd == 0){
            break;
        }
        str[i] = pwd % 10 + '0';
        pwd /= 10;
    }
    return str;
}

string User::getUserNameStr() const{
    string str = userName;
    str.resize(20, '-');
    return str;
}

int User::checkPWD(int password){
    cout << this->wrongTime;
    // -2 locked, -1 not locked
    if(password == -1){
        if(wrongTime > 2){
            return -2;
        }else{
            return -1;
        }
    }
    // 0 true, -1 wrong, -2 locked
    if(wrongTime > 2){
        return -2;
    }else{
        if(password == this->password){
            wrongTime = 0;
            return 0;
        }else{
            wrongTime++;
            return -1;
        }
    }
}
