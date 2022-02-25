#ifndef DIRSCANNER_H
#define DIRSCANNER_H

#include <filesystem>
#include <vector>

class dirScanner{
    private:
        std::vector<std::filesystem::path> __subdirs;
        std::vector<std::filesystem::path> __regularFiles;
        std::vector<std::filesystem::path> __otherFiles;      
        std::filesystem::path __path;
        std::uintmax_t __linesCount;
        std::uintmax_t __nonEmptyLinesCount;
        std::uintmax_t __emptyLinesCount;

    public:
        dirScanner(std::filesystem::path path): __path(path) {};

        void scan();

        std::vector<std::filesystem::path> subdirs() { return __subdirs;}
        std::vector<std::filesystem::path> regularFiles() { return __regularFiles; }
        std::vector<std::filesystem::path> otherFiles() { return __otherFiles; }

};

#endif  /* DIRSCANNER_H */