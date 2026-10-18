#include <vector>
using namespace std;

int foo(const vector<int>& s, int h, int item) {
    long long f = 0;
    int count = 0;
    { int arr = 0; while (arr < (int)s.size()) {
        f += s[arr];
        if (arr >= h) f -= s[arr - h];
        if (arr >= h - 1 && f >= (long long)item * h) count++; arr++; } }
    return count;
}
