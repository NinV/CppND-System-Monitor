#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
Process::Process(int pid, float cpuUti, long uptime, std::string user, std::string command, std::string ram){
    pid_ = pid;
    cpuUti_ = cpuUti;
    uptime_ = uptime;
    user_ = user;
    command_ = command;
    ram_ = ram;

}
int Process::Pid() {
    return pid_;
}

// Return this process's CPU utilization
// TODO: The cpu utilization calculation should reflect recent changes --> need update
float Process::CpuUtilization() { return cpuUti_; }

// Return the command that generated this process
string Process::Command() { return command_; }

// Return this process's memory utilization
string Process::Ram() { return ram_; }

// Return the user (name) that generated this process
string Process::User() { return user_; }

// Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { return (cpuUti_ > a.cpuUti_); }