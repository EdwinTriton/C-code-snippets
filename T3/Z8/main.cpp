// TP 2021/2022: LV 3, Zadatak 8
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

using std::string;

string IzdvojiRijec(string a, int n) {

  bool c = true;
  if (n <= 0)
    throw std::range_error("Pogresan redni broj rijeci");
  int i, p = 0, arr = a.length();
  bool rijec = false;
  int r = 0;
  for (i = 0; i < arr; i++) {
    if (a.at(i) != ' ' && !rijec) {
      rijec = true;
      p = i;
    }
    if (rijec && a.at(i) != ' ') {
      continue;
    } else {
      if (rijec)
        r++;
      rijec = false;
    }
    if (n == r) {
      c = false;
      break;
    }
  }
  if (rijec) r++;
  if (n == r) c=false;
  if (c)
    throw std::range_error("Pogresan redni broj rijeci");
  string izlaz;
  for (int t = p; t < i; t++) {
    izlaz.push_back(a.at(t));
  }
  return izlaz;
}

int main() {

  std::cout << "Unesite redni broj rijeci: " << std::endl;
  int n;
  std::cin >> n;
  std::cout << "Unesite recenicu: " << std::endl;
  string s;
  std::cin.ignore(100, '\n');
  std::getline(std::cin, s);
  try {
    string m = (IzdvojiRijec(s, n));
  } catch (std::range_error izuzetak) {
    std::cout << "IZUZETAK: Pogresan redni broj rijeci!" << std::endl;
    return 1;
  }
  std::cout << "Rijec na poziciji " << n << " je " << IzdvojiRijec(s, n);
  return 0;
}
