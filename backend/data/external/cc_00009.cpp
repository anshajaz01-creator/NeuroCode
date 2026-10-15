#ifndef __APPLE__
#include <bits/stdc++.h>
#else
#include <iostream>
#include <cstring>
#include <algorithm>
#endif

using namespace std;

typedef long long ll;
const int N = 105;
const int M = 1e9 + 7;
int n, c[N], b[N], q, x, bp[N], bpp[N];
ll dp[N][N * N], sdp[N][N * N], cp[N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> c[i];
        cp[i] = cp[i - 1] + c[i];
    }

    for (int i = 1; i <= n - 1; i++)
    {
        cin >> b[i];
        bp[i] = bp[i - 1] + b[i];
        bpp[i] = bpp[i - 1] + bp[i];
    }
    cin >> q;
    while (q--)
    {
        cin >> x;
        memset(dp, 0, sizeof(dp));
        memset(sdp, 0, sizeof(sdp));
        for (int i = 0; i < N; i++) sdp[0][i] = 1;
        for (int i = 1; i <= n; i++)
        {
            int minj = max(0, i * x + bpp[i - 1]);
            for (int j = minj; j <= cp[i]; j++)
            {
                sdp[i][j] = sdp[i][j] + sdp[i-1][min((int)cp[i-1], j)];
                if (j > c[i])
                    sdp[i][j] = (sdp[i][j] - sdp[i-1][j-c[i]-1]+M) % M;
            }
            for (int j = 1; j <= cp[i]; j++) {
                sdp[i][j] += sdp[i][j-1] + M;
                sdp[i][j] %= M;
            }
        }

        cout << sdp[n][cp[n]] << endl;
    }
    return 0;
}