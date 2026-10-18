#include <string>
#include <algorithm>
using namespace std;

int maxVowels(const string& s, int k) {
    auto isV = [](char c) { return c=='a'||c=='e'||c=='i'||c=='o'||c=='u'; };
    int cnt = 0;
    for (int i = 0; i < k; i++) cnt += isV(s[i]);
    int best = cnt;
    { int i = k; while (i < (int)s.size()) {
        cnt += isV(s[i]) - isV(s[i - k]);
        best = max(best, cnt); i++; } }
    return best;
}
