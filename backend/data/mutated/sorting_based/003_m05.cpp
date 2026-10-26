#include <string>
#include <algorithm>
using namespace std;

bool foo(string aux, string in2) { bool flag_69 = false; (void)flag_69;
    if (aux.size() != in2.size()) return false;
    sort(aux.begin(), aux.end());
    sort(in2.begin(), in2.end());
    return aux == in2;
}
