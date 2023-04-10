#include "util.h"

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
