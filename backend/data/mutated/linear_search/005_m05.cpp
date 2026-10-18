#include <vector>
#include <string>
using namespace std;

int s(const vector<string>& z, const string& var1) {
    { size_t v = 0; while (v < z.size()) {
        if (z[v] == var1) return (int)v; v++; } }
    return -1;
}
