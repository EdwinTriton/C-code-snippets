// TP 2020/2021: Tutorijal 2, Zadatak 2
#include <iostream>
#include <vector>
bool TestPerioda(std::vector<double> a, double p) {
  if (a.size() <= p || a.size() == 0 || p <= 0)
    return false;
  int n = a.size(), i;
  for (i = 0; i < n; i++) {
    if (i + p < n) {
      if (a[i] != a[i + p]) {
        return false;
      }
    } else if (i-p>=0) {
      if (a[i] != a[i - p])
        return false;
    } 
  }
  return true;
}

int OdrediOsnovniPeriod(std::vector<double> a) {
    int n=a.size();
    for (int i=1;i<n;i++) {
        if (TestPerioda(a,i)) return i;
    }
    return 0;
}

int main() {
  std::cout<<"Unesite slijed brojeva (0 za kraj): ";
  std::vector<double> a;
  double broj;
  do {
    std::cin>>broj;
    if (broj!=0) a.push_back(broj);
  } while (broj!=0);
  int q=OdrediOsnovniPeriod(a);
  if (q) {
      std::cout<<"Slijed je periodican sa osnovnim periodom "<<q<<"."<<std::endl;
  }
  else std::cout<<"Slijed nije periodican! "<<std::endl;
  return 0;
}
