#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iomanip>

#include "linux_parser.h"

using std::stof;
using std::stoi;
using std::stol;
using std::string;
using std::to_string;
using std::vector;


// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float memTotal, memFree;
  string smemTotal, smemFree;
  string line, rowName;

  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    
    // get total memory from first line
    std::getline(filestream, line);
    std::istringstream ss1(line);
    ss1 >> rowName >> smemTotal;

    // get current free memory from second line
    std::getline(filestream, line);
    std::istringstream ss2(line);
    ss2 >> rowName >> smemFree;
    
    // convert from string to float
    memTotal = stof(smemTotal);
    memFree = stof(smemFree);

    filestream.close();
    return (memTotal - memFree)/memTotal;
  }
  return 0.0; 
  }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long upTime;
  string supTime;
  string line;

  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    
    // get system uptime
    std::getline(filestream, line);
    std::istringstream ss1(line);
    ss1 >> supTime;    
    
    // convert from string to int
    upTime = stoi(supTime);
    
    filestream.close();
    return upTime;
  }
  return 0; }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  vector<long> cpuUti = LinuxParser::CpuUtilization();
  return LinuxParser::ActiveJiffies(cpuUti) + LinuxParser::IdleJiffies(cpuUti); }

long LinuxParser::Jiffies(vector<long> cpuUti){
  return LinuxParser::ActiveJiffies(cpuUti) + LinuxParser::IdleJiffies(cpuUti); 
  }


// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  vector<long> cpuUti = LinuxParser::CpuUtilization();
  return LinuxParser::ActiveJiffies(cpuUti); 
}

long LinuxParser::ActiveJiffies(vector<long> cpuUti){
  long activeJiffies;
  // NonIdle = user + nice + system + irq + softirq + steal
  activeJiffies = cpuUti[kUser_] + cpuUti[kNice_] + cpuUti[kSystem_] 
                  + cpuUti[kIRQ_] + cpuUti[kSoftIRQ_] + cpuUti[kSteal_];
  return activeJiffies; 

};

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  vector<long> cpuUti = LinuxParser::CpuUtilization();
  return LinuxParser::IdleJiffies(cpuUti); 
}
long LinuxParser::IdleJiffies(vector<long> cpuUti){
  long idleJiffies;
  // Idle = idle + iowait
  idleJiffies = cpuUti[kIdle_] + cpuUti[kIOwait_];
  return idleJiffies; 

}

// TODO: Read and return CPU utilization
vector<long> LinuxParser::CpuUtilization() {
  int numCPUStates = 10;
  vector<long> jiffies;
  string line, jiffy, start;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()){
    
    // get cpu utilization info from the first line
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> start;
    for(int i=0; i<numCPUStates; i++){
      linestream >> jiffy;
      jiffies.push_back(stol(jiffy));
    }
    filestream.close();
  }
  return jiffies;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line, start, totalProc;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  
  if (filestream.is_open()) {
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> start;
      if (start == "processes"){
        linestream >> totalProc;
        filestream.close();
        return stof(totalProc);
      }
    }
    filestream.close();
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line, start, runningProc;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  
  if (filestream.is_open()) {
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> start;
      if (start == "procs_running"){
        linestream >> runningProc;
        filestream.close();
        return stof(runningProc);
      }
    }
    filestream.close();
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()){
    std::getline(filestream, line);
    filestream.close();
    return line;
  }
  return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line, start, memUsages;
  int num;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      linestream >> start;
      if(start == "VmSize:"){
        linestream >> memUsages;

        // kB --> MB
        num = stoi(memUsages) / 1000;
        std::ostringstream ostr;

        // Set Fixed -Point Notation
        ostr << std::fixed;
        
        // Set precision to 1 digits
        ostr << std::setprecision(1);
        
        // Set width to 5
        ostr << std::setfill(' ') << std::setw(5);
        
        // Add num to stream
        ostr << num;

        memUsages = ostr.str();
        return memUsages;
      }
    }
    filestream.close();
  }
  return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line, start, Uid;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      linestream >> start;
      if(start == "Uid:"){
        linestream >> Uid;
        return Uid;
      }
    }
    filestream.close();
  }
  return string(); 
}

// lookup table
std::map<int, std::string> UidToUsername;

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string line, username, pwd, uid_;
  int Uid_ = stoi(LinuxParser::Uid(pid));
  string user;
  // construct lookup table
  if (UidToUsername.empty()){
    std::ifstream filestream(kPasswordPath);
    if(filestream.is_open()){
      while (std::getline(filestream, line))
      {
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream linestream(line);
        linestream >> username >> pwd >> uid_;
        UidToUsername[stoi(uid_)] = username;
      }
    }
  }
  if (UidToUsername.find(Uid_) != UidToUsername.end()){
    user = UidToUsername[Uid_];
    return user;
  };
  return string(); 
}

// int utimeIdx{14}, stimeIdx{15}, cutimeIdx{16}, cstimeIdx{17}, starttimeIdx{22};
vector<string> LinuxParser::GetStat(int pid){
  int starttimeIdx{22};
  vector<string> stat;
  string line;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      string temp;
      for(int i=1; i <= starttimeIdx; i++){
        linestream >> temp;
        stat.push_back(temp);
      }
    }
    filestream.close();
  }
  return stat;
}

// 1-based index
// int utimeIdx{14}, stimeIdx{15}, cutimeIdx{16}, cstimeIdx{17}, starttimeIdx{22};
// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
// long LinuxParser::StartTime(int pid) { 
//   vector<std::string> stat=GetStat(pid);
//   long uptime;
//   if (!stat.empty()){
//     uptime = stol(stat[starttimeIdx -1]);
//     return uptime;
//   }
//   return 0; 
// }
