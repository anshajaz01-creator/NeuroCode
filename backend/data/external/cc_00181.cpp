#include <bits/stdc++.h>
using namespace std;
int main() {
  double k, d, t;
  scanf("%lf%lf%lf", &k, &d, &t);
  double total_time;
  if (d >= k) {
    if (t > k + (d - k) * 0.5) {
      long long mult = t / (k + (d - k) * 0.5);
      double rem = t - mult * (k + (d - k) * 0.5);
      if (rem > k) {
        total_time = mult * d + k + (rem - k) * 2;
      } else {
        total_time = mult * d + rem;
      }
    } else {
      if (t > k) {
        total_time = k + 2 * (t - k);
      } else {
        total_time = t;
      }
    }
  } else {
    long long r;
    long long k_temp = (long long)k;
    long long d_temp = (long long)d;
    if (k_temp % d_temp == 0) {
      r = k_temp / d_temp;
    } else {
      r = k_temp / d_temp + 1;
    }
    double l = r * d - k;
    if (t > k + l * 0.5) {
      long long mult = t / (k + l * 0.5);
      double rem = t - mult * (k + l * 0.5);
      if (rem > k) {
        total_time = mult * (k + l) + k + (rem - k) * 2;
      } else {
        total_time = mult * (k + l) + rem;
      }
    } else {
      if (t > k) {
        total_time = k + 2 * (t - k);
      } else {
        total_time = t;
      }
    }
  }
  printf("%lf", total_time);
  return 0;
}
