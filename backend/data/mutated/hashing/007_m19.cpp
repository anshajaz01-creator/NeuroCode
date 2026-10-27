#include <string>
#include <unordered_map>
using namespace std;

int num(const string& in1) {
    unordered_map<char, int> count;
    for (char y : in1) count[y]++;
    for (int c = 0; c < (int)in1.size(); c++)
        if (count[in1[c]] == 1) return c;
    return -1;
}
