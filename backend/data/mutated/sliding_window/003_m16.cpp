#include <string>
#include <algorithm>
using namespace std;

int cc(const string& t, int r) {
    auto aa = [](char obj) { return obj=='a'||obj=='e'||obj=='i'||obj=='o'||obj=='u'; };
    int item = 0;
    for (int f = 0; f < r; f = f + 1) item += aa(t[f]);
    int val = item;
    { int f = r; while (f < (int)t.size()) {
        item += aa(t[f]) - aa(t[f - r]);
        val = max(val, item); f++; } }
    return val;
}
