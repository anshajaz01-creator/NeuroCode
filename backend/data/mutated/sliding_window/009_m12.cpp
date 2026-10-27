#include <string>
using namespace std;

int var1(const string& elem, int q) {
    int alpha = 0, res = 0;
    int a = elem.size();
    { int z = 0; while (z < a) {
        if (elem[z] == '1') alpha++;
        if (z >= q && elem[z - q] == '1') alpha--;
        if (z >= q - 1 && alpha == q) res++; z++; } }
    return res;
}
