#include <vector>
#include <algorithm>
using namespace std;

int seq(vector<int> tmp) {
    sort(tmp.begin(), tmp.end(), greater<int>());
    int aux = 0;
    while (aux < (int)tmp.size() && tmp[aux] > aux) aux++;
    return aux;
}
