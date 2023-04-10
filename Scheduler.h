#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <string>
#include <fstream>
#include <functional>
#include "util.h"
using namespace std;

struct cpu_cmp {
	bool operator()(const process& a, const process& b)
	{
		if (a.cpu.empty())
			return true;
		if (b.cpu.empty())
			return false;
		// if (a.arrival != b.arrival)
		// 	return a.arrival > b.arrival;
		return a.cpu[0] > b.cpu[0];
	}
};

typedef priority_queue<process, vector<process>, greater<process>> ProcessQueue;
typedef priority_queue<process, vector<process>, cpu_cmp> CpuQueue;

class Scheduler
{
private:
	string input_path;
	string output_path;
	int type, q;
	ProcessQueue pq;
	vector<int> cpu_gantt, resource_gantt, tt, wt;
	void fcfs();
	void rr();
	void sjf();
	void srtn();

	void resource_schedule(process& p, int& time);

public:
	Scheduler();
	Scheduler(const string& input_path, const string& output_path);
	void set_input(const string& input_path);
	void set_output(const string& output_path);

	void read_input();
	void print_output(bool console = false);
	void print_process();
	void scheduling();
};

#endif
