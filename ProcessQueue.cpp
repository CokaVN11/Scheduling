#include "ProcessQueue.h"

void ProcessQueue::push(const process &p, bool cpu_prior)
{
    if (cpu_prior) {
        this->c.push_back(p);
        std::push_heap(this->c.begin(), this->c.end(), cpu_cmp());
    }
    else
        std::priority_queue<process, std::vector<process>, std::greater<process>>::push(p);
}

void ProcessQueue::print()
{
    for (const auto& i : this->c) std::cout << i << std::endl;
}
