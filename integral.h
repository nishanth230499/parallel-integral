#include "parallel.h"
#include <atomic>

using namespace parlay;

// template <class Func>
// double integral(const Func& f, size_t n, double low, double high) {
//   double ans = 0;
//   // std::atomic<double> ans = 0;
//   size_t p = 100000;
//   double temp_sum[p];
//   parallel_for(0, p, [&](size_t i) {
//     temp_sum[i] = 0;
//     for(size_t j = i * n / p; j < (i+1) * n / p; j++) {
//       double x = low + (high - low) * j / n;
//       double dx = (high - low) / n;
//       double fxdx = f(x) * dx;
//       temp_sum[i] += fxdx;
//     }
//   });
//   for(size_t i=0; i<p; i++) {
//     ans += temp_sum[i];
//   }
//   return ans;
// }


template <class Func>
double integral(const Func& f, size_t n, double low, double high) {
  // printf("%ld\n", n);
  double dx = (high - low) / n;
  if (n < 100000) {
    double seq_sum = 0;
    for(size_t i = 0; i < n; i++) {
      double x = low + dx * i;
      double fxdx = f(x) * dx;
      seq_sum += fxdx;
    }
    return seq_sum;
  } else {
    double v1, v2;
    size_t halfn = n / 2;
    double midx = low + dx * halfn;
    // printf("%f, %f, %ld\n", low, high, n);
    auto f1 = [&]() { v1 = integral(f, halfn, low, midx); };
    auto f2 = [&]() { v2 = integral(f, n - halfn, midx, high); };
    par_do(f1, f2);
    return v1 + v2;
  }
}