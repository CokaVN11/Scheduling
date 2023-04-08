#include "ProcessQueue.h"

void ProcessQueue::push_cpu_prior(const process& p)
{
    if (head == nullptr) {
        head = new Node{p};
        tail = head;
        ++size;
        return;
    }

    if (head->value.cpu.empty() || p.cpu[0] < head->value.cpu[0]) {
        Node* temp = new Node{p};
        temp->next = head;
        head = temp;
    }
    else if (!tail->value.cpu.empty() && p.cpu[0] >= tail->value.cpu[0]) {
        Node* temp = new Node{p};
        tail->next = temp;
        tail = temp;
    }
    else {
        for (Node* cur = head; cur->next != nullptr; cur = cur->next) {
            Node* following = cur->next;
            if (following->value.cpu.empty() || p.cpu[0] <= following->value.cpu[0]) {
                Node* temp = new Node{p};
                temp->next = following;
                cur->next = temp;
                break;
            }
        }
    }

    ++size;
}

void ProcessQueue::push_arrival_prior(const process& p)
{
    if (head == nullptr) {
        head = new Node{p};
        tail = head;
        ++size;
        return;
    }

    if (p.arrival <= head->value.arrival) {
        Node* temp = new Node{p};
        temp->next = head;
        head = temp;
    }
    else if (p.arrival >= tail->value.arrival) {
        Node* temp = new Node{p};
        tail->next = temp;
        tail = temp;
    }
    else {
        for (Node* cur = head; cur->next != nullptr; cur = cur->next) {
            Node* following = cur->next;
            if (p.arrival < following->value.arrival) {
                Node* temp = new Node{p};
                temp->next = following;
                cur->next = temp;
                break;
            }
        }
    }
    ++size;
}

ProcessQueue::ProcessQueue()
    : head(nullptr), tail(nullptr), size(0)
{
}

ProcessQueue::~ProcessQueue()
{
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    head = tail = nullptr;
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
    return head->value;
}

void ProcessQueue::pop()
{
    if (head) {
        Node* temp = head;
        head = head->next;
        if (head == nullptr)
            tail = nullptr;
        delete temp;
    }
    --size;
}

bool ProcessQueue::empty()
{
    return (head == nullptr || tail == nullptr);
}

void ProcessQueue::print()
{
    for (Node* cur = head; cur; cur = cur->next)
        cout << cur->value << "\n";
}
