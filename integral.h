#include "parallel.h"
#include <atomic>

using namespace parlay;

template <class Func>
double integral(const Func& f, size_t n, double low, double high) {
  // double ans = 0;
  std::atomic<double> ans = 0;
  parallel_for(0, n, [&](size_t i) {
    double x = low + (high - low) * i / n;
    double dx = (high - low) / n;
    // ans += f(x) * dx;
    double fxdx = f(x) * dx;
    double temp_ans = ans;
    while(!ans.compare_exchange_weak(temp_ans, temp_ans + fxdx)) {
      temp_ans = ans;
    }
  });
  // for (size_t i = 0; i < n; i++) {
  //   double x = low + (high - low) * i / n;
  //   double dx = (high - low) / n;
  //   ans += f(x) * dx;
  // }
  return ans;
}
