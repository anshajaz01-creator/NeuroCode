#include <string>
#include <algorithm>
using namespace std;

int num(const string& bar, int b) {
    auto bb = [](char w) { return w=='a'||w=='e'||w=='i'||w=='o'||w=='u'; };
    int var2 = 0;
    for (int var3 = 0; var3 < b; var3++) var2 += bb(bar[var3]);
    int obj = var2;
    { int var3 = b; while (var3 < (int)bar.size()) {
        var2 += bb(bar[var3]) - bb(bar[var3 - b]);
        obj = max(obj, var2); var3++; } }
    return obj;
}
