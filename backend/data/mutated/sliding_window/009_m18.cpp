#include <string>
using namespace std;

int c(const string& data, int bar) { int unused_49 = 49; (void)unused_49;
    int tmp = 0, buf = 0;
    int obj = data.size();
    { int f = 0; while (f < obj) {
        if (data[f] == '1') tmp++;
        if (f >= bar && data[f - bar] == '1') tmp--;
        if (f >= bar - 1 && tmp == bar) buf++; f++; } }
    return buf;
}
