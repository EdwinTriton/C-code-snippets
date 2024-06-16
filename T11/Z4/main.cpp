#include <algorithm>
#include <cstring>
#include <iomanip>
#include <ios>
#include <iostream>
#include <list>

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

class Liga {
  int broj_timova;
  const int max_br_timova;
  Tim **timovi;

  void alociraj(int vel) {
    try {
      timovi = new Tim *[vel];
    } catch (...) {
      del();
      throw;
    }
  }

  void del() {
    if (timovi == nullptr)
      return;
    for (int i = 0; i < broj_timova; i++)
      delete timovi[i];
    delete[] timovi;
    timovi = nullptr;
  }

  bool timPostoji(const char ime_tima[]) {
    for (int i = 0; i < broj_timova; i++) {
      if (strcmp(ime_tima, timovi[i]->DajImeTima()) == 0)
        return true;
    }
    return false;
  }

  int indexx(const char *ime_tima) {
    for (int i = 0; i < broj_timova; i++) {
      if (strcmp(ime_tima, timovi[i]->DajImeTima()) == 0)
        return i;
    }
    return -1;
  }

  static bool kriteri(Tim *x, Tim *y) {
    if (x->DajBrojPoena() != y->DajBrojPoena())
      return x->DajBrojPoena() > y->DajBrojPoena();
    if (x->DajGolRazliku() != y->DajGolRazliku())
      return x->DajGolRazliku() > y->DajGolRazliku();
    if (strcmp(x->DajImeTima(), y->DajImeTima()) < 0)
      return true;
    return false;
  }

public:
  explicit Liga(int velicina_lige)
      : broj_timova(0), max_br_timova(velicina_lige), timovi(nullptr) {
    alociraj(max_br_timova);
  };
  explicit Liga(std::initializer_list<Tim> lista_timova)
      : broj_timova(lista_timova.size()), max_br_timova(lista_timova.size()),
        timovi(nullptr) {
    try {
      alociraj(max_br_timova);
      int i = 0;
      for (auto j = lista_timova.begin(); j != lista_timova.end(); j++) {
        timovi[i] = new Tim(*j);
        i++;
      }
    } catch (...) {
      del();
      throw;
    }
  };
  ~Liga() {
    for (int i = 0; i < broj_timova; i++)
      delete timovi[i];
    delete[] timovi;
  }
  Liga(const Liga &l)
      : broj_timova(l.broj_timova), max_br_timova(l.max_br_timova),
        timovi(nullptr) {
    try {
      alociraj(max_br_timova);
      for (int i = 0; i < broj_timova; i++) {
        this->timovi[i] = new Tim(*l.timovi[i]);
      }
    } catch (...) {
      del();
      throw;
    }
  }
  Liga(Liga &&l)
      : broj_timova(l.broj_timova), max_br_timova(l.max_br_timova),
        timovi(nullptr) {
    timovi = l.timovi;
  }
  Liga &operator=(const Liga &l) {
    if (max_br_timova != l.max_br_timova)
      std::__throw_logic_error("Nesaglasni kapaciteti liga");
    if (&l == this)
      return *this;
    Tim **iskra = nullptr;
    try {
        iskra=new Tim*[l.broj_timova];
      for (int i = 0; i < l.broj_timova; i++) {
        iskra[i] = nullptr;
        iskra[i] = new Tim(*l.timovi[i]);
      }
      for (int i = 0; i < broj_timova; i++) {
        delete timovi[i];
      }
      delete[] timovi;
      timovi = iskra;
      iskra = nullptr;
      broj_timova = l.broj_timova;

    } catch (...) {
      for (int i = 0; i < broj_timova; i++) {
        delete iskra[i];
      }
      delete[] iskra;
      iskra = nullptr;
      throw;
    }
    return *this;
  }
  Liga &operator=(Liga &&l) {
    if (&l == this)
      return *this;
    if (max_br_timova != l.max_br_timova)
      std::__throw_logic_error("Nesaglasni kapaciteti liga");
    timovi = l.timovi;
    broj_timova = l.broj_timova;
    l.timovi = nullptr;
    return *this;
  }
  void DodajNoviTim(const char ime_tima[]) {
    if (max_br_timova == broj_timova)
      std::__throw_range_error("Liga popunjena");
    if (timPostoji(ime_tima))
      std::__throw_logic_error("Tim vec postoji");
    try {
      broj_timova++;
      timovi[broj_timova - 1] = new Tim(ime_tima);

    } catch (...) {
      broj_timova--;
      throw;
    }
  }
  void RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1,
                           int rezultat_2) {
    if (timPostoji(tim1) && timPostoji(tim2)) {
      try {
        timovi[indexx(tim1)]->ObradiUtakmicu(rezultat_1, rezultat_2);
        timovi[indexx(tim2)]->ObradiUtakmicu(rezultat_2, rezultat_1);
      } catch (...) {
        std::__throw_range_error("Neispravan broj golova");
      }
    } else
      std::__throw_logic_error("Tim nije nadjen");
  }
  void IspisiTabelu() {
    std::sort(timovi, timovi + broj_timova, kriteri);
    for (int i = 0; i < broj_timova; i++)
      timovi[i]->IspisiPodatke();
  }
};

int main() {
    

Liga l1{"NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo", "FK Sloboda", "FK Krupa", "FK Radnik Bijeljina"};
l1.RegistrirajUtakmicu("FK Sloboda", "HSK Zrinjski",1,1);
	
Liga l2{"NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo"};
Liga l3{"NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo","NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo","NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo"};
	
l3 = std::move(l1);
l2 = l1;
	
std::cout << "Liga 1:" << std::endl;
l1.IspisiTabelu();
std::cout << std::endl  << "Liga 2:" << std::endl;
l2.IspisiTabelu();
std::cout << std::endl  << "Liga 3:" << std::endl;
l3.IspisiTabelu();
  return 0;
}