#ifndef NODESCANNER_H
#define NODESCANNER_H

#include "node.h"
#include <vector>

class NodeScanner{
    public:
        NodeScanner(){}

        virtual std::vector<Node *> scan(dirNode& nod);
        virtual std::vector<Node *> scan(fileNode& nod);
};


#endif  /* NODESCANNER_H */