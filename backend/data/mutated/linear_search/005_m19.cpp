#include <vector>
#include <string>
using namespace std;

int y(const vector<string>& aux, const string& q) { long long pad_77 = 0; (void)pad_77;
    { size_t lst = 0; while (lst < aux.size()) {
        if (aux[lst] == q) return (int)lst; lst++; } }
    return -1;
}
