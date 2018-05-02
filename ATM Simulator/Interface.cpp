#include "Interface.h"

void Interface::test(){
    welcome();
    cout << keyBoardListener();
}

int* Interface::getRowCol(){
    int* result;
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
    result = (int*)malloc(sizeof(int) * 2);
    result[0] = w.ws_row;
    result[1] = w.ws_col;

    return result;
}

void Interface::printCenter(int col, string str, bool color /* =false */, char place /* =' ' */){
    int times = col - str.length();
    PRINT_TIMES(times / 2, place);
    if(color)cout << "\033[41;36m";
    cout << str;
    if(color)cout << "\033[0m";
    PRINT_TIMES(times - times / 2, place);
    cout << endl;
}

void Interface::showMenu(vector<string> menu, int select /* =0 */){
    clean();
    int* rc = getRowCol();
    int col = rc[1];
    int line = rc[0] - 4 - menu.size();
    printCenter(col, "A         T          M", false, '=');
    printCenter(col, "CopyRight by Junji Wei", false, '-');
    printCenter(col, "Use <- to go to previous page", false, '-');
    PRINT_TIMES(line / 2, '\n');
    for(size_t i = 0; i < menu.size(); i++){
        if(i == select){
            printCenter(col, menu[i], true);
        }else{
            printCenter(col, menu[i]);
        }
    }
    PRINT_TIMES(line - line / 2, '\n');
    free(rc);
}

void Interface::showRemind(string str){
    vector<string> menu;
    menu.push_back(str);
    menu.push_back("Press any key to quit");
    showMenu(menu, 2);
    keyBoardListener();
}

int Interface::keyBoardListener(){
    /*
    up : 65
    down: 66
    <- : 68
    0: 48
    1: 49
    2: 50
    9: 57
    enter: 10
    */
    int ch;
    ch = getch();
    if(ch == 27){
        keyBoardListener();
        return keyBoardListener();
    }else{
        return ch;
    }
}

void Interface::clean(){
    #ifndef DEBUG
        cout << "\033c";
    #endif
}

int Interface::welcome(){
    vector<string> menu;
    menu.push_back("Welcome to use this ATM");
    menu.push_back("Press any key to start");
    showMenu(menu, 3);
    if(keyBoardListener() == 68) return -1;
    return 0;
}

int Interface::menuSelect(vector<string> menu, int select){
    // -1: quit, others: select
    int max = menu.size();
    int key;
    showMenu(menu, select);
    while((key = keyBoardListener()) != 10){
        if(key == 65 && select > 0) select--;
        if(key == 66 && select < max - 1) select++;
        if(key == 68) return -1;
        showMenu(menu, select);
    }
    return select;
}

int Interface::startMenu(){
    vector<string> menu;
    menu.push_back("I have an account");
    menu.push_back("I don't have an account");
    return menuSelect(menu);
}

string* Interface::enterAccount(string error /* = "" */){
    vector<string> menu;
    menu.push_back("Please enter the account: ");
    menu.push_back("Enter q to quit");

    if(error == ""){
        showMenu(menu, 2);
    }else{
        menu.push_back(error);
        showMenu(menu, 2);
        menu.erase(menu.begin() + 2);
    }
    
    string account;
    cin >> account;
    if(account.size() == 1 && account[0] == 'q') return NULL;
    while(account.size() != 19){
        menu.push_back("The size of account must be 19, your input is " + toString(account.size()));
        showMenu(menu, 2);
        menu.erase(menu.begin() + 2);
        cin >> account;
        if(account.size() == 1 && account[0] == 'q') return NULL;
    }
    cin.ignore();
    return new string(account);
}

int Interface::enterPwd(int status){
    // -1: wrong pwd, -2: locked, 1: change pwd, 2: confirm pwd, 3: set pwd
    // -1: quit, others: password
    vector<string> menu;
    if(status == 1){
        menu.push_back("Enter the password you want to change: ");
    }else if(status == 2){
        menu.push_back("Please enter the password again: ");
    }else if(status == 3){
        menu.push_back("Enter the password you want to set: ");
    }else{
        menu.push_back("Please enter your password: ");
    }
    menu.push_back("Enter q to quit");
    if(status == -1)menu.push_back("Wrong password");
    if(status == -2){
        showRemind("Your account have been locked");
        return -1;
    }
    showMenu(menu, 2);
    int password = 0;
    int ch;
    int times = 0;
    while(times < 6){
        ch = getch();
        if(ch == 113) return -1;
        if(ch == 127){
            cout << '\b';
            password /= 10;
            times--;
        }
        if(ch >= 48 && ch <= 57){
            times++;
            password *= 10;
            password += (ch - 48);
            cout << '*';
        }
    }
    return password;
}

int Interface::userMenu(string username){
    vector<string> menu;
    menu.push_back("Welcome! " + username);
    menu.push_back("Take money");
    menu.push_back("Save money");
    menu.push_back("Transfer");
    menu.push_back("Change password");
    menu.push_back("Quit");
    return menuSelect(menu, 1);
}

int Interface::takeMoney(int balance, int error){
    // error: 0: no error, -1: not enough, -2: limit once, -3: limit one day
    vector<string> menu;

    menu.push_back("You have " + toString(balance) + " now !");
    menu.push_back("Please enter the money you want to take :");
    menu.push_back("Enter 0 to quit");

    int money;
    bool pushed = false;
    do{
        if(error == -1) menu.push_back("You don't have enough money !");
        if(error == -2) menu.push_back("You can't take too much once");
        if(error == -3) menu.push_back("You can't take too much one day");
        showMenu(menu, 3);
        if(error != 0) menu.erase(menu.begin() + 3);
        if(!pushed){
            menu.push_back("The money must be times of 100");
            pushed = true;
        }

        cin >> money;
        if(!cin.good()){
            cin.clear();
            cin.sync();
            continue;
        }

    }while(money % 100 != 0 || money < 0);
    cin.ignore();
    return money;
}

int Interface::saveMoney(int balance, bool error){
    vector<string> menu;

    menu.push_back("You have " + toString(balance) + " now !");
    menu.push_back("Please enter the money you want to save :");
    menu.push_back("Enter 0 to quit");

    int money;
    bool pushed = false;
    do{
        if(error) menu.push_back("You money is out of range !");
        showMenu(menu, 3);
        if(error) menu.erase(menu.begin() + 3);
        if(!pushed){
            menu.push_back("The money must be times of 100");
            pushed = true;
        }

        cin >> money;
        if(!cin.good()){
            cin.clear();
            cin.sync();
            continue;
        }

    }while(money % 100 != 0 || money < 0);
    getchar();
    return money;
}

int Interface::transfer(string account, int error){
    vector<string> menu;

    menu.push_back("You are transferring to " + account + " now !");
    menu.push_back("Please check the account you transfer to !!!");
    menu.push_back("Please enter the money you want to transfer :");

    int money;
    bool pushed = false;
    do{
        if(error == -1) menu.push_back("There is no enough money in your account!");
        if(error == -2) menu.push_back("The money is out of range !");
        showMenu(menu, 3);
        if(error == -1 || error == -2) menu.erase(menu.begin() + 2);
        if(!pushed){
            menu.push_back("The money must be times of 100");
            pushed = true;
        }

        cin >> money;
        if(!cin.good()){
            cin.clear();
            cin.sync();
            continue;
        }

    }while(money % 100 != 0 || money < 0);
    getchar();
    return money;
}

int Interface::powerOff(){
    // 1: no, 2: yes
    vector<string> menu;
    menu.push_back("Are you sure to power off ?");
    menu.push_back("No");
    menu.push_back("Yes");
    int select = -1;
    while(select == -1 || select == 0){
        select = menuSelect(menu, 1);
    }
    return select;
}
