#include <iostream>
#include "util.h"
#include "Scheduler.h"
using namespace std;

int main(int argc, char *argv[])
{
    check_argv(argc, argv);
    Scheduler scheduler(argv[1], argv[2]);
    scheduler.read_input();
    // scheduler.print_process();
    scheduler.scheduling();
    scheduler.print_output();
    scheduler.print_output(true);

    return 0;
}
