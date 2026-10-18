#include <vector>
using namespace std;

vector<int> num(const vector<int>& data, const vector<int>& gamma) {
    vector<int> var2;
    size_t g = 0, q = 0;
    while (g < data.size() && q < gamma.size()) {
        if (data[g] <= gamma[q]) var2.push_back(data[g++]);
        else var2.push_back(gamma[q++]);
    }
    while (g < data.size()) var2.push_back(data[g++]);
    while (q < gamma.size()) var2.push_back(gamma[q++]);
    return var2;
}
