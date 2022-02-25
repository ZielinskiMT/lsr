#include "threadPool.h"


threadPool::threadPool(std::size_t maxNoOfThreads):
__maxNoOfThreads(maxNoOfThreads),
__returnWhenIdle(false),
__waitingWorkers(0),
__maxNoOfThreadsUsed(0),
__loopingThreads(0) {}

threadPool::~threadPool(){
    /* join all threads and delete nodes */
/*     const std::unique_lock<std::mutex> lock(__dataLock);
    while(!__nodes.empty()){
        Node *nptr = __nodes.back();
        __nodes.pop_back();
        delete(nptr);
    } */
}


void threadPool::start(std::size_t poolSize){
    if (__workers.size() <  poolSize){
        for(std::size_t i = __workers.size(); i < poolSize; i++){
            __workers.push_back( std::thread(&threadPool::thread_loop, this) );
            __loopingThreads++;
        }
    }
    __maxNoOfThreadsUsed =  __workers.size();
}


void threadPool::add(std::vector<Node *> nodes){

    /* check if there is something in nodes */
    if(nodes.empty())
        return;
    /* start workers if there is place for them */
    std::size_t newNodesSize = nodes.size();
/* 
    if (__workers.size() < ( __maxNoOfThreads - 1)){
        for(int i = 0; i < std::min(newNodesSize, (__maxNoOfThreads - 1)); i++){
            __workers.push_back( std::thread(&threadPool::thread_loop, this) );
            __loopingThreads++;
        }
    }
    __maxNoOfThreadsUsed = std::max(__maxNoOfThreadsUsed, __workers.size()); */
    /* add nodes to process and notify workers */
    {
        const std::unique_lock<std::mutex> lock(__dataLock);
        /* add nodes to "queue" */
        std::move(nodes.begin(), nodes.end(), std::back_inserter(__nodes));
    }
    if(newNodesSize > 1)
        __manager.notify_all();
    else
        __manager.notify_one();
}

void threadPool::add(Node * node){
    /* start worker if there is place for it */
/*     if (__workers.size() < ( __maxNoOfThreads - 1)){
        __workers.push_back( std::thread(&threadPool::thread_loop, this) );
        __loopingThreads++;
    }
    __maxNoOfThreadsUsed = std::max(__maxNoOfThreadsUsed, __workers.size()); */
    /* add node and notify workers */
    {
        const std::unique_lock<std::mutex> lock(__dataLock);
        __nodes.push_back(node);
    }
    __manager.notify_one();
}

void threadPool::finish(){
    {
        const std::unique_lock<std::mutex> lock(__dataLock);
        __returnWhenIdle = true;
    }
    __manager.notify_all();

    for(auto &w : __workers){
        w.join();
    }
    return;
}

void threadPool::thread_loop(){
    Node *nptr = NULL;
    while(true){
        /* Wait for data or exit */
        {
            std::unique_lock<std::mutex> lock(__dataLock);
            __waitingWorkers++;
            __manager.wait(lock, [this](){return !__nodes.empty() || ( this->__returnWhenIdle  && ( this->__waitingWorkers >= this->__loopingThreads));});
            if( !__nodes.empty()){
                nptr = __nodes.back();
                __nodes.pop_back();
            }
            else if( __returnWhenIdle  && ( __waitingWorkers >= __loopingThreads)){
                __loopingThreads--;
                __manager.notify_all();
                return;
            }
            else{
                nptr = NULL;
            }

            __waitingWorkers--;
        }

        /* Process node */
        if(nptr != NULL){
            std::vector<Node *> subnodes = nptr->scan();
            this->add(subnodes);
            __rootData += nptr->data;
            delete(nptr);
            nptr = NULL;
        }
    }
}