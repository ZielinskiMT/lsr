#ifndef NODE_H
#define NODE_H

#include <filesystem>
#include <vector>
#include "fsXxxData.h"


class Node{
    public:
        Node(const std::filesystem::path path): __path(path) {}

        std::filesystem::path path(){
            return __path;
        }

        virtual std::vector<Node *> scan(){
            return std::vector<Node *>();
        } 

        virtual const std::string string(){
            return __path.filename().string();
        };

        fsDirData data;

    protected:
        std::filesystem::path __path;
};


class dirNode: public Node {
    public:
        dirNode(const std::filesystem::path path): Node(path){};

        std::vector<Node *> scan();

        const std::string string();
};


class fileNode: public Node {
    public:
        fileNode(const std::filesystem::path path): Node(path){};

        std::vector<Node *> scan();

        const std::string string();
};

#endif  /* NODE_H */