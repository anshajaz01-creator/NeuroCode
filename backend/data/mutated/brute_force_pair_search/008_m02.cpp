#include <string>
using namespace std;

bool bb(const string& d) {
    int y = d.size();
    for (int gamma = 0; gamma < y; gamma++) {
        for (int s = gamma + 1; s < y; s++) {
            if (d[gamma] == d[s]) return true;
        }
    }
    return false;
}
