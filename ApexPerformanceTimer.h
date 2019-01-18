#ifndef APEXPERFORMANCETIMER_H
#define APEXPERFORMANCETIMER_H

#define ENABLE_APEXPERFORMANCE

// Immediate will print right after the elapsed time is obtained
// may affect performance 
// Retained collects data so that it can be shown at the end of the
// program 
// if show immediate is set to true will enter retained mode
#define APEXPERFORMANCE_SHOWIMMEDIATE false

#ifdef ENABLE_APEXPERFORMANCE

#include <chrono>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std::chrono;
using namespace std;

#define PERFORMANCE_PRINTF_FUNC printf

class ApexPerformanceTimer
{
 public:
  // Constructor for the performance timer 
  ApexPerformanceTimer(const char* strText, bool bShowImmediate);
  // Destructor for the performance timer 
  ~ApexPerformanceTimer();

  // Disallows copying cant have the same performance timer twice 
  ApexPerformanceTimer(const ApexPerformanceTimer&) = delete;
  ApexPerformanceTimer& operator=(const ApexPerformanceTimer&) = delete;

  static void ReportAll();
  
 private:
  unsigned m_id;
  const char *m_str;
  const bool m_bShowImmediate;

  time_point<std::chrono::high_resolution_clock> t_start;
  time_point<std::chrono::high_resolution_clock> t_stop;

  duration<double> t_elapsed;

  static std::vector<std::tuple<std::string, duration<double>, int>> s_data;
  static int s_indent;
};

// Concatenates Preprocessor to a counter macro to create a unique string 
#define PP_CAT(a,b) PP_CAT_I(a,b)
#define PP_CAT_I(a,b) PP_CAT_II(~, a ## b)
#define PP_CAT_II(p, res) res
#define UNIQUE_NAME(base) PP_CAT(base, __COUNTER__)


#define APEXPERFORMANCETIMER_FUNCSTART ApexPerformanceTimer UNIQUE_NAME(__func__)((std::string(__func__) +" : %f\n").c_str(), APEXPERFORMANCE_SHOWIMMEDIATE)
#define APEXPERFORMANCETIMER_SCOPED(str) ApexPerformanceTimer UNIQUE_NAME(__func__)((std::string(str) +" : %f\n").c_str(), APEXPERFORMANCE_SHOWIMMEDIATE)
#define APEXPERFORMANCETIMER_START(str) { ApexPerformanceTimer UNIQUE_NAME(__func__)((std::string(str) +" : %f\n").c_str(), APEXPERFORMANCE_SHOWIMMEDIATE)
#define APEXPERFORMANCETIMER_END }
// Show the current data from collected data
#define APEXPERFORMANCETIMER_REPORTALL ApexPerformanceTimer::ReportAll
// will show the data but after the main function is done 
#define APEXPERFORMANCETIMER_REPORTALL_ATEXIT atexit(ApexPerformanceTimer::ReportAll);

#else 

#define APEXPERFORMANCETIMER_FUNCSTART
#define APEXPERFORMANCETIMER_SCOPED
#define APEXPERFORMANCETIMER_START
#define APEXPERFORMANCETIMER_END
#define APEXPERFORMANCETIMER_REPORTALL 
#define APEXPERFORMANCETIMER_REPORTALL_ATEXIT 

#endif // ENABLE_SIMPLEPERF

#endif // APEXPERFORMANCETIMER
