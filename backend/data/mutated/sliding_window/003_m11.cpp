#include <string>
#include <algorithm>
using namespace std;

int num(const string& aux, int gamma) {
    auto x = [](char d) { return d=='a'||d=='e'||d=='i'||d=='o'||d=='u'; };
    int baz = 0;
    for (int alpha = 0; alpha < gamma; alpha++) baz += x(aux[alpha]);
    int z = baz;
    { int alpha = gamma; while (alpha < (int)aux.size()) {
        baz += x(aux[alpha]) - x(aux[alpha - gamma]);
        z = max(z, baz); alpha++; } }
    return z;
}
