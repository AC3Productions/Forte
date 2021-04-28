// file:   trace.h
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//  trace.h is included in forte.h, which means it's in every file.
//  The way trace logging should happen is by typing the following:
//  trace.[severity] << [your trace log message];
//  There are four severity levels:
//    -Verbose: For things that happen VERY often (like a system updating every frame).
//    -Info: For things of note that are proceeding as normal
//    -Warning: Something has gone wrong, but it's not the end of the world (ex. a sound couldn't play)
//    -Error: Something has gone pretty badly. These are likely errors the engine cannot recover from (probably gonna crash).

#ifndef TRACE_H
#define TRACE_H

#include <forte.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#define trace (*TraceLogger::Instance())

class TraceLogger
{
  private:
    std::ofstream m_log_file;

  public:  

    // Details:
    //  Singleton pattern; creates the TraceLogger if it doesn't exist yet.
    //  Use this function to get the tracelogger when you need it (but you should probably use the trace macro instead).
    static TraceLogger* Instance();

    class Trace
    {
      public:
      enum class Severity
      {
        S_VERBOSE,
        S_INFO,
        S_WARNING,
        S_ERROR,
        S_NONE = -1
      };

      Trace(Severity sev, std::ofstream *file) : m_sev(sev), m_file(file) {}

      template <typename T>
      Trace operator<<(const T &rhs) const
      {
        if (TraceLogger::Instance()->GetMinSeverity() > m_sev)
          return *this;

        std::stringstream log_message;

        switch (m_sev)
        {
          case Severity::S_VERBOSE:
            log_message << "[VERBOSE] ";
            break;
          case Severity::S_INFO:
            log_message << "[INFO]    ";
            break;
          case Severity::S_WARNING:
            log_message << "[WARNING] ";
            break;
          case Severity::S_ERROR:
            log_message << "[ERROR]   ";
            break;
          default:
            break;
        }

        // Add message
        log_message << rhs;

        

        std::cout << log_message.str() << std::endl;
        *m_file << log_message.str() << std::endl;

        return *this;

      }

      private:
      Severity m_sev;
      std::ofstream *m_file;
    };

    const Trace verbose;
    const Trace info;
    const Trace warning;
    const Trace error;

    void SetMinSeverity(Trace::Severity sev) { m_min_severity = sev; }
    Trace::Severity GetMinSeverity() { return m_min_severity; }

  private:

    static TraceLogger* s_instance;

    Trace::Severity m_min_severity;

    // Private constructor for singleton pattern
    TraceLogger();

};

#endif