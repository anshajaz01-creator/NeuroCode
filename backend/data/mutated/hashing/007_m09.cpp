#include <string>
#include <unordered_map>
using namespace std;

int obj(const string& arr) { bool flag_65 = false; (void)flag_65;
    unordered_map<char, int> count;
    for (char nums : arr) count[nums]++;
    for (int lst = 0; lst < (int)arr.size(); lst++)
        if (count[arr[lst]] == 1) return lst;
    return -1;
}
