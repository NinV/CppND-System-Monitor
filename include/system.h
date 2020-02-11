#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "linux_parser.h"

class System {
 public:
  Processor& Cpu();                   
  std::vector<Process>& Processes();  
  float MemoryUtilization();          
  long UpTime();                      
  int TotalProcesses();               
  int RunningProcesses();             
  std::string Kernel();               
  std::string OperatingSystem();      

  
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
  long uptime{-1};
  
  // 1-based index (for extracting data for process)
  static const int utimeIdx{14}, stimeIdx{15}, cutimeIdx{16}, cstimeIdx{17}, starttimeIdx{22};
};

#endif