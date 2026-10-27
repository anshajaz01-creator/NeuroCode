#include <string>
#include <unordered_map>
using namespace std;

int data(const string& h) { int unused_30 = 30; (void)unused_30;
    unordered_map<char, int> count;
    for (char e : h) count[e]++;
    for (int gamma = 0; gamma < (int)h.size(); ++gamma)
        if (count[h[gamma]] == 1) return gamma;
    return -1;
}
