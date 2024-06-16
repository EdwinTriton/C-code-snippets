/*
    TP 2018/2019: LV 6, Zadatak 2

        Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
        i sugestije saljite na mail: khodzic2@etf.unsa.ba

        Napomene: testovi su konacni tek pred tutorijal
                          za krsenje zabrana dobiva se 0 bodova za zadatak

*/
#include <iostream>
#include <new>
#include <vector>

template <typename tip> 
auto KreirajIzvrnutiNiz(tip a, tip b) {
  int duz(0);
  for (auto s=a;s!=b;s++) duz++;
  auto c=new typename std::remove_reference<decltype(*a)>::type[duz];
  for (int i=duz-1; i>=0; i--) {
    *(c+i)=*a++;
  }
  return c;
}

int main() {
  try { 
std::cout << "Koliko zelite elemenata: " ;
  int n{};
  std::cin >> n;
  std::vector<double> q(n);
  std::cout<< std::endl << "Unesite elemente: " << std::endl;
  for (int i = 0; i < n; i++) {
      double k{};
    std::cin >> k;
    q.push_back(k);
  };
  auto t = KreirajIzvrnutiNiz(q.begin(), q.end());
  std::cout << "Kreirani niz:" ;
  for (int i = 0; i < n; i++) {
    std::cout << " " << *(t+i);
  }
  delete [] t;
  }
  catch (std::bad_alloc) {
      std::cout<<"Nedovoljno memorije!";
  }
  return 0;
}
/*
template <typename tip> tip KreirajIzvrnutiNiz(tip a, tip b) {
  tip c{};b--;
  try {
    auto c = new typename std::vector<tip>;
    for (;a<b; b--) {
        c.push_back(*b);
    }
  } catch (...) {
    throw;
  }
  return c;
}
template <typename tip> tip KreirajIzvrnutiNiz(tip a, tip b) {
  tip c{};
  int w = b - a;
  try {
    tip *c = new tip[w];
  } catch (...) {
    throw;
  }
  auto d = c + w - 1;
  for (; d > c; d--) {
    *d = *a++;
  }
  return c;
}
*/