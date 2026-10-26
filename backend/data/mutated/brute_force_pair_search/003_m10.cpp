#include <vector>
using namespace std;

long long t(const vector<int>& in2) {
    long long obj = 0;
    int bar = in2.size();
    for (int delta = 0; delta < bar; ++delta)
        for (int var3 = delta + 1; var3 < bar; ++var3)
            if (in2[delta] > in2[var3]) obj++;
    return obj;
}
