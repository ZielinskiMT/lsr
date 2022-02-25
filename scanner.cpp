#include "scanner.h"
#include <limits>

Scanner::Scanner(){
}

fsDirData Scanner::scan(std::istream & istr){

    __fileData.lineCount = 0;
    __fileData.nonEmptyLinesCount = 0;
    __fileData.emptyLinesCount = 0;

    istr.seekg(0, istr.end);
    std::streampos endPos = istr.tellg();
    istr.seekg(0, istr.beg);

    if(istr.tellg() == endPos)
        return __fileData;

    while(true){
       std::string str;
        getline(istr, str);

        if(str.length() == 0)
            __fileData.emptyLinesCount++;
        else
            __fileData.nonEmptyLinesCount++;

        if(istr.bad()){
            break;
        }
        if(istr.eof()){
            break;
        }
    }
    __fileData.lineCount = __fileData.emptyLinesCount +__fileData.nonEmptyLinesCount;
    return __fileData;
 }

int Scanner::lineCount(){
    return __fileData.lineCount;
}

int Scanner::emptyLineCount(){   
    return __fileData.emptyLinesCount;
}

int Scanner::nonEmpytLineCount(){
    return __fileData.nonEmptyLinesCount;
}