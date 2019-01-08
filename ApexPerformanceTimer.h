#ifndef APEXPERFORMANCETIMER_H
#define APEXPERFORMANCETIMER_H

#define ENABLE_APEXPERFORMANCETIMER

#ifdef ENABLE_APEXPERFORMANCETIMER

#include <chrono>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std::chrono;

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
  duration<double> t_start;
  //duration<double> t_elapsed;

  static std::vector<std::tuple<std::string, double, int>> s_data;
  static int s_indent;
};

#define APEXPERFORMANCETIMER_FUNCSTART ApexPerformanceTimer __xperfstart##__COUNTER__(__FUNCTION__" : %f\n")
#define APEXPERFORMANCETIMER_SCOPED(str) ApexPerformanceTimer __xperfstart##__COUNTER__(str" : %f\n")
#define APEXPERFORMANCETIMER_START(str) { ApexPerformanceTimer __xperfstart##__COUNTER__(str" : %f\n")
#define APEXPERFORMANCETIMER_END }
#define APEXPERFORMANCETIMER_REPORTALL SimplePerfTimer::ReportAll
#define APEXPERFORMANCETIMER_REPORTALL_ATEXIT atexit(SimplePerfTimer::ReportAll);

#else 

#define APEXPERFORMANCETIMER_FUNCSTART
#define APEXPERFORMANCETIMER_SCOPED
#define APEXPERFORMANCETIMER_START
#define APEXPERFORMANCETIMER_END
#define APEXPERFORMANCETIMER_REPORTALL 
#define APEXPERFORMANCETIMER_REPORTALL_ATEXIT 

#endif // ENABLE_SIMPLEPERF
#endif // APEXPERFORMANCETIMER
