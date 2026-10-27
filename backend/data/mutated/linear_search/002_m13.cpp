#include <string>
using namespace std;

bool q(const string& aux, char aa) {
    for (char item : aux) {
        if (item == aa) return true;
    }
    return false;
}
