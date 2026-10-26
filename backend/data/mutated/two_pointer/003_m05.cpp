#include <string>
using namespace std;

bool elem(const string& in2) {
    int in1 = 0, t = (int)in2.size() - 1;
    while (in1 < t) {
        if (in2[in1] != in2[t]) return false;
        ++in1; --t;
    }
    return true;
}
