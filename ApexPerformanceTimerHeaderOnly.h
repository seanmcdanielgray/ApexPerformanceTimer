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

  duration<double> getStart() const{return t_start;}
  duration<double> getStop() const{return t_stop;}
  duration<double> getElapsed() const{return (t_stop - t_start);}
  
  void setStart(duration<double> start) const{start = t_start;}
  void setStop(duration<double> stop) const{stop = t_stop;}

  ApexPerformanceTimer(const char* strText)
    {
      //auto t_start = high_resolution_clock::now();

      /* I need something here to set the start time */
      duration<double> tmp = duration_cast<duration<double>>(high_resolution_clock::now())
      setStart(tmp);
    }

  ~ApexPerformanceTimer()
    {
      //auto t_stop = high_resolution_clock::now();

      /* I need something here to set the stop time */
      setStop(high_resolution_clock::now());

      //t_elapsed = duration_cast<duration<double>>(t_stop - t_start);

      /* I need something here to compute the elapsed time*/
      auto t_elapsed = getElapsed();

      PERFORMANCE_PRINTF_FUNC(m_str, t_elapsed);
    }

  ApexPerformanceTimer(const ApexPerformanceTimer&) = delete;
  ApexPerformanceTimer& operator=(const ApexPerformanceTimer&) = delete;

 private:
  const char *m_str;
  duration<double> t_start = high_resolution_clock::duration::zero();
  duration<double> t_elapsed = high_resolution_clock::duration::zero();
  duration<double> t_stop = high_resolution_clock::duration::zero();
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

