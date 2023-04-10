#ifndef PROCESS_QUEUE_H
#define PROCESS_QUEUE_H
#include <deque>
#include "util.h"

struct cpu_cmp {
    bool operator()(const process& a, const process& b) {
        if (a.cpu.empty() || b.cpu.empty())
            return a.cpu.empty() < b.cpu.empty();
        return a.cpu[0] > b.cpu[0];
    }
};

class ProcessQueue : public std::priority_queue<process, std::vector<process>, std::greater<process>> {
public:
    void push(const process& p, bool cpu_prior = false);
    void print();
};

#endif
