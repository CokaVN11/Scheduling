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
    friend bool operator<(const process& a, const process& b) {
        return a.arrival < b.arrival;
    }
    friend bool operator>(const process& a, const process& b) {
        return a.arrival > b.arrival;
    }
    ~process() {}

    static bool cpu_cmp(const process& a, const process& b) {
        if (a.cpu.empty() || b.need_cpu == false)
            return false;
        if (b.cpu.empty() || a.need_cpu == false)
            return true;
        return a.cpu[0] > b.cpu[0];
    }
};

typedef priority_queue<process, vector<process>, greater<process>> process_queue;

void read_file(string path, int &type, int &q, process_queue& pq);
string print_file(string path);
void show_usage();
void check_argv(int argc, char* argv[]);
bool check_txt(string path);

#endif
