// TP 2021/2022: LV 4, Zadatak 4
#include <cmath>
#include <iostream>
#include <string>

template <typename tip> void UnosBroja(std::string s, std::string c, tip &n) {
  bool t = false;
  do {
    if (!std::cin || t) {
      std::cout << c << std::endl;
      std::cin.clear();
      std::cin.ignore(1000, '\n');
    }
    std::cout << s;
    std::cin >> n;
    t = (std::cin.peek() != '\n');
  } while (!std::cin || std::cin.peek() != '\n');
}

int main() {
  double i;
  int j;
  UnosBroja("Unesite bazu: ", "Neispravan unos, pokusajte ponovo...\n", i);
  std::cout<<std::endl;
  UnosBroja("\nUnesite cjelobrojni eksponent: ",
            "Neispravan unos, pokusajte ponovo...", j);
  double q = 1,s=i;
  int w=j;
  if (w<0) {
      w*=-1;
      s=1/s;
  }
  for (int c = 0; c < w; c++) {
    q *= s;
  }
  printf("%g na %d iznosi %g", i, j, q);
  return 0;
}
