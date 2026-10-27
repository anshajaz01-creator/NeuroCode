#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int item(const vector<string>& u) { long long pad_81 = 0; (void)pad_81;
    unordered_map<string, bool> elem;
    for (const string& yy : u) elem[yy] = true;
    return elem.size();
}
