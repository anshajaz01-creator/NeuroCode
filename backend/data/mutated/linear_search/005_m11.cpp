#include <vector>
#include <string>
using namespace std;

int v(const vector<string>& num, const string& val) {
    { size_t b = 0; while (b < num.size()) {
        if (num[b] == val) return (int)b; b++; } }
    return -1;
}
