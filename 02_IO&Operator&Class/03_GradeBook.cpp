/*
* author: Junji Wei
* date: 2018.3.20
* name: 03_GradeBook.cpp
* Copyright by Junji Wei
*/
#include <iostream>
#include <string>
using namespace std;

class GradeBook{
    public:
        GradeBook(string name, string instructor) : name(name), instructor(instructor){
        
        }

        string getInstructor(){
            return instructor;
        }

        void setInstructor(string instructor){
            this->instructor = instructor;
        }

        void printMessage(){
            cout << "Welcome to \" " << name << " \"" << endl;
            cout << "This course is presented by: " << instructor << endl;
        }

    private:
        string name;
        string instructor;
};

int main(){
    GradeBook myBook = GradeBook("C++ programing", "Mr. Wei");
    myBook.printMessage();
    cout << "Instructor : " << myBook.getInstructor() << endl;
    myBook.setInstructor("Mr. Zhou");
    myBook.printMessage();
    return 0;
}
