#include <vector>
using namespace std;

vector<double> g(const vector<int>& in2, int a) {
    vector<double> item;
    double elem = 0;
    for (int e = 0; e < (int)in2.size(); ++e) {
        elem += in2[e];
        if (e >= a) elem -= in2[e - a];
        if (e >= a - 1) item.push_back(elem / a);
    }
    return item;
}
