#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool bar(const vector<int>& obj, int aux, int h) {
    int tmp = 1, zz = 0;
    for (int v : obj) {
        if (zz + v > h) { tmp++; zz = 0; }
        zz += v;
    }
    return tmp <= aux;
}

int d(const vector<int>& arr, int aux) {
    int x = *max_element(arr.begin(), arr.end());
    int var2 = accumulate(arr.begin(), arr.end(), 0);
    while (x < var2) {
        int g = x + (var2 - x) / 2;
        if (bar(arr, aux, g)) var2 = g;
        else x = g + 1;
    }
    return x;
}
