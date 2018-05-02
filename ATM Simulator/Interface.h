#ifndef INTERFACE_H
#define INTERFACE_H

#define PRINT_TIMES(x, y) for(size_t i = 0; i < x; i++)cout << y;

#define DEBUG
#undef DEBUG

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

#include "others.h"

using namespace std;

class Interface{
    private:
        void clean();
        int* getRowCol();
        void printCenter(int col, string str, bool color=false, char place=' ');
        int keyBoardListener();
        int menuSelect(vector<string> menu, int select = 0);

    public:
        int welcome();
        int startMenu();
        string* enterAccount(string error = "");
        int enterPwd(int status);

        void showMenu(vector<string> menu, int select=0);
        void showRemind(string str);

        int userMenu(string username);
        int takeMoney(int balance, int error = 0);
        int saveMoney(int balance, bool error = false);
        int transfer(string account, int error);

        int powerOff();

        void test();
};
#endif

/*
插卡， 新建用户
    插卡（输入密码）
    新建用户
操作选择（取钱， 存钱， 转账， 修改密码）
    取钱（输入金额）
        金额不足
    存钱（输入金额）
*/
