/*
* author: Junji Wei
* date: 2018.3.20
* name: 02_shapes.cpp
* Copyright by Junji Wei
*/
#include <iostream>
using namespace std;

void printBox(){
    cout << "*********" << endl;
    for(int i = 0; i < 7; i++){
        cout << "*       *" << endl;
    }
    cout << "*********" << endl;
    cout << endl;
}

void printOval(){
    cout << "   ***   " << endl;
    cout << " *     * " << endl;
    for(int i = 0; i < 5; i++){
        cout << "*       *" << endl;
    }
    cout << " *     * " << endl;
    cout << "   ***   " << endl;
    cout << endl;
}

void printArrow(){
    cout << "    *    " << endl;
    cout << "   ***   " << endl;
    cout << "  *****  " << endl;
    for(int i = 0; i < 5; i++){
        cout << "    *    " << endl;
    }
    cout << endl;
}

void printDiamond(){
    cout << "    *    " << endl;
    cout << "   * *   " << endl;
    cout << "  *   *  " << endl;
    cout << " *     * " << endl;
    cout << "*       *" << endl;
    cout << " *     * " << endl;
    cout << "  *   *  " << endl;
    cout << "   * *   " << endl;
    cout << "    *    " << endl;
    cout << endl;    
}

int main(){
    printBox();
    printOval();
    printArrow();
    printDiamond();
    return 0;
}
