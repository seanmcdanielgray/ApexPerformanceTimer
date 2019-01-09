#ifndef APEXPERFORMANCETIMER_H
#define APEXPERFORMANCETIMER_H

#define ENABLE_APEXPERFORMANCE

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
  ApexPerformanceTimer(const char* strText, bool bShowImmediate);
  ~ApexPerformanceTimer();

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

#define APEXPERFORMANCETIMER_FUNCSTART ApexPerformanceTimer __xperfstart##__COUNTER__(__FUNCTION__" : %f\n", APEXPERFORMANCE_SHOWIMMEDIATE)
#define APEXPERFORMANCETIMER_SCOPED(str) ApexPerformanceTimer __xperfstart##__COUNTER__(str" : %f\n", APEXPERFORMANCE_SHOWIMMEDIATE)
#define APEXPERFORMANCETIMER_START(str) { ApexPerformanceTimer __xperfstart##__COUNTER__(str" : %f\n", APEXPERFORMANCE_SHOWIMMEDIATE)
#define APEXPERFORMANCETIMER_END }
#define APEXPERFORMANCETIMER_REPORTALL ApexPerformanceTimer::ReportAll
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
