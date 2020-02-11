#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <linux_parser.h>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               
  std::string User();                      
  std::string Command();                   
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime();                       
  bool operator<(Process const& a) const;  
  Process(int pid, float cpuUti, long uptime,
          std::string user, std::string command,
          std::string ram);

 private:
    int pid_;
    float cpuUti_;
    long uptime_;
    std::string user_, command_, ram_;

};

#endif