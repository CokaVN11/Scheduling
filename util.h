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

    process() {
        id = 0;
        arrival = 0;
        waiting_time = 0;
        turnaround_time = 0;
        need_cpu = true;
    }

    process(const process& p) {
        // cout << "copy\n";
        id = p.id;
        arrival = p.arrival;
        init = p.init;
        cpu = p.cpu;
        resource = p.resource;
        waiting_time = p.waiting_time;
        turnaround_time = p.turnaround_time;
        need_cpu = p.need_cpu;
        cpu_prior = p.cpu_prior;
    }

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

    static bool cpu_cmp(const process& a, const process& b) {
        if (a.cpu.empty() || b.cpu.empty())
            return a.cpu.empty() < b.cpu.empty();
        if (a.cpu[0] == b.cpu[0])
            return a.arrival > b.arrival;
        return a.cpu[0] > b.cpu[0];
    }
};


string print_file(string path);
void show_usage();
void check_argv(int argc, char* argv[]);
bool check_txt(string path);

#endif
