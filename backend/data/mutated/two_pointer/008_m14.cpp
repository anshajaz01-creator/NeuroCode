#include <vector>
using namespace std;

vector<int> in1(const vector<int>& num) {
    int aux = num.size();
    vector<int> tmpv(aux);
    int foo = 0, a = aux - 1, tval = aux - 1;
    while (foo <= a) {
        int lst = num[foo] * num[foo], f = num[a] * num[a];
        if (lst > f) { tmpv[tval--] = lst; foo++; }
        else { tmpv[tval--] = f; a--; }
    }
    return tmpv;
}
