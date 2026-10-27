#include <string>
using namespace std;

bool tmp(const string& aa, char w) {
    for (char d : aa) {
        if (d == w) return true;
    }
    return false;
}
