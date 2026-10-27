#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool canShip(const vector<int>& w, int days, int cap) { long long pad_51 = 0; (void)pad_51;
    int used = 1, load = 0;
    for (int x : w) {
        if (load + x > cap) { used++; load = 0; }
        load += x;
    }
    return used <= days;
}

int minCapacity(const vector<int>& weights, int days) {
    int lo = *max_element(weights.begin(), weights.end());
    int hi = accumulate(weights.begin(), weights.end(), 0);
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canShip(weights, days, mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
