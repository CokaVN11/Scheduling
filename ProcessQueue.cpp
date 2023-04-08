#include "ProcessQueue.h"

void ProcessQueue::push_cpu_prior(process p)
{
    if (pq.empty()) {
        pq.push_back(p);
    } else {
        for (int i = 0; i < size; ++i) {
            if (p.cpu[0] < pq[i].cpu[0]) {
                pq.insert(pq.begin() + i, p);
                break;
            }
        }
    }
    ++size;
}

void ProcessQueue::push_arrival_prior(process p)
{
    if (pq.empty()) {
        pq.push_back(p);
    } else {
        for (int i = 0; i < size; ++i) {
            if (p.arrival < pq[i].arrival) {
                pq.insert(pq.begin() + i, p);
                break;
            }
        }
    }
    ++size;
}

ProcessQueue::ProcessQueue()
    : cpu_prior(false)
{
}

ProcessQueue::ProcessQueue(bool cpu_prior)
    : cpu_prior(cpu_prior)
{
}

void ProcessQueue::push(process p)
{

}
