/* Author: Sean L. McDaniel-Gray
 *
 * The goal of this tool is to find hotspots all withouth using
 * advanced frameworks or tools.
 *
 * If you need to check the execution time of some code/system
 * just include a header ( and the cpp file) and use the
 * APEXPERFORMANCETIMER_FUNCSTART or APEXPERFORMANCETIMER_FUNCSTART(str)/END
 * in the analyzed placed
 */

#include <iostream>
#include <tuple>
#include <thread>
#include "ApexPerformanceTimer.h"

#ifdef ENABLE_APEXPERFORMANCE

vector<tuple<string, duration<double>, int>> ApexPerformanceTimer::s_data;

int ApexPerformanceTimer::s_indent = 0;

duration<double> dummy_zero = high_resolution_clock::duration::zero();

// The constructor adds a new entry into the static vector
ApexPerformanceTimer::ApexPerformanceTimer(const char* strText, bool bShowImmediate) : m_str(strText), m_bShowImmediate(bShowImmediate)
{
  // Takes the start time when the timer is first constructor
  t_start = high_resolution_clock::now();

  // If showImmediate is false add data to the vector
  if (!m_bShowImmediate)
    {
      m_id = s_data.size();

      // adds new element to the end of the vector
      s_data.push_back(std::make_tuple(m_str, dummy_zero, s_indent));

      s_indent++;
    }
}

// The destructor
ApexPerformanceTimer::~ApexPerformanceTimer()
{

  // Takes the ending time of the timer
  t_stop = high_resolution_clock::now();

  // Computes the elapsed time using the start and end time
  t_elapsed = duration_cast<duration<double>>(t_stop - t_start);

  // If showImmediate is true will print out the data immediately
  if (m_bShowImmediate)
    {
      PERFORMANCE_PRINTF_FUNC(m_str, t_elapsed);
    }
  else
    {
      get<1>(s_data[m_id]) = t_elapsed;
    }

  --s_indent;
}

// Show the current data
void ApexPerformanceTimer::ReportAll()
{
  for (const auto &d : s_data)
    {
      int indents = get<2>(d);

      while (indents-- > 0)
	PERFORMANCE_PRINTF_FUNC("  ");

      PERFORMANCE_PRINTF_FUNC(get<0>(d).c_str(), ((get<1>(d)).count()));
    }
}

#endif // ENABLE_SIMPLEPERF
