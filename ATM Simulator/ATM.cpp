#include "ATM.h"

ATM::ATM(){
    data = new Data();
}

ATM::ATM(string data_file){
    data = new Data(data_file);
}

void ATM::powerOn(){
    while(true){
        if(interface.welcome() == -1){
            if(powerOff() == -1) break;
            continue;
        }
        start();
    }
}

int ATM::start(){
    int have = interface.startMenu();
    if(have == -1) return -1;
    if(have == 0){
        enterAccount();
    }else{
        createUser();
    }
}

int ATM::enterAccount(){
    string* account = interface.enterAccount();
    if(account == NULL){
        return -1;
    }
    user = data->getByAccount(*account);
    while(user == NULL){
        account = interface.enterAccount("There is no account called " + *account);
        if(account == NULL){
            return -1;
        }
        user = data->getByAccount(*account);
    }
    checkPwd();
}

int ATM::checkPwd(){
    // check the password is locked ?
    int status = user->checkPWD(-1);
    bool flag = false;
    // you can input 4 times, but the 4th one is nothing.
    while(status == -1){
        if(!flag){
            status = 0;
            flag = true;
        }
        int password = interface.enterPwd(status);
        if(password == -1){
            return -1;
        }
        status = user->checkPWD(password);
        data->save(user);
    }
    if(status == -2){
        // tell the password is locked
        interface.enterPwd(status);
        return -1;
    }else{
        userMenu();
    }
}

int ATM::userMenu(){
    int status;
    while(true){
        status = interface.userMenu(user->getUserName());
        if(status == 1){
            takeMoney();
        }else if(status == 2){
            saveMoney();
        }else if(status == 3){
            transfer();
        }else if(status == 4){
            changePwd();
        }else if(status == 5 || status == -1){
            break;
        }
    }
}

void ATM::takeMoney(){
    int balance = user->getBalance();
    int status = 0;
    int money;
    do{
        money = interface.takeMoney(balance, status);
    }while((status = user->takeMoney(money)) != 0);
    data->save(user);
    if(money != 0){
        interface.showRemind("Here is your " + toString(money) + " yuan !");
    }
}

void ATM::saveMoney(){
    int balance = user->getBalance();
    bool status = false;
    int money;
    do{
        money = interface.saveMoney(balance, status);
        status = true;
    }while(user->saveMoney(money) == -1);
    data->save(user);
    if(money != 0){
        interface.showRemind("You saved " + toString(money) + " yuan !");
    }
}

void ATM::transfer(){
    string* account;
    User* from = user;
    // get user from account
    account = interface.enterAccount();
    if(account == NULL) return;
    user = data->getByAccount(*account);
    while(user == NULL){
        account = interface.enterAccount("There is no account called " + *account);
        if(account == NULL){
            data->getByAccount(from->getAccount());
            return;
        }
        user = data->getByAccount(user->getAccount());
    }
    // get money and check illeagl
    int error = 0;
    int money;
    while(true){
        money = interface.transfer(*account, error);
        if(from->getBalance() > money && user->getBalance() + money < BALANCE_MAX){
            // save money and save user data
            user->saveMoney(money);
            data->save(user);
            // switch to current user and take money
            user = data->getByAccount(from->getAccount());
            user->takeMoney(money, true);
            data->save(user);
            interface.showRemind("Transfer " + toString(money) + " to " + *account + " success!");
            break;
        }else if(from->getBalance() > money){
            error = -1;
        }else{
            error = -2;
        }
    }
}

void ATM::changePwd(){
    int password = interface.enterPwd(1);
    if(password == -1){
        return;
    }
    if(password == interface.enterPwd(2)){
        user->changePWD(password);
        data->save(user);
        interface.showRemind("Change password success, remember your password");
        return;
    }else{
        interface.showRemind("The twice you input isn't match");
    }
}

void ATM::createUser(){
    // input account -> check account -> input password -> confirm password -> 
    // input username(length 20) -> input id -> check id -> create user -> showRedmine
    // input and check account
    string* account;
    int status = 0;
    do{
        if(status == 0) account = interface.enterAccount();
        if(status == -1) account = interface.enterAccount("The account must be made with number");
        if(status == -2) account = interface.enterAccount("This account is already exist");
        if(account == NULL) return;
        status = checkAccount(*account);
    }while(status != 0);
    // input and confirm pwd
    int password;
    while(true){
        password = interface.enterPwd(3);
        if(password == -1){
            return;
        }
        if(password != interface.enterPwd(2)){
            interface.showRemind("The twice your input is not same, try again");
        }else{
            break;
        }
    }
    // input username
    string userName;
    vector<string> menu1;
    menu1.push_back("Input your userName");
    menu1.push_back("The username should be shorter than " + toString(USER_NAME_MAX));
    menu1.push_back("Input q to quit");
    do{
        userName = "";
        interface.showMenu(menu1, 1);
        cin >> userName;
        if(userName == "q") return;
    }while(userName.size() > USER_NAME_MAX);
    // input id
    string id;
    vector<string> menu2;
    menu2.push_back("Input your ID");
    menu2.push_back("The ID should be 18-bit ");
    menu2.push_back("Input q to quit");
    do{
        id = "";
        interface.showMenu(menu2, 1);
        cin >> id;
        if(id == "q") return;
    }while(!checkId(id));
    getchar();

    User* new_user = new User(*account, password, 10000, userName, id, 0, "", 0);
    data->saveNew(new_user);
    interface.showRemind("Create " + new_user->getAccount() + " success, remeber your account");
    delete account;
    delete new_user;
}

bool ATM::checkId(string id){
    if(id.size() != 18) return false;
    string::const_iterator it = id.begin();
    while(it != id.end()){
        if(*it < '0' || *it > '9'){
            return false;
        }
        it++;
    }
    return true;
}

int ATM::checkAccount(string a){
    // 0: access, -1: wrong format, -2: user already exist.
    string::const_iterator it = a.begin();
    while(it != a.end()){
        if(*it < '0' || *it > '9'){
            return -1;
        }
        it++;
    }
    User* user = data->getByAccount(a);
    if(user == NULL){
        return 0;
    }else{
        return -2;
    }
}

int ATM::powerOff(){
    // 0: cancel, -1: power off
    int status = 0;
    while(status == 0){
        status = interface.powerOff();
        if(status == 1) return 0;
        if(status == 2) return -1;
    }
}
