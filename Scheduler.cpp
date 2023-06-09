﻿#include "Scheduler.h"

Scheduler::Scheduler()
	: type(0), q(0)
{}

Scheduler::Scheduler(const string& input_path, const string& output_path)
	: input_path(std::move(input_path)), output_path(std::move(output_path)), type(0), q(0)
{}

void Scheduler::set_input(const string& input_path)
{
	this->input_path = std::move(input_path);
}

void Scheduler::set_output(const string& output_path)
{
	this->output_path = std::move(output_path);
}

void Scheduler::read_input()
{
	ifstream file(input_path, ios::in);
	file >> type;
	if (type == 2)
		file >> q;
	// bool cpu_prior = type == 3 || type == 4;
	int n = 0;
	file >> n;
	for (int i = 0; i < n; i++)
	{
		process p;

		p.id = i + 1;
		file >> p.arrival;
		p.init = p.arrival;
		// p.cpu_prior = cpu_prior;

		string tmp;
		file.ignore();
		getline(file, tmp);
		stringstream ss(tmp);

		int x;
		while (ss >> x)
		{
			p.cpu.push_back(x);
			if (ss.eof()) break;
			ss >> x;
			p.resource.push_back(x);
		}

		pq.push(p);
	}

	tt.resize(n);
	wt.resize(n);
}

void Scheduler::fcfs()
{
	cout << "FCFS running...\n";
    int cpu_time = 0;
    int resource_time = 0;

    while (!pq.empty())
    {
        process p = pq.top();
        pq.pop();

        if (p.cpu.empty() && p.resource.empty()) continue;
        if (p.need_cpu)
        {
            if (p.arrival > cpu_time)
            {
                for (int i = 0; i < p.arrival - cpu_time; ++i) cpu_gantt.push_back(-1);
                cpu_time = p.arrival;
            }
            wt[p.id - 1] += abs(cpu_time - p.arrival);

            for (int i = 0; i < p.cpu[0]; ++i) cpu_gantt.push_back(p.id);
            cpu_time += p.cpu[0];
            tt[p.id - 1] += cpu_time - p.arrival;

            p.cpu.erase(p.cpu.begin());
            p.need_cpu = false;

            p.arrival = cpu_time;

        }
        else
            resource_schedule(p, resource_time);
        pq.push(p);
    }
}

void Scheduler::rr()
{
	cout << "RR running...\n";
    int cpu_time = 0;
    int resource_time = 0;

    while (!pq.empty())
    {
        process p = pq.top();
        pq.pop();

        if (p.cpu.empty() && p.resource.empty()) continue;
        if (p.need_cpu)
        {
            if (p.arrival > cpu_time)
            {
                for (int i = 0; i < p.arrival - cpu_time; ++i)
                    cpu_gantt.push_back(-1);
                cpu_time = p.arrival;
            }
            wt[p.id - 1] += abs(cpu_time - p.arrival);

            // process time is the minimum of the cpu burst time and quantumn
            int process_time = min(p.cpu[0], q);
            for (int i = 0; i < process_time; ++i) cpu_gantt.push_back(p.id);
            cpu_time += process_time;
            tt[p.id - 1] += cpu_time - p.arrival;

            p.cpu[0] -= process_time;
            // if the process is not finished,
            // but quantumn for it end push it back to the queue
            if (p.cpu[0] == 0)
            {
                p.cpu.erase(p.cpu.begin());
                p.need_cpu = false;
            }
            p.arrival = cpu_time;
        }
        else
            resource_schedule(p, resource_time);

        pq.push(p);
    }
}

void Scheduler::sjf()
{
	cout << "SJF running...\n";
    int cpu_time = 0;
    int resource_time = 0;

    CpuQueue ready_queue;
    ProcessQueue resource_queue;

    while (!pq.empty() || !ready_queue.empty() || !resource_queue.empty())
    {
        // when the process arrvive, push it into ready queue
        while (!pq.empty())
        {
            if (pq.top().need_cpu && pq.top().arrival <= cpu_time)
            {
                ready_queue.push(pq.top());
                pq.pop();
            }
            else if (!pq.top().need_cpu && pq.top().arrival <= resource_time)
            {
                resource_queue.push(pq.top());
                pq.pop();
            }
            else break;
        }

        if (!ready_queue.empty())
        {
            process p = ready_queue.top();
            ready_queue.pop();

            if (p.resource.empty() && p.cpu.empty()) continue;
            if (p.arrival > cpu_time)
            {
                for (int i = 0; i < p.arrival - cpu_time; ++i)
                    cpu_gantt.push_back(-1);
                cpu_time = p.arrival;
            }
            wt[p.id - 1] += abs(cpu_time - p.arrival);
            int process_time = p.cpu[0];
            for (int i = 0; i < process_time; ++i) cpu_gantt.push_back(p.id);
            cpu_time += process_time;
            tt[p.id - 1] += cpu_time - p.arrival;
            p.arrival = cpu_time;
            p.cpu[0] -= process_time;
            if (p.cpu[0] == 0)
            {
                p.cpu.erase(p.cpu.begin());
                p.need_cpu = false;
                resource_queue.push(p);
            }
            else pq.push(p);
        } else {
            if (pq.empty()) break;
            if (!pq.top().need_cpu) continue;
            int idle_time = pq.top().arrival - cpu_time;
            for (int i = 0; i < idle_time; ++i)
                cpu_gantt.push_back(-1);
            cpu_time += idle_time;
        }

        if (!resource_queue.empty())
        {
            process p = resource_queue.top();
            resource_queue.pop();

            if (p.resource.empty() && p.cpu.empty()) continue;
            resource_schedule(p, resource_time);
            pq.push(p);
        } else {
            if (pq.empty()) break;
            if (pq.top().need_cpu) continue;
            int idle_time = pq.top().arrival - resource_time;
            for (int i = 0; i < idle_time; ++i)
                resource_gantt.push_back(-1);
            resource_time += idle_time;
        }
    }
}

void Scheduler::srtn(){
    cout << "SRTN running...\n";
    int cpu_time = 0;
    int resource_time = 0;

    CpuQueue ready_queue;
    ProcessQueue resource_queue;

    while (!pq.empty() || !ready_queue.empty() || !resource_queue.empty())
    {
        while (!pq.empty())
        {
            if (pq.top().need_cpu && pq.top().arrival <= cpu_time)
            {
                ready_queue.push(pq.top());
                pq.pop();
            }
            else if (!pq.top().need_cpu && pq.top().arrival <= resource_time)
            {
                resource_queue.push(pq.top());
                pq.pop();
            }
            else break;
        }

        if (!ready_queue.empty())
        {
            process p = ready_queue.top();
            ready_queue.pop();

            if (p.cpu.empty() && p.resource.empty()) continue;
            if (p.arrival > cpu_time)
            {
                for (int i = 0; i < p.arrival - cpu_time; ++i)
                    cpu_gantt.push_back(-1);
                cpu_time = p.arrival;
            }
            wt[p.id - 1] += abs(cpu_time - p.arrival);
            int process_time = p.cpu[0];
            if (!ready_queue.empty() && ready_queue.top().arrival > cpu_time)
                process_time = min(process_time, ready_queue.top().arrival - cpu_time);

            for (int i = 0; i < process_time; ++i) cpu_gantt.push_back(p.id);
            cpu_time += process_time;
            tt[p.id - 1] += cpu_time - p.arrival;
            p.arrival = cpu_time;
            p.cpu[0] -= process_time;
            if (p.cpu[0] == 0)
            {
                p.cpu.erase(p.cpu.begin());
                p.need_cpu = false;
                resource_queue.push(p);
            }
            else pq.push(p);
        } else {
            if (pq.empty()) break;
            if (!pq.top().need_cpu) continue;
            int idle_time = pq.top().arrival - cpu_time;
            for (int i = 0; i < idle_time; ++i)
                cpu_gantt.push_back(-1);
            cpu_time += idle_time;
        }

        if (!resource_queue.empty())
        {
            process p = resource_queue.top();
            resource_queue.pop();

            if (p.resource.empty() && p.cpu.empty()) continue;
            resource_schedule(p, resource_time);
            pq.push(p);
        } else {
            if (pq.empty()) break;
            if (pq.top().need_cpu) continue;
            int idle_time = pq.top().arrival - resource_time;
            for (int i = 0; i < idle_time; ++i)
                resource_gantt.push_back(-1);
            resource_time += idle_time;
        }
    }
}

void Scheduler::resource_schedule(process& p, int& time)
{
    if (p.resource.empty()) return;

    if (p.arrival > time)
    {
        for (int i = 0; i < p.arrival - time; ++i)
            resource_gantt.push_back(-1);
        time = p.arrival;
    }
    for (int i = 0; i < p.resource[0]; ++i)
        resource_gantt.push_back(p.id);
    time += p.resource[0];
    tt[p.id - 1] += time - p.arrival;
    p.resource.erase(p.resource.begin());
    p.arrival = time;
    p.need_cpu = true;
}

void Scheduler::scheduling()
{
	switch (type)
	{
	case 1:
		fcfs();
		break;
	case 2:
		rr();
		break;
	case 3:
		sjf();
		break;
	case 4:
		// srtn();
        srtn();
		break;
	default:
		cout << "Not supported scheduling type.\n";
		break;
	}
}

void Scheduler::print_output(bool console)
{
    if (console)
    {
        for (int& i : cpu_gantt)
        {
            if (i == -1)
                cout << "_ ";
            else
                cout << i << " ";
        }
        cout << "\n";
        for (int& i : resource_gantt)
        {
            if (i == -1)
                cout << "_ ";
            else
                cout << i << " ";
        }
        cout << "\n";
        for (int& i : tt)
            cout << i << " ";
        cout << "\n";
        for (int& i : wt)
            cout << i << " ";
    }
    else
    {
        ofstream out(output_path, ios::out);
        for (int& i : cpu_gantt)
        {
            if (i == -1)
                out << "_ ";
            else
                out << i << " ";
        }
        out << "\n";
        for (int& i : resource_gantt)
        {
            if (i == -1)
                out << "_ ";
            else
                out << i << " ";
        }
        out << "\n";
        for (int& i : tt)
            out << i << " ";
        out << "\n";
        for (int& i : wt)
            out << i << " ";
        out.close();
    }
}

void Scheduler::print_process()
{
    ProcessQueue tmp = pq;
    while (!tmp.empty())
    {
        process p = tmp.top();
        tmp.pop();
        cout << p << "====================\n";
    }
}
