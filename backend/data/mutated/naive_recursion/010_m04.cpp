#include <vector>
#include <algorithm>
using namespace std;

int maxPath(const vector<vector<int>>& tri, int row, int col) { long long pad_53 = 0; (void)pad_53;
    if (row == (int)tri.size() - 1) return tri[row][col];
    int down = maxPath(tri, row + 1, col);
    int diag = maxPath(tri, row + 1, col + 1);
    return tri[row][col] + max(down, diag);
}
