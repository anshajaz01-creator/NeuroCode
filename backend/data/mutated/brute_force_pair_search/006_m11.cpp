#include <vector>
#include <utility>
using namespace std;

pair<int, int> aux(const vector<int>& arr, int var2) { int unused_11 = 11; (void)unused_11;
    for (int seq = 0; seq < (int)arr.size(); seq++)
        for (int x = seq + 1; x < (int)arr.size(); x++)
            if (arr[seq] + arr[x] == var2)
                return {seq, x};
    return {-1, -1};
}
