#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "system.h"


using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 

    // because a Pid can be reused when a process ended, we need to re-scan 
    // the pid list each time System object update
    processes_.clear();
    vector<int> Pids_ = LinuxParser::Pids();
    for (int pid : Pids_){
        string pcommand = LinuxParser::Command(pid);
        string puser = LinuxParser::User(pid);
        string pram = LinuxParser::Ram(pid);

        // calc process cpu utilization, uptime 
        vector<string> pstat = LinuxParser::GetStat(pid);
        // stat_ = LinuxParser::GetStat(pid_);
        if (!pstat.empty()){
            // utimeIdx{14}, stimeIdx{15}, cutimeIdx{16}, cstimeIdx{17}, starttimeIdx{22}
            long utime = std::stol(pstat[utimeIdx-1]);
            long stime = std::stol(pstat[stimeIdx-1]);
            long cutime = std::stol(pstat[cutimeIdx-1]);
            long cstime = std::stol(pstat[cstimeIdx-1]);
            long starttime = std::stol(pstat[starttimeIdx-1]);
            float totalTime = float(utime + stime + cutime + cstime)/sysconf(_SC_CLK_TCK);
            float pelapsedTime = uptime - (starttime / sysconf(_SC_CLK_TCK));
            float pcpuUti =  totalTime / pelapsedTime; 
            processes_.push_back(Process(pid, pcpuUti, totalTime, puser, pcommand, pram));
        }
    }
    std::sort(processes_.begin(), processes_.end());
    return processes_; 
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() {
    if (this->uptime == -1){this->uptime = LinuxParser::UpTime();}
    else {this->uptime++;}
    return this->uptime;
}