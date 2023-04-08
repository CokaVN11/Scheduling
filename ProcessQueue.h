#ifndef PROCESS_QUEUE_H
#define PROCESS_QUEUE_H

#include <deque>
#include "util.h"
class ProcessQueue{
private:
    deque<process> pq;
    bool cpu_prior;
    int size = 0;

    void push_cpu_prior(process p);
    void push_arrival_prior(process p);
public:
    ProcessQueue();
    ProcessQueue(bool cpu_prior);
    void push(process p);
    process top();
    void pop();
    bool empty();
    void print();
};

#endif
