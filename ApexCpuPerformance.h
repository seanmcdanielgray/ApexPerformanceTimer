#ifndef APEXCPUPERFORMANCE_H
#define APEXCPUPERFORMANCE_H

#define ENABLE_APEXPERFORMANCE


#define APEXPERFORMANCE_SHOWIMMEDIATE false

#ifdef ENABLE_APEXPERFORMANCE

#include <stdio.h>
#include <vector>
#include <string>
#include "stdlib.h"


using namespace std;

class ApexCpuPerformance
{
public:
  // constructor and destructor
  ApexCpuPerformance(const char* strText, bool bShowImmediate);
  ApexCpuPerformance();

  //Disallows copyign cant have the same cpu performance monitor twice
  ApexCpuPerformance(const ApexCpuPerformance&) = delete;
  ApexCpuPerformance& operator=(const ApexCpuPerformance&) = delete;

  static void ReportAll();

  void init();

  double getCurrentValue();

private:
  unsigned m_id;
  const char *m_str;
  const bool m_bShowImmediate;
  static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;
  static int numProcessors;
}

// Concatenates Preprocessor to a counter macro to create a unique string
#define PP_CAT(a,b) PP_CAT_I(a,b)
#define PP_CAT_I(a,b) PP_CAT_II(~, a ## b)
#define PP_CAT_II(p, res) res
#define UNIQUE_NAME(base) PP_CAT(base, __COUNTER__)

#define APEXCPUPERFORMANCE_FUNCSTART ApexCpuPerformance UNIQUE_NAME(__func__)((std::string(__func__) +" : %f\n").c_str(), APEXCPUPERFORMANCE_SHOWIMMEDIATE)
#define APEXCPUPERFORMANCE_SCOPED(str) ApexCpuPerformance UNIQUE_NAME(__func__)((std::string(str) +" : %f\n").c_str(), APEXPERFORMANCE_SHOWIMMEDIATE)
#define APEXCPUPERFORMANCE_START(str) { ApexCpuPerformance UNIQUE_NAME(__func__)((std::string(str) +" : %f\n").c_str(), APEXCPUPERFORMANCE_SHOWIMMEDIATE)
#define APEXCPUPERFORMANCE_END }
// Show the current data from collected data
#define APEXCPUPERFORMANCE_REPORTALL ApexCpuPerformance::ReportAll
// will show the data but after the main function is done
#define APEXCPUPERFORMANCE_REPORTALL_ATEXIT atexit(ApexCpuPerformance::ReportAll);

#else

#define APEXCPUPERFORMANCE_FUNCSTART
#define APEXCPUPERFORMANCE_SCOPED
#define APEXCPUPERFORMANCE_START
#define APEXCPUPERFORMANCE_END
#define APEXCPUPERFORMANCE_REPORTALL
#define APEXCPUPERFORMANCE_REPORTALL_ATEXIT

#endif // ENABLE_SIMPLEPERF

#endif // APEXPERFORMANCETIMER

