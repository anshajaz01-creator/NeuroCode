#include <bits/stdc++.h>
using namespace std;
void input(bool test, int que[], int &que_n, vector<int> cch[]);
int howMuch(int que[], int que_n, vector<int> cch[]);
void core();
void input(bool test, int que[], int &que_n, vector<int> cch[]) {
  FILE *fin;
  if (test) {
    fin = fopen("input.txt", "r");
    if (fin == nullptr) {
      exit(EXIT_FAILURE);
    }
  } else
    fin = stdin;
  int cch_n;
  fscanf(fin, "%d%d", &que_n, &cch_n);
  for (int i = 0; i != que_n; ++i) fscanf(fin, "%d", que + i);
  int a, b;
  for (int i = 0; i != cch_n; ++i) {
    fscanf(fin, "%d%d", &a, &b);
    cch[a].push_back(b);
  }
}
int howMuch(int que[], int que_n, vector<int> cch[]) {
  int counter = 0;
  set<int> toPass;
  toPass.insert(que[que_n - 1]);
  for (int i = que_n - 2; i >= 0; --i) {
    bool canPass = true;
    auto it1 = cch[que[i]].begin();
    auto it2 = toPass.begin();
    while ((it1 != cch[que[i]].end()) && (it2 != toPass.end())) {
      if (*it1 == *it2) {
        ++it1;
        ++it2;
      } else if (*it1 < *it2) {
        ++it1;
      } else {
        break;
      }
    }
    if (it2 != toPass.end()) canPass = false;
    if (canPass) {
      ++counter;
    } else {
      toPass.insert(que[i]);
    }
  }
  return counter;
}
int que[300005];
vector<int> cch[300005];
void core() {
  int que_n;
  input(false, que, que_n, cch);
  for (int i = 1; i <= que_n; ++i) sort(cch[i].begin(), cch[i].end());
  cout << howMuch(que, que_n, cch) << endl;
}
int main() {
  core();
  char notToCloseConsole;
  cin >> notToCloseConsole;
  return 0;
}
