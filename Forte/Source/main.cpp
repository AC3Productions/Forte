// file:   main.cpp
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//  The program driver. Creates, updates, and shuts down the engine.
#pragma once
#include <forte.h>
#include "Engine.h"

int main(int argc, char** argv)
{
  
  Engine engine;
  engine.Init();
  
  // Default severity level
  TraceLogger::Trace::Severity sev_level = TraceLogger::Trace::Severity::S_INFO;
  
  // If necessary, set new severity level
  if (argc > 1)
  {
    sev_level = TraceLogger::Trace::Severity(std::atoi(argv[1]));
    trace.SetMinSeverity(sev_level);
  }

  while (engine.IsRunning())
  {
    engine.Update();
    engine.Render();
  }
  
  engine.ShutDown();


  return 0;
}