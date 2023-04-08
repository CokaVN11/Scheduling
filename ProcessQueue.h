#ifndef PROCESS_QUEUE_H
#define PROCESS_QUEUE_H
#include <deque>
#include "util.h"

class ProcessQueue{
private:
    struct Node {
        process value;
        Node* next = nullptr;
    };

    Node* head;
    Node* tail;
    int size = 0;

    void push_cpu_prior(const process& p);
    void push_arrival_prior(const process& p);
public:
    ProcessQueue();
    ~ProcessQueue();
    void push(const process& p, bool cpu_prior = false);
    process top();
    void pop();
    bool empty();
    void print();
};

#endif
