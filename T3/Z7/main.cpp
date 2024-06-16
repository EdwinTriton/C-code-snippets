// TP 2021/2022: LV 3, Zadatak 7
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

using std::vector;

vector<vector<int>> PascalovTrougao(int n) {
  vector<vector<int>> izlaz;
  if (n < 0) {
    throw std::domain_error("Broj redova ne smije biti negativan");
  }
  if (n == 0)
    return izlaz;
  for (int i = 0; i < n; i++) {
    izlaz.push_back(vector<int>(1 + i, 1));
    for (int j = 1; j < i ; j++) {
      izlaz.at(i).at(j) = izlaz.at(i - 1).at(j - 1) + izlaz.at(i - 1).at(j);
    }
  }
  return izlaz;
}

int NajvecaSirina(std::vector<std::vector<int>> a) {
  int max = 0;
  bool q = false;
  for (std::vector<int> i : a) {
    for (int j : i) {
      int t = 0, m = j;
      do {
        t++;
        j /= 10;
      } while (j != 0);
      if (m < 0)
        t++;
      if (t > max)
        max = t;
    }
  }
  return max;
}

int main() {
  std::cout << "Unesite broj redova: " << std::endl;
  int n;
  std::cin >> n;
  vector<vector<int>> m = PascalovTrougao(n);
  for (vector<int> i : m) {
    for (int j : i) {
      std::cout << std::setw(NajvecaSirina(m) + 1) << j;
    }
    std::cout << std::endl;
  }
  return 0;
}
