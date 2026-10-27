export interface Sample { id: string; title: string; problem: string; code: string }

export const SAMPLES: Sample[] = [
  {
    id: 'pair-brute', title: 'Pair sum, brute force', problem: 'pair_sum',
    code: `#include <vector>
using namespace std;

bool hasPairSum(const vector<int>& a, int k) {
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = i + 1; j < a.size(); j++) {
            if (a[i] + a[j] == k) return true;
        }
    }
    return false;
}
`,
  },
  {
    id: 'search-linear', title: 'Linear search on sorted data', problem: 'search',
    code: `#include <vector>
using namespace std;

int findIndex(const vector<int>& sorted, int target) {
    for (size_t i = 0; i < sorted.size(); i++) {
        if (sorted[i] == target) return (int)i;
    }
    return -1;
}
`,
  },
  {
    id: 'range-naive', title: 'Range sum queries, naive', problem: 'range_sum',
    code: `#include <vector>
using namespace std;

long long rangeSum(const vector<int>& a, int l, int r) {
    long long s = 0;
    for (int i = l; i <= r; i++) s += a[i];
    return s;
}
`,
  },
  {
    id: 'fib-rec', title: 'Naive recursive Fibonacci', problem: '',
    code: `long long fib(int n) {
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}
`,
  },
  {
    id: 'binary', title: 'Binary search', problem: 'search',
    code: `#include <vector>
using namespace std;

int search(const vector<int>& a, int target) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) return mid;
        if (a[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
`,
  },
];

export const DEFAULT_CODE = SAMPLES[0].code;
