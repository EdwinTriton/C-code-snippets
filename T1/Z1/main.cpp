#include <iostream>
int main() {
    std::cout<<(-17)%(2);
}

/*int main() {
  std::cout << "Unesite duzinu, sirinu i dubinu bazena u metrima: ";
  int a, b, c;
  double d;
  std::cin >> a >> b >> c;
  std::cout<<log(a)/log(10);
  std::cin.ignore(10000, '\n');

  std::cout << "Unesite sirinu plocice u centimetrima: \n";
  std::cin >> d;
  std::cin.ignore(10000, '\n');

  d /= 100;
  if (!(a / d == int(a / d) && b / d == int(b / d) && c / d == int(c / d))) {
    std::cout << "Poplocavanje bazena dimenzija " << a << "x" << b << "x"
              << c << "m sa plocicama dimenzija " << d*100 << "x" << d*100
              << "cm\nnije izvodljivo bez lomljenja plocica!";
    return 0;
  }
  std::cout << "Za poplocavanje bazena dimenzija " << a << "x" << b << "x" << c
            << "m sa plocicama dimenzija " << d * 100 << "x" << d * 100
            << "cm potrebno je " << (2 * a * c / d + 2 * b * c / d + a * b / d)/d
            << " plocica.";
  return 0;
}*/