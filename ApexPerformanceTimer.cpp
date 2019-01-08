#include "ApexPerformanceTimer.h"
#include <tuple>

#ifdef ENABLE_APEXPERFORMANCETIMER

std::vector<std::tuple<std::string, double, int>> ApexPerformanceTimer::s_data;

int ApexPerformanceTimer::s_indent = 0;

ApexPerformanceTimer::ApexPerformanceTimer(const char* strText, bool bShowImmediate) : m_str(strText), m_bShowImmediate(bShowImmediate)
{
  auto t_start = high_resolution_clock::now();

  if (!m_bShowImmediate)
    {
      m_id = s_data.size();
      s_data.push_back(std::make_tuple(m_str, 0.0, s_indent));
      s_indent++;
    }
}

ApexPerformanceTimer::~ApexPerformanceTimer()
{
  auto t_stop = high_resolution_clock::now();

  duration<double> t_elapsed = duration_cast<duration<double>>(t_stop - t_start);

  if (m_bShowImmediate)
    {
      PERFORMANCE_PRINTF_FUNC(m_str, t_elapsed);
    }
  else
    {
      std::get<1>(s_data[m_id]) = t_elapsed;
    }

  --s_indent;
}

void ApexPerformanceTimer::ReportAll()
{
  for (const auto &d : s_data)
    {
      int indents = std::get<2>(d);
      while (indents-- > 0) PERFORMANCE_PRINTF_FUNC("  ");
      PERFORMANCE_PRINTF_FUNC(std::get<0>(d).c_str(), std::get<1>(d));
    }
}

#endif // ENABLE_SIMPLEPERF
