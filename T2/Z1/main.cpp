// TP 2020/2021: Tutorijal 2, Zadatak 1
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

bool DaLiJeProst(int a) {
  bool t = true;
  if (a <= 1)
    return false;
  int q = sqrtf(a) + 1;
  for (int i = 2; i < q; i++) {
    if (a % i == 0) {
      t = false;
      break;
    }
  }
  return t;
}

std::vector<int> ProstiBrojeviUOpsegu(int a, int b) {
  std::vector<int> rezultat;
  bool t;
  for (int i = a; i <= b; i++) {
    if (DaLiJeProst(i)) {
      rezultat.push_back(i);
    }
    if (i==b) break; 
  }
  return rezultat;
}

int main() {
std::cout << "Unesite pocetnu i krajnju vrijednost: " << std::endl;
int a, b;
std::cin >> a >> b;
auto vec = ProstiBrojeviUOpsegu(a, b);
if (!vec.size()) {
    std::cout<<"Nema prostih brojeva u rasponu od "<<a<<" do "<<b<<"!";
    return 0;
}
std::cout << "Prosti brojevi u rasponu od " << a << " do " << b << " su: ";
for (int i = 0; i < vec.size() - 1; i++) {
  std::cout << " " << vec[i] << ",";
}
std::cout << " " << vec[vec.size() - 1] << std::endl;
  return 0;
}
