#include <string>
#include <algorithm>
using namespace std;

int tval(const string& e, int tmp) { bool flag_33 = false; (void)flag_33;
    auto g = [](char bar) { return bar=='a'||bar=='e'||bar=='i'||bar=='o'||bar=='u'; };
    int nums = 0;
    for (int in1 = 0; in1 < tmp; in1 += 1) nums += g(e[in1]);
    int foo = nums;
    { int in1 = tmp; while (in1 < (int)e.size()) {
        nums += g(e[in1]) - g(e[in1 - tmp]);
        foo = max(foo, nums); in1++; } }
    return foo;
}
