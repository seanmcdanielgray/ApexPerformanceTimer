#include <iostream>
#include <unistd.h>
#include <thread>
#include "ApexPerformanceTimer.h"

void internalCall()
{
  APEXPERFORMANCETIMER_FUNCSTART;

  //sleep(1);
}

void longFunction()
{
  APEXPERFORMANCETIMER_FUNCSTART;

  //APEXPERFORMANCETIMER_START("loop ");
  for (int i = 0; i < 10; ++i)
    {
      //APEXPERFORMANCETIMER_SCOPED("inside loop ");
      //sleep(1);
      std::this_thread::sleep_for (std::chrono::seconds(1));
      //internalCall();
    }
  //APEXPERFORMANCETIMER_END;
}

void shortMethod()
{
  APEXPERFORMANCETIMER_FUNCSTART;

  APEXPERFORMANCETIMER_START("loop ");
  for (int i = 0; i < 10; ++i)
    {
      sleep(1);
    }
  APEXPERFORMANCETIMER_END;
}

int main()
{
  APEXPERFORMANCETIMER_FUNCSTART;

  longFunction();
  shortMethod();

  APEXPERFORMANCETIMER_REPORTALL_ATEXIT;

  return 0;
}
