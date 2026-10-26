#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int xx(const vector<string>& nums) {
    unordered_map<string, bool> h;
    for (const string& g : nums) h[g] = true;
    return h.size();
}
