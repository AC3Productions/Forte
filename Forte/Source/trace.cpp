// file:   trace.cpp
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//   Implementation of the classes defined in trace.h
#pragma once
#include <forte.h> // includes trace.h
#include <sstream>
#include <trace.h>

// Static Member Variable Declaration
TraceLogger *TraceLogger::s_instance = nullptr;


TraceLogger *TraceLogger::Instance()
{
  if (!s_instance)
    s_instance = new TraceLogger;
  return s_instance;
}

TraceLogger::TraceLogger() : m_log_file("trace.log"), 
                             verbose(Trace::Severity::S_VERBOSE, &m_log_file),
                             info(Trace::Severity::S_INFO, &m_log_file), 
                             warning(Trace::Severity::S_INFO, &m_log_file), 
                             error(Trace::Severity::S_INFO, &m_log_file), 
                             m_min_severity(Trace::Severity::S_INFO)
{
}
