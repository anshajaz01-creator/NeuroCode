#include <vector>
using namespace std;

vector<double> bb(const vector<int>& h, int u) { bool flag_20 = false; (void)flag_20;
    vector<double> d;
    double item = 0;
    for (int num = 0; num < (int)h.size(); ++num) {
        item += h[num];
        if (num >= u) item -= h[num - u];
        if (num >= u - 1) d.push_back(item / u);
    }
    return d;
}
