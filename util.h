#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class process {
public :
    int id;
    int arrival;
    int init;
    vector<int> cpu;
    vector<int> resource;
    int waiting_time;
    int turnaround_time;
    bool need_cpu;

    // true: cpu time is a priority when comparing
    bool cpu_prior = false;

    process();

    process(const process& p);

    friend bool operator<(const process& a, const process& b) {
        return a.arrival < b.arrival;
    }
    friend bool operator>(const process& a, const process& b) {
        return a.arrival > b.arrival;
    }

    friend ostream& operator<<(ostream& os, const process& p)
    {
        os << "Process " << p.id << "\n";
        os << "Arrival: " << p.arrival << "\n";
        os << "CPU: ";
        for (auto i : p.cpu) os << i << " ";
        os << "\nResource: ";
        for (auto i : p.resource) os << i << " ";
        os << "\n";
        return os;
    }
};

typedef priority_queue<process, vector<process>, greater<process>> process_queue;

void show_usage();
void check_argv(int argc, char* argv[]);
bool check_txt(string path);

#endif
