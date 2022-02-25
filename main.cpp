#include <iostream>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <chrono>
#include <thread>

#include "node.h"
#include "threadPool.h"

using namespace std;

namespace fs = std::filesystem;

int main(int argc, char** argv) {

    fs::path root;
    size_t poolSize(0); // if > 0 specifies No of threads to be used, if == 0  then std::thread::hardware_concurrency() value will be used

    /* COMMAND LINE ARUMENTS */
    if (argc == 4){
        /* nr of threads is given */
        if (string(argv[1]).compare("-t") == 0){
            try{
                poolSize = static_cast<size_t>(stoi(string(argv[2])));
                poolSize = max(poolSize, size_t(0));
            }
            catch(const std::exception& e){
                std::cerr << e.what() << '\n';
                cout << "Usage: lsr [-t <max nr of threads to use>] <path to a directory>\n";
                return -1;
            }
        }
        else{
            cout << "Usage: lsr [-t <max nr of threads to use>] <path to a directory>\n";
            return -1; 
        }
    }
    else if(argc == 2){
        poolSize = 0; 
    }
    else{
        cout << "Usage: lsr [-t <max nr of threads to use>] <path to a directory>\n";
        return -1; 
    }


    /* CHECK IF PATH ACTUALLY EXISTS AND IF IT IS A DIRECTORY */
    uint argPath = argc - 1;
    if(argv[argPath][0] =='/') // absolute path is given
        root = fs::path(argv[argPath]);
    else if(argv[argPath][0] =='.' && argv[argPath][1] =='/'){
        root = fs::current_path();
    }
    else if(argv[argPath][0] =='.' && argv[argPath][1] =='.'){
        root = fs::current_path().parent_path();
    }
    else{   // relative path is given
        root = fs::current_path();
        root /= argv[argPath];
    }
    if(!fs::exists(root)){
        cout << "! "<< root.string() << " does not exist!\nUsage: lsr <path to a directory>\n";
        return -1;
    }
    if(!fs::is_directory(root) ){
        cout << "! "<< root.string() << " is not a directory !\nUsage: lsr <path to a directory>\n";
        return -1;
    }

    /* SCAN NODES */
    cout << "Scanning...\n";
    Node * nptr = new dirNode(root);

    auto timeStart = std::chrono::high_resolution_clock::now();

    threadPool tp;
    if(poolSize > 0)
        tp.start(poolSize);
    else
        tp.start();
    tp.add(nptr);
    tp.finish();

    dirNode rootData(root);
    rootData.data += tp.rootData();

    auto timeStop = std::chrono::high_resolution_clock::now();   
    std::chrono::duration<double, std::milli> ms_double = timeStop - timeStart;
    
    /* PRINT SUMMARY */
    cout << rootData.string();
    cout << "\nBenchmark:\n   std::thread::hardware_concurrency() = " << tp.maxNoOfThreads() << "\n   threads used = " << tp.maxNoOfThreadsUsed() << "\n   Execution time: " << ms_double.count() << "ms\n\n";
    
    return 0;
}

