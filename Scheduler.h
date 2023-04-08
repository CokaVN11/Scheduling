#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <string>
#include <fstream>
#include <functional>
#include "util.h"
#include "ProcessQueue.h"
using namespace std;

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
	void sjf_upgrade();
	void srtn();
	void srtn_upgrade();

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
