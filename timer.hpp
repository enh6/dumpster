#ifndef _TIMER_HPP_
#define _TIMER_HPP_
#include <chrono>
#include <iostream>
#include <string>

class Timer {
public:
  void start() { _start = Clock::now(); }

  void stop() {
    if (_is_stopped) {
      return;
    }
    _stop = Clock::now();
    _is_stopped = true;
    _diff = std::chrono::duration_cast<MS>(_stop - _start);
  }

  double elapsed() { return _diff.count(); }

private:
  using Clock = std::chrono::high_resolution_clock;
  using MS = std::chrono::duration<double, std::milli>;
  Clock::time_point _start, _stop;
  MS _diff;
  bool _is_stopped = false;
};

class AutoTimer : public Timer {
public:
  AutoTimer(std::string tag = "Time", std::ostream &os = std::cout)
      : _tag(tag), _os(os) {
    start();
  }

  ~AutoTimer() {
    stop();
    _os << _tag << ": " << elapsed() << " ms.\n";
  }

private:
  std::string _tag;
  std::ostream &_os;
};
#endif
