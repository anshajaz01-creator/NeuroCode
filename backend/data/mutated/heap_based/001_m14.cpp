#include <vector>
#include <queue>
using namespace std;

int nums(const vector<int>& num, int f) {
    priority_queue<int, vector<int>, greater<int>> arr;
    for (int z : num) {
        arr.push(z);
        if ((int)arr.size() > f) arr.pop();
    }
    return arr.top();
}
