#include "util.h"

void read_file(string path, int &type, int &q, process_queue &pq)
{
    ifstream file(path, ios::in);
    int n;
    file >> type;
    if (type == 2)
        file >> q;
    bool cpu_prior = type == 3 || type == 4;
    file >> n;
    for (int i = 0; i < n; i++)
    {
        process p;

        p.id = i + 1;
        file >> p.arrival;
        p.init = p.arrival;
        p.cpu_prior = cpu_prior;

        string tmp;
        file.ignore();
        getline(file, tmp);
        stringstream ss(tmp);

        int x;
        while (ss >> x)
        {
            p.cpu.push_back(x);
            if (ss.eof())
                break;
            ss >> x;
            p.resource.push_back(x);
        }

        pq.push(p);
    }
}

void show_usage()
{
    cout << "Usage: 21127071.exe <input_file> <output_file>\n";
    cout << "       <input_file>: Path to the input files (.txt).\n";
    cout << "       <output_file>: Path to the output file (.txt).\n";
}

bool check_txt(const string path)
{
    return path.substr(path.find_last_of(".") + 1) == "txt";
}

void check_argv(const int argc, char *argv[])
{
    if (argc != 3)
    {
        show_usage();
        exit(1);
    }
    if (!check_txt(argv[1]) || !check_txt(argv[2]))
    {
        show_usage();
        exit(1);
    }
}

process::process()
{
    id = 0;
    arrival = 0;
    waiting_time = 0;
    turnaround_time = 0;
    need_cpu = true;
}

process::process(const process &p)
{
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
