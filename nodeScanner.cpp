#include "nodeScanner.h"
#include <filesystem>
#include <fstream>
#include "scanner.h"


std::vector<Node *> NodeScanner::scan(dirNode& nod){

    auto __path = nod.path();

    std::vector<Node *> nodes;

    if(!std::filesystem::exists(__path)){
        return nodes;
    }
    for(const auto& fse : std::filesystem::directory_iterator(__path)){
        if(fse.is_directory()){
            nod.data.subirsCount++;
            dirNode* sub = new dirNode(fse.path());
            nodes.push_back(sub);
        }
        else if(fse.is_regular_file()){
            nod.data.regFilesCount++;
            fileNode * file = new fileNode(fse.path());
            nodes.push_back(file);
        }
        else{
            nod.data.otherFilesCount++;
        }
    }
    return nodes;
}

std::vector<Node *> NodeScanner::scan(fileNode& nod){

    std::ifstream ifs;
    Scanner scn;

    ifs.open(nod.path().string());
    nod.data =  scn.scan(ifs);
    ifs.close();

    return std::vector<Node *>();
}