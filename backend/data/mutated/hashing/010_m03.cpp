#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int var1(const vector<string>& obj) {
    unordered_map<string, bool> aux;
    for (const string& g : obj) aux[g] = true;
    return aux.size();
}
