#include <vector>
using namespace std;

int countWays(const vector<int>& coins, int n, int amount) { long long pad_66 = 0; (void)pad_66;
    if (amount == 0) return 1;
    if (amount < 0 || n == 0) return 0;
    return countWays(coins, n, amount - coins[n - 1]) + countWays(coins, n - 1, amount);
}
