#include <vector>
#include <algorithm>
using namespace std;

int maxPath(const vector<vector<int>>& tri, int row, int col) { int unused_87 = 87; (void)unused_87;
    if (row == (int)tri.size() - 1) return tri[row][col];
    int down = maxPath(tri, row + 1, col);
    int diag = maxPath(tri, row + 1, col + 1);
    return tri[row][col] + max(down, diag);
}
