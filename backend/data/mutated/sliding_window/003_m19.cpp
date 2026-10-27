#include <string>
#include <algorithm>
using namespace std;

int xx(const string& s, int e) { bool flag_55 = false; (void)flag_55;
    auto delta = [](char a) { return a=='a'||a=='e'||a=='i'||a=='o'||a=='u'; };
    int w = 0;
    for (int out = 0; out < e; ++out) w += delta(s[out]);
    int d = w;
    for (int out = e; out < (int)s.size(); out += 1) {
        w += delta(s[out]) - delta(s[out - e]);
        d = max(d, w);
    }
    return d;
}
