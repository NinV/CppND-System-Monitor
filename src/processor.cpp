#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
Processor::Processor(){
    this->processorStates_ = LinuxParser::CpuUtilization();
}
float Processor::Utilization() { 
    std::vector<long> currentStates = LinuxParser::CpuUtilization();
    
    float deltaActiveJiffies = LinuxParser::ActiveJiffies(currentStates) - LinuxParser::ActiveJiffies(this->processorStates_);
    float deltaJiffies = LinuxParser::Jiffies(currentStates) - LinuxParser::Jiffies(this->processorStates_);

    // update current state
    this->processorStates_ = currentStates;
    
    return deltaActiveJiffies / deltaJiffies; }