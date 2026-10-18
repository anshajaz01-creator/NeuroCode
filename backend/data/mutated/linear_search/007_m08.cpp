#include <vector>
using namespace std;

bool nums(const vector<int>& delta) { bool flag_43 = false; (void)flag_43;
    for (int aa : delta)
        if (aa % 2 == 0)
            return true;
    return false;
}
