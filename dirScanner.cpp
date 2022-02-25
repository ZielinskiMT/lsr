#include "dirScanner.h"
#include "scanner.h"
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

void dirScanner::scan(){
    if(!fs::exists(__path)){
        std::cerr << "dirFileScanner::scan(): given path is incorrect./n";
    }
    if(!fs::is_directory(__path)){
        std::cerr << "dirFileScanner::scan(): object under given path is not a directory./n";
    }
    for(const auto& fse : fs::directory_iterator(__path)){
        if(fse.is_directory()){
            __subdirs.push_back(fse.path());
        }
        else if(fse.is_regular_file()){
            __regularFiles.push_back(fse.path());
        }
        else{
            __otherFiles.push_back(fse.path());
        }
    }
}

