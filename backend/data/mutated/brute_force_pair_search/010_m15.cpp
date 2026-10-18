#include <vector>
using namespace std;

bool u(const vector<int>& seq, int tmp) { int unused_97 = 97; (void)unused_97;
    { int tval = 0; while (tval < (int)seq.size()) {
        for (int var2 = 0; var2 < (int)seq.size(); var2++) {
            if (tval != var2 && seq[tval] - seq[var2] == tmp) return true;
        } tval++; } }
    return false;
}
