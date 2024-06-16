/*
   TP 2018/2019: LV 6, Zadatak 3

       Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
       i sugestije saljite na mail: khodzic2@etf.unsa.ba

       Napomene: testovi su konacni tek pred tutorijal
                         za krsenje zabrana dobiva se 0 bodova za zadatak

*/
#include <iostream>
#include <stdexcept>

int **KreirajTrougao(int n) {
  if (n <= 0)
    throw std::domain_error("Broj redova mora biti pozitivan");
  typedef int *PokTip;
  PokTip*a=nullptr;
  try {
      a=new int*[n] {};
      try {
          for (int i=0; i<n; i++) {
              a[i]=new int[2*i+1];
              for (int j=0; j<2*i+1; j++) {
                  a[i][j]=abs(i-j)+1;
              }
          }
      }
      catch (...) {
          for (int i=0; i<n; i++) delete[] a[i];
          throw;
      }
  }
  catch (...) {
          delete[] a;
          throw;
      }
  return a;
}
int main() {
  std::cout << "Koliko zelite redova: " << std::endl;
  int n{};
  std::cin >> n;
  int **s{};
  try {
    auto s(KreirajTrougao(n));
    for (int i = 0, z = 1; i < n; i++, z += 2) {
      for (int j = 0; j < z; j++) {
        std::cout << " " << s[i][j];
      }
      std::cout << std::endl;
    }
    for (int i=0; i<n; i++) {
        delete[] s[i];
    }
    delete []s;
  } catch (std::domain_error e) {
    std::cout << "Izuzetak: " << e.what();
  } catch (std::bad_alloc) {
    std::cout << "Izuzetak: Nedovoljno memorije!";
  }
  return 0;
}