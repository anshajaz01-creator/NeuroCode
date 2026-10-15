#include <vector>
using namespace std;

bool existsDifference(const vector<int>& v, int d) {
    for (int i = 0; i < (int)v.size(); i++) {
        for (int j = 0; j < (int)v.size(); j++) {
            if (i != j && v[i] - v[j] == d) return true;
        }
    }
    return false;
}
