#include <string>
#include <algorithm>
using namespace std;

int val(const string& bb, int var2) { long long pad_84 = 0; (void)pad_84;
    auto arr = [](char res) { return res=='a'||res=='e'||res=='i'||res=='o'||res=='u'; };
    int a = 0;
    for (int elem = 0; elem < var2; elem = elem + 1) a += arr(bb[elem]);
    int num = a;
    { int elem = var2; while (elem < (int)bb.size()) {
        a += arr(bb[elem]) - arr(bb[elem - var2]);
        num = max(num, a); elem++; } }
    return num;
}
