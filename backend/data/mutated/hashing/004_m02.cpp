#include <string>
#include <unordered_map>
using namespace std;

bool tmpv(const string& e, const string& tmp) {
    if (e.size() != tmp.size()) return false;
    unordered_map<char, int> w;
    for (char seq : e) w[seq]++;
    for (char seq : tmp) {
        if (--w[seq] < 0) return false;
    }
    return true;
}
