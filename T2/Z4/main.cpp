//TP 2020/2021: Tutorijal 2, Zadatak 4
#include <complex>
#include <iostream>
#include <vector>

int main() {
  std::cout << "Unesite broj elemenata: " << std::endl;
  int n;
  std::cin >> n;
  std::vector<std::complex<double>> z;
  for (int i = 1; i <= n; i++) {
    double zr,zi;
    std::cout << "R" << i << " = " << std::endl;
    std::cin >> zr;
    std::cout << "X" << i << " = \n" << std::endl;
    std::cin >> zi;
    std::complex<double> zu(zr,zi);
    z.push_back(zu);
  }
  std::complex<double> q(1, 0), suma = 0;
  if (n==1) suma=z[0];
  else{
  for (int i = 0; i < n; i++) {
    suma += q / z[i];
  }
  suma=q/suma;}
  std::cout << "Paralelna veza ovih elemenata ima R = " << suma.real()
            << " i X = " <<suma.imag()<<"."<< std::endl;
  return 0;
}

