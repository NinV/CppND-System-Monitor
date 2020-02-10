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

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    // stat_ = LinuxParser::GetStat(pid_);
    // if (!stat_.empty()){
    //     // utimeIdx{14}, stimeIdx{15}, cutimeIdx{16}, cstimeIdx{17}, starttimeIdx{22}
    //     long utime = std::stol(stat_[utimeIdx-1]);
    //     long stime = std::stol(stat_[stimeIdx-1]);
    //     long cutime = std::stol(stat_[cutimeIdx-1]);
    //     long cstime = std::stol(stat_[cstimeIdx-1]);
    //     long starttime = std::stol(stat_[starttimeIdx-1]);
    //     float totalTime = float(utime + stime + cutime + cstime)/sysconf(_SC_CLK_TCK);
    //     float elapsedTime = *systemUptime_ - (starttime / sysconf(_SC_CLK_TCK));
    //     return totalTime / elapsedTime; 
    // }
    return cpuUti_;
    }

// TODO: Return the command that generated this process
string Process::Command() { 
    return command_;
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    return ram_; 
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    return user_;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return uptime_;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    return (cpuUti_ > a.cpuUti_);
    }