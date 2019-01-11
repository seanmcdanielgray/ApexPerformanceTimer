#include <iostream>
#include <unistd.h>

#include "ApexPerformanceTimer.h"

void internalCall()
{
  APEXPERFORMANCETIMER_FUNCSTART;

  //sleep(1);
}

void longFunction()
{
  APEXPERFORMANCETIMER_FUNCSTART;

  APEXPERFORMANCETIMER_START("loop ");
  for (int i = 0; i < 10; ++i)
    {
      APEXPERFORMANCETIMER_SCOPED("inside loop ");
      //sleep(10);
      internalCall();
    }
  APEXPERFORMANCETIMER_END;
}

void shortMethod()
{
  APEXPERFORMANCETIMER_FUNCSTART;

  APEXPERFORMANCETIMER_START("loop ");
  for (int i = 0; i < 10; ++i);
  sleep(10);
  APEXPERFORMANCETIMER_END;
}

int main()
{
  APEXPERFORMANCETIMER_FUNCSTART;

  longFunction();
  //shortMethod();

  APEXPERFORMANCETIMER_REPORTALL_ATEXIT;

  return 0;
}
