#ifndef FS_XXX_DATA_H
#define FS_XXX_DATA_H

#include<iostream>

class fsFileData
{
    public:
        fsFileData();

        int lineCount;
        int nonEmptyLinesCount;
        int emptyLinesCount;

        virtual fsFileData& operator+=(const fsFileData& rhs);
        friend fsFileData operator+(fsFileData lhs, const fsFileData& rhs);
};

class fsDirData: public fsFileData
{
    public:
        fsDirData();

        int subirsCount;
        int regFilesCount;
        int otherFilesCount;

        fsDirData& operator+=(const fsDirData& rhs);
        friend fsDirData operator+(fsDirData lhs, const fsFileData& rhs);        
};

#endif  /* FS_XXX_DATA_H */