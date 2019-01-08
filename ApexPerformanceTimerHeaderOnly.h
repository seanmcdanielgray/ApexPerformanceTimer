#ifndef APEXPERFORMANCETIMER_H
#define APEXPERFORMANCETIMER_H

#define ENABLE_APEXPERFORMANCETIMER

#ifdef ENABLE_APEXPERFORMANCETIMER

#include <chrono>
#include <stdio.h>
#include <tuple>

using namespace std::chrono;

#define PERFORMANCE_PRINTF_FUNC printf

class ApexPerformanceTimer
{
 public:
  ApexPerformanceTimer(const char* strText)
    {
      auto t_start = high_resolution_clock::now();
    }

  ~ApexPerformanceTimer()
    {
      auto t_stop = high_resolution_clock::now();

      t_elapsed = duration_cast<duration<double>>(t_stop - t_start);

      PERFORMANCE_PRINTF_FUNC(m_str, t_elapsed);
    }

  ApexPerformanceTimer(const ApexPerformanceTimer&) = delete;
  ApexPerformanceTimer& operator=(const ApexPerformanceTimer&) = delete;

 private:
  const char *m_str;
  duration<double> t_start = high_resolution_clock::duration::zero();
  //duration<double> t_elapsed = high_resolution_clock::duration::zero();

};

#define APEXPERFORMANCETIMER_FUNCSTART ApexPerformanceTimer __xperfstart##__COUNTER__(__FUNCTION__" : %f\n")
#define APEXPERFORMANCETIMER_SCOPED(str) ApexPerformanceTimer __xperfstart##__COUNTER__(str" : %f\n")
#define APEXPERFORMANCETIMER_START(str) { ApexPerformanceTimer __xperfstart##__COUNTER__(str" : %f\n")
#define APEXPERFORMANCETIMER_END }

#else

#define APEXPERFORMANCETIMER_FUNCSTART
#define APEXPERFORMANCETIMER_SCOPED
#define APEXPERFORMANCETIMER_START
#define APEXPERFORMANCETIMER_END

#endif // ENABLE_APEXPERFORMANCETIMER                                                                                                                                               

#endif // APEXPERFORMANCETIMER_H

