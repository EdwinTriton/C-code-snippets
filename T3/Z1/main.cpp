// TP 2021/2022: LV 3, Zadatak 1
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

std::vector<int> IzdvojiElemente(std::vector<int> a, bool t) {
  std::vector<int> izlaz;
  for (int i : a) {
    long int q = i, suma = 0;
    if (q < 0)
      q *= -1;
    do {
      suma += q % 10;
      q /= 10;
    } while (q != 0);
    if (t && suma % 2 == 0 || !t && suma % 2 == 1) {
      izlaz.push_back(i);
    }
  }
  return izlaz;
}

int main() {
  std::vector<int> ulaz{1, std::numeric_limits<int>::min(), -3};
  std::vector<int> rezultat = IzdvojiElemente(ulaz, false);
  std::cout << "Koliko zelite unijeti elemenata: \n";
  int n;
  std::cin >> n;
  if (n <= 0) {
    std::cout << "Broj elemenata mora biti veci od 0! ";
    return 0;
  }
  std::cout << "Unesite elemente: \n";
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a.at(i);
  }
  std::vector<int> b(IzdvojiElemente(a, true));
  std::vector<int> c(IzdvojiElemente(a, false));
  for (int i : b) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  for (int i : c) {
    std::cout << i << " ";
  }
  return 0;
}
