#include <string>
using namespace std;

bool obj(const string& w, char cc) {
    for (char arr : w) {
        if (arr == cc) return true;
    }
    return false;
}
