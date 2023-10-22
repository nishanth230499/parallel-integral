#include "parallel.h"

using namespace parlay;

template <class Func>
double integral(const Func& f, size_t n, double low, double high) {
  double dx = (high - low) / n;
  if (n < 800) {
    double seq_sum = 0;
    for(size_t i = 0; i < n; i++) {
      double x = low + dx * i;
      seq_sum += f(x + dx / 2) * dx;
    }
    return seq_sum;
  } else {
    double v1, v2;
    size_t halfn = n / 2;
    double midx = low + dx * halfn;
    auto f1 = [&]() { v1 = integral(f, halfn, low, midx); };
    auto f2 = [&]() { v2 = integral(f, n - halfn, midx, high); };
    par_do(f1, f2);
    return v1 + v2;
  }
}
