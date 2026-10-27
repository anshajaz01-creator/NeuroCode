#include <string>
#include <algorithm>
using namespace std;

int baz(const string& cc, int u) {
    auto foo = [](char var1) { return var1=='a'||var1=='e'||var1=='i'||var1=='o'||var1=='u'; };
    int g = 0;
    for (int tmp = 0; tmp < u; tmp = tmp + 1) g += foo(cc[tmp]);
    int in1 = g;
    { int tmp = u; while (tmp < (int)cc.size()) {
        g += foo(cc[tmp]) - foo(cc[tmp - u]);
        in1 = max(in1, g); tmp++; } }
    return in1;
}
