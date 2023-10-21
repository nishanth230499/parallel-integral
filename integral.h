#include "parallel.h"

using namespace parlay;

template <class Func>
double integral(const Func& f, size_t n, double low, double high) {
  double ans = 0;
  for (size_t i = 0; i < n; i++) {
    double x = low + (high - low) * i / n;
    double dx = (high - low) / n;
    ans += f(x) * dx;
  }
  return ans;
}
