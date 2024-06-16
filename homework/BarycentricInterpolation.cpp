// TP 2021/2022: Zadaća 3, Zadatak 1
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

double f(double x) { return x * x + std::sin(x); }

int maks(int x, int y) {
  if (x > y)
    return x;
  return y;
}

int mins(int x, int y) {
  if (x > y)
    return y;
  return x;
}

std::function<double(double)>
BaricentricnaInterpolacija(std::vector<std::pair<double, double>> vektor,
                           int d) {
  int n = vektor.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (vektor.at(i).first == vektor.at(j).first &&
          vektor.at(i).second != vektor.at(j).second)
        throw std::domain_error("Neispravni cvorovi");
    }
  }
  if (d < 0 || d >= n) {
    throw std::domain_error("Nedozvoljen red");
  }
  std::vector<double> w(n);
  for (int i = 1; i <= n; i++) {
    double suma = 0;
    for (int k = maks(1, i - d); k <= mins(i, n - d); k++) {
      double crazy_symbol = 1;
      int broj_neg = -1;
      if ((k - 1) % 2 == 0)
        broj_neg = 1;
      for (int j = k; j <= k + d; j++) {
        if (i != j) {
          crazy_symbol *= 1 / (vektor.at(i - 1).first - vektor.at(j - 1).first);
        }
      }
      suma += broj_neg * crazy_symbol;
    }
    w.at(i - 1) = suma;
  }
  return [vektor, w](double x) -> double {
    if (w.size() != vektor.size())
      std::cout << "PANIC!!!!" << std::endl;
    double g = 0, d = 0;
    for (int i = 1; i <= vektor.size(); i++) {
      if (vektor.at(i - 1).first == x)
        return vektor.at(i - 1).second;
      g += w.at(i - 1) * vektor.at(i - 1).second / (x - vektor.at(i - 1).first);
    }
    for (int i = 1; i <= vektor.size(); i++) {
      d += w.at(i - 1) / (x - vektor.at(i - 1).first);
    }
    return g / d;
  };
}

std::function<double(double)> BaricentricnaInterpolacija(double a(double),
                                                         double xmin,
                                                         double xmax,
                                                         double xdel, int d) {
  if (xmin > xmax || xdel <= 0)
    throw std::domain_error("Nekorektni parametri");
  std::vector<std::pair<double, double>> v;
  for (double i = xmin; i < xmax; i += xdel) {
    v.push_back({i, a(i)});
  }
  if (xmin == xmax && !v.size())
    v.push_back({xmin, a(xmin)});
  return BaricentricnaInterpolacija(v, d);
}

int main() {

  try {
    int t{};
    std::cout << "Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): "
              << std::endl;
    std::cin >> t;
    std::vector<std::pair<double, double>> v;
    if (t == 1) {
      std::cout << "Unesite broj cvorova: " << std::endl;
      int b{};
      std::cin >> b;
      std::cout << "Unesite cvorove kao parove x y: " << std::endl;
      for (double i = 0, x = 0, y = 0; i < b; i++) {
        std::cin >> x >> y;
        v.push_back({x, y});
      }
      std::cout << "Unesite red interpolacije: " << std::endl;
      std::cin >> t;
      auto bar = BaricentricnaInterpolacija(v, t);
      while (1) {
        std::string konac;
        double q{};
        std::cout << "Unesite argument (ili \"kraj\" za kraj): " << std::endl;
        std::cin >> q;
        if (!std::cin)
          break;
        std::cout << "f(" << q << ")"
                  << " = " << bar(q) << std::endl;
      }
    } else {
      double a{}, b{}, c{};
      std::cout << "Unesite krajeve intervala i korak: " << std::endl;
      std::cin >> a >> b >> c;
      std::cout << "Unesite red interpolacije: " << std::endl;
      std::cin >> t;
      auto bar = BaricentricnaInterpolacija(f, a, b, c, t);
      while (1) {
        double q{};
        std::cout << "Unesite argument (ili \"kraj\" za kraj): " << std::endl;
        std::cin >> q;
        if (!std::cin)
          break; /*popravi poslije*/
        std::cout << "f(" << q << ")"
                  << " = " << f(q);
        std::cout << " fapprox(" << q << ")"
                  << " = " << bar(q) << std::endl;
      }
    }
  } catch (std::domain_error e) {
    std::cout<<e.what();
  }
  return 0;
}