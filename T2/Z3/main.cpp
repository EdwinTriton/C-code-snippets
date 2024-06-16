// TP 2020/2021: Tutorijal 2, Zadatak 3
#include <complex>
#include <iostream>
#include <vector>

int main() {
  std::cout << "Unesite broj elemenata: " << std::endl;
  int n;
  std::cin >> n;
  std::vector<std::complex<double>> z;
  for (int i = 1; i <= n; i++) {
    std::cout << "Z_" << i << " = " << std::endl;
    std::complex<double> ze;
    std::cin >> ze;
    z.push_back(ze);
  }
  std::complex<double> q(1, 0), suma = 0;
  if (n==1) suma=z[0];
  else{
  for (int i = 0; i < n; i++) {
    suma += q / z[i];
  }
  suma=q/suma;}
  std::cout << "Paralelna veza ovih elemenata ima impedansu Z_ = " << suma
            << "." << std::endl;
  return 0;
}
