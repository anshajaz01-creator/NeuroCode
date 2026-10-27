#include <bits/stdc++.h>
using namespace std;
void RD(int &x) { scanf("%d", &x); }
void RD(long long &x) { scanf("%I64d", &x); }
void RD(unsigned long long &x) { scanf("%I64u", &x); }
void RD(unsigned int &x) { scanf("%u", &x); }
void RD(double &x) { scanf("%lf", &x); }
void RD(int &x, int &y) { scanf("%d%d", &x, &y); }
void RD(unsigned int &x, unsigned int &y) { scanf("%u%u", &x, &y); }
void RD(double &x, double &y) { scanf("%lf%lf", &x, &y); }
void RD(double &x, double &y, double &z) { scanf("%lf%lf%lf", &x, &y, &z); }
void RD(int &x, int &y, int &z) { scanf("%d%d%d", &x, &y, &z); }
void RD(unsigned int &x, unsigned int &y, unsigned int &z) {
  scanf("%u%u%u", &x, &y, &z);
}
void RD(char &x) { x = getchar(); }
void RD(char *s) { scanf("%s", s); }
void RD(string &s) { cin >> s; }
void PR(int x) { printf("%d\n", x); }
void PR(int x, int y) { printf("%d %d\n", x, y); }
void PR(long long x) { printf("%I64d\n", x); }
void PR(unsigned int x) { printf("%u\n", x); }
void PR(double x) { printf("%.10lf\n", x); }
void PR(double x, double y) { printf("%.5lf %.5lf\n", x, y); }
void PR(char x) { printf("%c\n", x); }
void PR(char *x) { printf("%s\n", x); }
void PR(string x) { cout << x << endl; }
void upMin(int &x, int y) {
  if (x > y) x = y;
}
void upMin(long long &x, long long y) {
  if (x > y) x = y;
}
void upMin(double &x, double y) {
  if (x > y) x = y;
}
void upMax(int &x, int y) {
  if (x < y) x = y;
}
void upMax(long long &x, long long y) {
  if (x < y) x = y;
}
void upMax(double &x, double y) {
  if (x < y) x = y;
}
const long long inf = ((long long)1) << 60;
const double dinf = 1e10;
const int INF = 100000000;
const int N = 100005;
int n, m, a[N], b[N], f[N];
int main() {
  while (scanf("%d", &n) != -1) {
    RD(m);
    int i;
    for (i = 1; i <= n; i++) RD(a[i]);
    for (i = 1; i <= n; i++) RD(b[i]), b[i] = a[i] - m * b[i];
    int j, k, t;
    for (i = 0; i < N; i++) f[i] = -INF;
    int p = N - 1, L = 50000;
    for (i = 1; i <= n; i++) {
      if (b[i] >= 0) {
        for (j = p; j >= b[i]; j--) upMax(f[j], f[j - b[i]] + a[i]);
        upMax(f[b[i] + L], a[i]);
      } else {
        b[i] = -b[i];
        for (j = 0; j + b[i] <= p; j++) upMax(f[j], f[j + b[i]] + a[i]);
        upMax(f[-b[i] + L], a[i]);
      }
    }
    if (f[L] >= 0)
      PR(f[L]);
    else
      PR(-1);
  }
}
