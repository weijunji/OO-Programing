/*
* author: Junji Wei
* date: 2018.3.20
* name: 01_hello.cpp
* Copyright by Junji Wei
*/
#include <iostream>
#include <string>
using namespace std;

int main() {
    string message;
    cout << "Please enter your first name:";
    cin >> message;
    cout << "****************" << endl;
    cout << "*                         *" << endl;
    cout << "* Hello, " << message << "! *" << endl;
    cout << "*                         *" << endl;
    cout << "****************" << endl;
    return 0;
}
