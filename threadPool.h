#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <condition_variable>
#include <atomic>
#include <thread>
#include <vector>
#include "nodeScanner.h"
#include "node.h"


class threadPool{
    fsDirData __rootData;
    std::size_t __maxNoOfThreads;
    std::size_t __maxNoOfThreadsUsed;
    std::size_t __loopingThreads;
    std::size_t __waitingWorkers;
    std::vector<std::thread> __workers;
    std::vector<Node *> __nodes;
    std::mutex __dataLock;
    std::condition_variable __manager;
    std::atomic<bool> __returnWhenIdle;

    public:
        threadPool(std::size_t maxNoOfThreads = std::thread::hardware_concurrency() );
        ~threadPool();

        void start(std::size_t poolSize = std::thread::hardware_concurrency());
        void add(std::vector<Node *> nodes);
        void add(Node * node);
        void finish();
        void thread_loop();
        fsDirData rootData(){ return __rootData; }
        std::size_t maxNoOfThreads(){return __maxNoOfThreads;}
        std::size_t maxNoOfThreadsUsed(){return __maxNoOfThreadsUsed;}
};

#endif  /* THREADPOOL_H */