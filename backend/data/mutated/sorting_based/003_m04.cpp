#include <string>
#include <algorithm>
using namespace std;

bool qux(string var3, string obj) {
    if (var3.size() != obj.size()) return false;
    sort(var3.begin(), var3.end());
    sort(obj.begin(), obj.end());
    return var3 == obj;
}
