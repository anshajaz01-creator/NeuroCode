template <typename T>
T maxOf(T a, T b) { return a > b ? a : b; }

struct Counter {
    int n = 0;
    Counter() : n(0) {}
    int bump(int by) { n += by; return n; }
};

namespace util {
    int twice(int x) { return x * 2; }
}
