#include "fsXxxData.h"

fsFileData::fsFileData(){
    lineCount = 0;
    emptyLinesCount = 0;
    nonEmptyLinesCount = 0;
}

fsFileData& fsFileData::operator+=(const fsFileData& rhs){
    this->lineCount += rhs.lineCount;
    this->emptyLinesCount += rhs.emptyLinesCount;
    this->nonEmptyLinesCount += rhs.nonEmptyLinesCount;
    return *this;
}

fsFileData operator+(fsFileData lhs, const fsFileData& rhs){
    lhs.lineCount += rhs.lineCount;
    lhs.emptyLinesCount += rhs.emptyLinesCount;
    lhs.nonEmptyLinesCount += rhs.nonEmptyLinesCount;
    return lhs;
}

fsDirData::fsDirData(){
    subirsCount = 0;
    regFilesCount = 0;
    otherFilesCount = 0;
    lineCount = 0;
    emptyLinesCount = 0;
    nonEmptyLinesCount = 0;
}

fsDirData& fsDirData::operator+=(const fsDirData& rhs){
    fsFileData::operator+=(rhs);
    this->subirsCount += rhs.subirsCount;
    this->regFilesCount += rhs.regFilesCount;
    this->otherFilesCount += rhs.otherFilesCount;
    return *this;
}

fsDirData operator+(fsDirData lhs, const fsDirData& rhs){
    lhs = operator+(lhs, rhs);
    lhs.subirsCount += rhs.subirsCount;
    lhs.regFilesCount += rhs.regFilesCount;
    lhs.otherFilesCount += rhs.otherFilesCount;
    return lhs;
}