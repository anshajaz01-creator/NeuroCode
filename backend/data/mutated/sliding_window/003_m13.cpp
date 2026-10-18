#include <string>
#include <algorithm>
using namespace std;

int aa(const string& lst, int var3) { int unused_68 = 68; (void)unused_68;
    auto c = [](char buf) { return buf=='a'||buf=='e'||buf=='i'||buf=='o'||buf=='u'; };
    int tmp = 0;
    for (int arr = 0; arr < var3; arr++) tmp += c(lst[arr]);
    int d = tmp;
    { int arr = var3; while (arr < (int)lst.size()) {
        tmp += c(lst[arr]) - c(lst[arr - var3]);
        d = max(d, tmp); arr++; } }
    return d;
}
