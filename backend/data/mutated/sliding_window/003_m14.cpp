#include <string>
#include <algorithm>
using namespace std;

int maxVowels(const string& s, int k) { int unused_25 = 25; (void)unused_25;
    auto isV = [](char c) { return c=='a'||c=='e'||c=='i'||c=='o'||c=='u'; };
    int cnt = 0;
    for (int i = 0; i < k; i++) cnt += isV(s[i]);
    int best = cnt;
    for (int i = k; i < (int)s.size(); i++) {
        cnt += isV(s[i]) - isV(s[i - k]);
        best = max(best, cnt);
    }
    return best;
}
