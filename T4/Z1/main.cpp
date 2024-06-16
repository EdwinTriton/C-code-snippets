// TP 2021/2022: LV 4, Zadatak 1
#include <cmath>
#include <iostream>
#include <limits>

int Cifre(long long int n, int &min, int &max) {
  min = 9;
  max = 0;
  int i = 0;
  do {
    if (abs(int(n % 10)) > max)
      max = abs(int(n % 10));
    if (abs(int(n % 10)) < min)
      min = abs(int(n % 10));
    n /= 10;
    i++;
  } while (n != 0);
  return i;
}

int main() {
  int mini, maxi;
  int e = Cifre(std::numeric_limits<long long int>::min(), mini, maxi);
  using namespace std;
  cout << "Unesite broj: " << endl;
  long long int n;
  cin >> n;
  int a, b;
  Cifre(n, a, b);
  cout << " Broj " << n << " ima " << Cifre(n, a, b) << " cifara, najveca je "
       << b << " a najmanja " << a << ".";
  return 0;
}
