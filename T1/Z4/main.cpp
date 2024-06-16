// TP 2016/2017: LV 1, Zadatak 4
#include <cmath>
#include <iostream>

int main() {
  using namespace std;
  double k = 1;
  int n = 1;
  while (1) {
      cout << "Unesite prirodan broj ili 0 za kraj: ";
      cin >> k;
      
    if (k < 0 || !cin || k != int(k)) {
      cout << "Niste unijeli prirodan broj!" << endl;
      cin.clear();
      cin.ignore(10000, '\n');
      continue;
    }
    if (k==0) break;
    n = k;
    int s = 0;
    for (int i = 1; i < n; i++) {
      if (n % i == 0) {
        s += i;
      }
    }
    if (s == n) {
      cout << "Broj " << s << " je savrsen!" << endl;
    } else if (s < n) {
      cout << "Broj " << n << " je manjkav!" << endl;
    } else if (s > n) {
      cout << "Broj " << n << " je obilan!" << endl;
    }
  }
  cout << "Dovidjenja!";
  return 0;
}