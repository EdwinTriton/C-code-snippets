#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cstring>
class Tim {
  char ime_tima[20];
  int broj_odigranih;
  int broj_pobjeda;
  int broj_nerijesenih;
  int broj_poraza;
  int broj_datih;
  int broj_primljenih;
  int broj_poena;

public:
  Tim(const char ime[]) {
    if (std::strlen(ime) > 20) {
      std::__throw_range_error("Predugacko ime tima");
    }

    std::strcpy(ime_tima, ime);

    broj_odigranih = 0;
    broj_pobjeda = 0;
    broj_nerijesenih = 0;
    broj_poraza = 0;
    broj_datih = 0;
    broj_primljenih = 0;
    broj_poena = 0;
  };

  void ObradiUtakmicu(int datih, int primljenih) {
    if (datih < 0 || primljenih < 0)
      std::__throw_range_error("Neispravan broj golova");

    broj_odigranih++;
    if (datih > primljenih) {
      broj_pobjeda++;
      broj_poena += 3;
    } else if (datih < primljenih) {
      broj_poraza++;
    } else {
      broj_nerijesenih++;
      broj_poena++;
    }
    broj_datih += datih;
    broj_primljenih += primljenih;
  };

  const char *DajImeTima() const { return ime_tima; };
  int DajBrojPoena() const { return broj_poena; };
  int DajGolRazliku() const { return broj_datih - broj_primljenih; };
  void IspisiPodatke() const {
    std::cout << std::left << std::setw(20) << ime_tima;
    std::cout << std::right << std::setw(4) << broj_odigranih << std::right
              << std::setw(4) << broj_pobjeda;
    std::cout << std::right << std::setw(4) << broj_nerijesenih << std::right
              << std::setw(4) << broj_poraza;
    std::cout << std::right << std::setw(4) << broj_datih << std::right
              << std::setw(4) << broj_primljenih;
    std::cout << std::right << std::setw(4) << broj_poena << std::endl;
  };
};
int main ()
{
    char a[10]{};
    std::cout<<"Unesi ime tima: \n";
    std::cin.getline(a,10);Tim A(a);
    std::cout<<"Unesi rezultate prosle igre\n";
    int b,c;
    std::cin>>b>>c;
    A.ObradiUtakmicu(b,c);
    A.IspisiPodatke();
	return 0;
}