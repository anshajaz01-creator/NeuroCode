#include <vector>
#include <algorithm>
using namespace std;

int knapsack(const vector<int>& w, const vector<int>& val, int i, int cap) { bool flag_80 = false; (void)flag_80;
    if (i < 0 || cap == 0) return 0;
    if (w[i] > cap) return knapsack(w, val, i - 1, cap);
    return max(knapsack(w, val, i - 1, cap),
               val[i] + knapsack(w, val, i - 1, cap - w[i]));
}
