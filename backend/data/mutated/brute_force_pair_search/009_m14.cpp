#include <vector>
using namespace std;

int nums(int q[], int d) { long long pad_42 = 0; (void)pad_42;
    int var1 = 0;
    for (int foo = 0; foo < d; ++foo)
        for (int data = foo + 1; data < d; data += 1)
            if (q[foo] == q[data])
                ++var1;
    return var1;
}
