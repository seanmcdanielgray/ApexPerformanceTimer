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
  // returns a starting time point 
  time_point<std::chrono::high_resolution_clock> getStart() const{return t_start;}

  // returns a stopping time point 
  time_point<std::chrono::high_resolution_clock> getStop() const{return t_stop;}

  // gets elapsed time between two time_points 
  duration<double> getElapsed() const{return (t_stop - t_start);}
  
  void setStart(time_point<std::chrono::high_resolution_clock> start) {start = t_start;}
  void setStop(time_point<std::chrono::high_resolution_clock> stop) {stop = t_stop;}

  ApexPerformanceTimer(const char* strText)
    {
      auto time = high_resolution_clock::now();
      
      setStart(time);
    }
  
  ~ApexPerformanceTimer()
    {
      auto time = high_resolution_clock::now();
      
      /* I need something here to set the stop time */
      setStop(time);
      
      /* I need something here to compute the elapsed time*/
      auto t_elapsed = getElapsed();

      PERFORMANCE_PRINTF_FUNC(m_str, t_elapsed);
    }

  ApexPerformanceTimer(const ApexPerformanceTimer&) = delete;
  ApexPerformanceTimer& operator=(const ApexPerformanceTimer&) = delete;

 private:
  const char *m_str;
  time_point<std::chrono::high_resolution_clock> t_start;
  time_point<std::chrono::high_resolution_clock> t_stop;
  duration<double> t_elapsed = high_resolution_clock::duration::zero();
};

#define APEXPERFORMANCETIMER_FUNCSTART ApexPerformanceTimer (__FUNCTION__" : %f\n")
#define APEXPERFORMANCETIMER_SCOPED(str) ApexPerformanceTimer (str" : %f\n")
#define APEXPERFORMANCETIMER_START(str) { ApexPerformanceTimer (str" : %f\n")
#define APEXPERFORMANCETIMER_END }

#else

#define APEXPERFORMANCETIMER_FUNCSTART
#define APEXPERFORMANCETIMER_SCOPED
#define APEXPERFORMANCETIMER_START
#define APEXPERFORMANCETIMER_END

#endif // ENABLE_APEXPERFORMANCETIMER                                                                                                                                               

#endif // APEXPERFORMANCETIMER_H

