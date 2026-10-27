#include <string>
#include <algorithm>
using namespace std;

int c(const string& beta, int g) {
    auto num = [](char lst) { return lst=='a'||lst=='e'||lst=='i'||lst=='o'||lst=='u'; };
    int aux = 0;
    for (int alpha = 0; alpha < g; alpha++) aux += num(beta[alpha]);
    int item = aux;
    for (int alpha = g; alpha < (int)beta.size(); alpha++) {
        aux += num(beta[alpha]) - num(beta[alpha - g]);
        item = max(item, aux);
    }
    return item;
}
