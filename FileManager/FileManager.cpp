#include "FileManager.h"

void FileManager::start(){
	welcome();
	do{
		printLocal();
	}while(getCommand());
}

void FileManager::welcome() const{
	cout << "==============================================" << endl;
	cout << "          Welcome to use FileManager" << endl;
	cout << "            ver: 0.1 by Junji Wei" << endl;
	cout << "==============================================" << endl;
	cout << " md   make direcory   |   rd   remove direcory" << endl;
	cout << " cd   change direcory |   ld   list direcory"<< endl;
	cout << " cp   copy file/dir   |   rf   remove file" << endl;
	cout << "  h   help            |    q   quit" << endl;
}

void FileManager::help() const{
	cout << "md [directory]" << endl;
	cout << "    make directory\n" << endl;
	cout << "rd [directory]" << endl;
	cout << "    remove direcory\n" << endl;
	cout << "cd [directory]" << endl;
	cout << "    change direcory\n" << endl;
	cout << "ld " << endl;
	cout << "    list the working direcory\n" << endl;
	cout << "cp [file/dir] [target]" << endl;
	cout << "    copy file or direcory to target\n" << endl;
	cout << "rf [file]" << endl;
	cout << "    remove file\n" << endl;
}

void FileManager::printLocal() const{
	char curDir[300];
	getcwd(curDir, 300);
	cout<< curDir <<" > ";
}

void FileManager::quit() const{
	cout << "welcome to use again" << endl;
}

bool FileManager::getCommand(){
	string commandLine;
	vector<string> commandArgs;

	getline(cin,commandLine);
	commandArgs=splitStr(commandLine);

	if(commandArgs.size()>0){
		if("q" == commandArgs[0]){
			quit();
			return false;
		}else if ("h" == commandArgs[0]){
			help();
		}else if("md" == commandArgs[0]){
			makeDir(commandArgs);
		}else if("rd" == commandArgs[0]){
			removeDir(commandArgs);
		}else if("rf" == commandArgs[0]){
			removeFile(commandArgs);
		}else if("cd" == commandArgs[0]){
			changeDir(commandArgs);
		}else if("ld" == commandArgs[0]){
			listDir();
		}else if("cp" == commandArgs[0]){
			copy(commandArgs);
		}else
		{
			cout << commandArgs[0] << " : command not find" <<endl;
		}
	}
	return true;
}

vector<string> FileManager::splitStr(string s){
	vector<string> tokens;
	istringstream iss(s);
    do
    {
        string sub;
        iss >> sub;
        tokens.push_back(sub);
    } while (iss);

    tokens.erase(tokens.end()-1);
	return tokens;
}

void FileManager::makeDir(vector<string> command){
	if(command.size() != 2){
		cout<< "error: require 1 args, but " << command.size() - 1 << " are given. Use h to get help." << endl;
	}else{
		string dirName = command[1];
		mode_t mode = 0775;
		if(mkdir(dirName.c_str(), mode) == 0){
	    	cout<<"Create \""<<dirName<<"\" success."<<endl;
	    }else{
	    	cout<<"error: Create \""<<dirName<<"\" failed."<<endl;
	    }
	}
}

void FileManager::removeDir(vector<string> command){
	if(command.size() != 2){
		cout<< "error: require 1 args, but " << command.size() - 1 << " are given. Use h to get help." << endl;
	}else{
		string dirName = command[1];
		if(rmdir(dirName.c_str()) == 0 ){
			cout<<"Remove directory \""<<dirName<<"\" success."<<endl;
		}else{
	    	cout<<"error: Remove directory \""<<dirName<<"\" failed."<<endl;
	    }
	}
}

void FileManager::changeDir(vector<string> command){
	if(command.size()<2){
		cout<< "error: require 1 args, but " << command.size() - 1 << " are given. Use h to get help." << endl;
	}else{
		string dirName = command[1];
		if(chdir(dirName.c_str()) != 0){
	    	char curDir[300];
	    	getcwd(curDir,300);
	    	cout<<"error: Change directory failed."<<endl;
		}
	}
}

void FileManager::listDir(){
	DIR * curDir;
	struct dirent *ent;
	struct stat entStat;
	if((curDir=opendir("."))==NULL){
	    cout<<"error: Open directory failed"<<endl;
	}else{
		while((ent=readdir(curDir))!=NULL){
			if(stat(ent->d_name, &entStat) == 0){
				if(entStat.st_mode & S_IFDIR){
					cout<<setw(6)<<left<<"d";
					cout<<right<<setw(10)<<entStat.st_size<<left<<setw(8)<<" bytes";
					cout<<ent->d_name<<"/"<<endl;
				}else if(entStat.st_mode & S_IFREG){
					cout<<setw(6)<<left<<"-";
					cout<<right<<setw(10)<<entStat.st_size<<left<<setw(8)<<" bytes";
					cout<<ent->d_name<<endl;
				}
		   	}
		}
	closedir(curDir);
	}
}

void FileManager::copydir(string from, string to){
	DIR * curDir;
	struct dirent *ent;
	struct stat entStat;
	if((curDir=opendir(from.c_str()))==NULL){
	    cout<<"error: Open directory failed"<<endl;
		return;
	}
	while((ent=readdir(curDir))!=NULL){
		if(strchr(ent->d_name, '.') - ent->d_name == 0){
			continue;
		}
		if(stat((from + '/' + ent->d_name).c_str(), &entStat) == 0){
			if(entStat.st_mode & S_IFDIR){
				mode_t mode = 0775;
				mkdir((to + '/' + ent->d_name).c_str(), mode);
				copydir(from + '/' + ent->d_name, to + '/' + ent->d_name);
			}else if(entStat.st_mode & S_IFREG){
				string sourceFileName = from + '/' + ent->d_name;
				string targetFileName = to + '/' + ent->d_name;
				ifstream sourceFile(sourceFileName.c_str(), ios::binary);
				ofstream targetFile(targetFileName.c_str(), ios::binary);
				targetFile<<sourceFile.rdbuf();
				targetFile.close();
				sourceFile.close();
			}
		}
	}
	closedir(curDir);
}

void FileManager::copyDirDeep(vector<string> command){
	if(command.size() != 3){
		cout<< "error: require 2 args, but " << command.size() - 1 << " are given. Use h to get help." << endl;
	}else{
		mode_t mode = 0775;
		mkdir(command[2].c_str(), mode);
		copydir(command[1], command[2]);
	}
}

void FileManager::copyFile(string sourceFileName, string targetFileName){
	ifstream sourceFile(sourceFileName.c_str(), ios::binary);
	ofstream targetFile(targetFileName.c_str(), ios::binary);
	targetFile<<sourceFile.rdbuf();
	targetFile.close();
	sourceFile.close();
}

void FileManager::copy(vector<string> command){
	if(command.size() != 3){
		cout<< "error: require 2 args, but " << command.size() - 1 << " are given. Use h to get help." << endl;
	}else{
		struct stat entStat;
		string source = command[1];
		string target = command[2];
		stat(source.c_str(), &entStat);
		if(entStat.st_mode & S_IFDIR){
			copyDirDeep(command);
		}else if(entStat.st_mode & S_IFREG){
			copyFile(source, target);
		}
		cout<<"Copy success"<<endl;
	}
}

void FileManager::removeFile(vector<string> command){
	if(command.size() != 2){
		cout<< "error: require 1 args, but " << command.size() - 1 << " are given. Use h to get help." << endl;
	}else{
		string fileName = command[1];
		if(remove(fileName.c_str()) == 0 ){
			cout<<"Remove file \""<<fileName<<"\" success."<<endl;
		}else{
	    	cout<<"error: Remove file \""<<fileName<<"\" failed."<<endl;
	    }
	}
}
