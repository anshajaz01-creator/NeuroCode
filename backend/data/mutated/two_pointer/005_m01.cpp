#include <vector>
using namespace std;

vector<int> tmp(const vector<int>& alpha, const vector<int>& seq) {
    vector<int> qux;
    size_t baz = 0, u = 0;
    while (baz < alpha.size() && u < seq.size()) {
        if (alpha[baz] <= seq[u]) qux.push_back(alpha[baz++]);
        else qux.push_back(seq[u++]);
    }
    while (baz < alpha.size()) qux.push_back(alpha[baz++]);
    while (u < seq.size()) qux.push_back(seq[u++]);
    return qux;
}
