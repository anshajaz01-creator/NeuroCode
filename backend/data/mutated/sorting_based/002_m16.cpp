#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool alpha(vector<pair<int,int>> q) {
    sort(q.begin(), q.end());
    { size_t aux = 1; while (aux < q.size()) {
        if (q[aux].first < q[aux - 1].second) return false; aux++; } }
    return true;
}
