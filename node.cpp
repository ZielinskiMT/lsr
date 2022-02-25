#include "node.h"
#include <fstream>
#include "scanner.h"

std::vector<Node *> dirNode::scan(){

    std::vector<Node *> nodes;

    if(!std::filesystem::exists(__path)){
        return nodes;
    }
    for(const auto& fse : std::filesystem::directory_iterator(__path)){
        if(fse.is_directory()){
            data.subirsCount++;
            dirNode* sub = new dirNode(fse.path());
            nodes.push_back(sub);
        }
        else if(fse.is_regular_file()){
            data.regFilesCount++;
            fileNode * file = new fileNode(fse.path());
            nodes.push_back(file);
        }
        else{
            data.otherFilesCount++;
        }
    }
    return nodes;
}

const std::string dirNode::string(){
    return "\n+---------------------------------------+\n" + 
            this->__path.string() + 
            "\n+---------------------------------------+" + 
            "\n subdirs: " + std::to_string(data.subirsCount) +
            "\n regular files: " + std::to_string(data.regFilesCount) + 
            "\n other files: " + std::to_string(data.otherFilesCount) + 
            "\n lines: " + std::to_string(data.lineCount) +
            "\n empty lines: " + std::to_string(data.emptyLinesCount) +
            "\n non empty lines: " + std::to_string(data.nonEmptyLinesCount) + 
            "\n+---------------------------------------+\n";
}


std::vector<Node *> fileNode::scan(){

    std::ifstream ifs;
    Scanner scn;

    ifs.open( __path.string() );
    data =  scn.scan(ifs);
    ifs.close();

    return std::vector<Node *>();
}

const std::string fileNode::string(){
    return " -- " + this->__path.filename().string() + 
            "[ lines: " + std::to_string(data.lineCount) + 
            ", empty lines: " + std::to_string(data.emptyLinesCount) +
            ", non empty lines" + std::to_string(data.nonEmptyLinesCount) + 
            "]\n";

}