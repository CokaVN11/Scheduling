#include "ProcessQueue.h"

int ProcessQueue::find_least_bigger_cpu(const process &p)
{
    int index = -1;

    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (process_queue[mid].cpu.empty() || p.cpu[0] <= process_queue[mid].cpu[0]) {
            index = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    return index;
}

void ProcessQueue::push_cpu_prior(const process &p)
{
    if (process_queue.empty()) {
        process_queue.push_back(p);
        ++size;
        return;
    }

    if (process_queue.front().cpu.empty() || (!p.cpu.empty() && p.cpu[0] < process_queue.front().cpu[0])) {
        process_queue.push_front(p);
    }
    else if (p.cpu.empty() || !process_queue.back().cpu.empty() && p.cpu[0] >= process_queue.back().cpu[0]) {
        process_queue.push_back(p);
    }
    else {
        // for (int i = 0; i < size; ++i) {
        //     if (process_queue[i].cpu.empty() || p.cpu[0] <= process_queue[i].cpu[0]) {
        //         process_queue.insert(process_queue.begin() + i, p);
        //         break;
        //     }
        // }
        int index = find_least_bigger_cpu(p);
        if (index != -1)
            process_queue.insert(process_queue.begin() + index, p);
        else {
            cout << "Error: cannot find the index to insert\n";
            return;
        }
    }

    ++size;
}

void ProcessQueue::push_arrival_prior(const process& p)
{
    if (process_queue.empty()) {
        process_queue.push_back(p);
        ++size;
        return;
    }

    if (p.arrival <= process_queue.front().arrival) {
        process_queue.push_front(p);
    }
    else if (p.arrival >= process_queue.back().arrival) {
        process_queue.push_back(p);
    }
    else {
        for (int i = 0; i < size; ++i) {
            if (p.arrival <= process_queue[i].arrival) {
                process_queue.insert(process_queue.begin() + i, p);
                break;
            }
        }
    }
    ++size;
}

ProcessQueue::ProcessQueue()
    : size(0)
{
}

ProcessQueue::~ProcessQueue()
{
    process_queue.clear();
    size = 0;
}

void ProcessQueue::push(const process& p, bool cpu_prior)
{
    if (cpu_prior)
        push_cpu_prior(p);
    else
        push_arrival_prior(p);
}

process ProcessQueue::top()
{
    return process_queue.front();
}

void ProcessQueue::pop()
{
    if (size == 0)
        return;
    process_queue.pop_front();
    --size;
}

bool ProcessQueue::empty()
{
    return (size == 0 || process_queue.empty());
}

void ProcessQueue::print()
{
    for (auto i : process_queue) {
        cout << i << "\n";
    }
}
