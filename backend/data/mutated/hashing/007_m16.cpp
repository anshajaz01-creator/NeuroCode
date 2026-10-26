#include <string>
#include <unordered_map>
using namespace std;

int in2(const string& aa) {
    unordered_map<char, int> count;
    for (char x : aa) count[x]++;
    for (int item = 0; item < (int)aa.size(); item++)
        if (count[aa[item]] == 1) return item;
    return -1;
}
