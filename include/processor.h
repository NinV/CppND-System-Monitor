#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<vector>

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  Processor();

  // TODO: Declare any necessary private members
 private:
    std::vector<long> processorStates_{std::vector<long>(10, -1)};
};

#endif