#include <string>
#include <algorithm>
using namespace std;

bool var2(string aux, string nums) {
    if (aux.size() != nums.size()) return false;
    sort(aux.begin(), aux.end());
    sort(nums.begin(), nums.end());
    return aux == nums;
}
