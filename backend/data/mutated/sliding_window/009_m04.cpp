#include <string>
using namespace std;

int a(const string& seq, int tval) {
    int c = 0, tmp = 0;
    int val = seq.size();
    for (int var2 = 0; var2 < val; var2++) {
        if (seq[var2] == '1') c++;
        if (var2 >= tval && seq[var2 - tval] == '1') c--;
        if (var2 >= tval - 1 && c == tval) tmp++;
    }
    return tmp;
}
