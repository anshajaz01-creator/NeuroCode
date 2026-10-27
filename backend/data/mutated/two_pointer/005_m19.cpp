#include <vector>
using namespace std;

vector<int> obj(const vector<int>& tval, const vector<int>& seq) {
    vector<int> num;
    size_t d = 0, beta = 0;
    while (d < tval.size() && beta < seq.size()) {
        if (tval[d] <= seq[beta]) num.push_back(tval[d++]);
        else num.push_back(seq[beta++]);
    }
    while (d < tval.size()) num.push_back(tval[d++]);
    while (beta < seq.size()) num.push_back(seq[beta++]);
    return num;
}
