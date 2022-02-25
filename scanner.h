#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include "fsXxxData.h"

class Scanner {
    private:
        fsDirData __fileData;
    public:
        Scanner();

        fsDirData scan(std::istream & istr);
        int lineCount();
        int emptyLineCount();
        int nonEmpytLineCount();
};

#endif  /* SCANNER_H */