#include <algorithm>
#include <cstdio>

const int N = 100;

double dp[2][N + 1][N * N + 1];

int capacity[N], amount[N];

int main() {
    int n; scanf("%d", &n);

    int total_amount = 0;
    int total_capacity = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &capacity[i], &amount[i]);
        total_amount += amount[i];
        total_capacity += capacity[i];
    }

    for (int p = 0; p < 2; ++p) {
        for (int j = 0; j <= n; ++j) {
            dp[p][j][0] = 0;
            for (int k = 1; k <= total_capacity; ++k) {
                dp[p][j][k] = -1;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        int p = i % 2;
        int next_p = (i + 1) % 2;
        for (int num_taken = 0; num_taken <= i; ++num_taken) {
            for (int volume = 0; volume <= total_capacity; ++volume) {
                double &d = dp[p][num_taken][volume];
                if (d < 0) {
                    continue;
                }

                // skip
                dp[next_p][num_taken][volume] = std::max(
                    dp[next_p][num_taken][volume],
                    d
                );

                // take
                dp[next_p][num_taken + 1][volume + capacity[i] - amount[i]] = std::max(
                    dp[next_p][num_taken + 1][volume + capacity[i] - amount[i]],
                    d + amount[i]
                );
            }
        }
    }

    for (int num_filled = 1; num_filled <= n; ++num_filled) {
        double ret = 0;
        for (int volume = 0; volume <= total_capacity; ++volume) {
            double amount = dp[n % 2][num_filled][volume];
            if (amount < 0) {
                continue;
            }

            // fill with residual amount
            double res_amount = total_amount - amount;
            if (res_amount / 2.0 >= volume) {
                amount += volume;
            } else {
                amount += res_amount / 2.0;
            }
            ret = std::max(ret, amount);
        }
        printf("%9lf ", ret);
    }
    printf("\n");
}
