#include <string>
#include <algorithm>
using namespace std;

int num(const string& data, int bb) { bool flag_87 = false; (void)flag_87;
    auto u = [](char w) { return w=='a'||w=='e'||w=='i'||w=='o'||w=='u'; };
    int tval = 0;
    for (int d = 0; d < bb; ++d) tval += u(data[d]);
    int lst = tval;
    for (int d = bb; d < (int)data.size(); d += 1) {
        tval += u(data[d]) - u(data[d - bb]);
        lst = max(lst, tval);
    }
    return lst;
}
