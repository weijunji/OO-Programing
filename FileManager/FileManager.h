#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
using namespace std;

class FileManager{
    private:
        void welcome() const;
        void help() const;
        void printLocal() const;
        void quit() const;
        bool getCommand();
        vector<string> splitStr(string s);
        void makeDir(vector<string> command);
        void removeDir(vector<string> command);
        void changeDir(vector<string> command);
        void listDir();
        void copy(vector<string> command);
        void removeFile(vector<string> command);
        void copyDirDeep(vector<string> command);
        void copydir(string from, string to);
        void copyFile(string sourceFileName, string targetFileName);

    public:
        void start();
};

#endif
