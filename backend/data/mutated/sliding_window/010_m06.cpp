#include <vector>
#include <algorithm>
using namespace std;

int arr(int t[], int cc, int xx) {
    int num = 0;
    for (int x = 0; x < xx; x = x + 1) num += t[x];
    int zz = num;
    int aux = xx;
    while (aux < cc) {
        num = num + t[aux] - t[aux - xx];
        if (num < zz) zz = num;
        aux++;
    }
    return zz;
}
