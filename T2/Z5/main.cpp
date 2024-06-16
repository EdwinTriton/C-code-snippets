//TP 2020/2021: Tutorijal 2, Zadatak 5
#include <complex>
#include <iostream>
#include <vector>

int main() {
  std::cout << "Unesite broj elemenata: " << std::endl;
  int n;
  std::cin >> n;
  std::vector<std::complex<double>> z;
  for (int i = 1; i <= n; i++) {
    double za,zfi;
    std::cout << "Z" << i << " = " << std::endl;
    std::cin >> za;
    std::cout << "fi" << i << " = \n" << std::endl;
    std::cin >> zfi;
    zfi*=atan(1)*4/180;
    std::complex<double> zu(za*cos(zfi),(za*sin(zfi)));
    z.push_back(zu);
  }
  std::complex<double> q(1, 0), suma = 0;
  if (n==1) suma=z[0];
  else{
  for (int i = 0; i < n; i++) {
    suma += q / z[i];
  }
  suma=q/suma;}
  std::cout << "Paralelna veza ovih elemenata ima Z = " << abs(suma)
            << " i fi = " <<arg(suma)*180/(4*atan(1))<<"."<< std::endl;
  return 0;
}