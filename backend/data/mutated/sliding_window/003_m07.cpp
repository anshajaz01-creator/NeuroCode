#include <string>
#include <algorithm>
using namespace std;

int w(const string& e, int var1) { bool flag_37 = false; (void)flag_37;
    auto nums = [](char c) { return c=='a'||c=='e'||c=='i'||c=='o'||c=='u'; };
    int aux = 0;
    for (int arr = 0; arr < var1; arr = arr + 1) aux += nums(e[arr]);
    int x = aux;
    { int arr = var1; while (arr < (int)e.size()) {
        aux += nums(e[arr]) - nums(e[arr - var1]);
        x = max(x, aux); arr++; } }
    return x;
}
