#include <algorithm>
#include <cstring>
#include <iomanip>
#include <ios>
#include <iostream>
#include <list>
#include <vector>

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
  
  std::vector<Tim*> timovi;

  void alociraj(int vel) {
    try {
        timovi.resize(vel);
      //  for(int i=0;i<vel;i++){
      //      timovi[i]=new Tim;
     // }
    } catch (...) {
      del();
      throw;
    }
  }

  void del() {
      bool x=true;
      for(int i=0;i<timovi.size();i++){
          if (timovi[i] != nullptr){
              x=false;
              break;
          }
      }

    if (x)
      return;
    for (int i = 0; i < timovi.size(); i++)
      delete timovi[i];
  }

  bool timPostoji(const char ime_tima[]) {
    for (int i = 0; i < timovi.size(); i++) {
      if (strcmp(ime_tima, timovi[i]->DajImeTima()) == 0)
        return true;
    }
    return false;
  }

  int indexx(const char *ime_tima) {
    for (int i = 0; i < timovi.size(); i++) {
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
  explicit Liga(int velicina_lige){
    alociraj(velicina_lige);
  };
  explicit Liga(std::initializer_list<Tim> lista_timova){
    try {
      alociraj(lista_timova.size());
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
    for (int i = 0; i < timovi.size(); i++)
      delete timovi[i];
  }
  Liga( Liga &l){
    try {
        
      alociraj(l.timovi.size());
      for (int i = 0; i < timovi.size(); i++) {
        this->timovi[i] = new Tim(*l.timovi[i]);
        
      }
    } catch (...) {
      del();
      throw;
    }
  }
  Liga(Liga &&l){
    timovi = l.timovi;
    for(int i=0;i<l.timovi.size();i++)
    l.timovi[i]=nullptr;
    l.timovi.resize(0);
  }
  Liga &operator=(const Liga &l) {
      
    if (&l == this)
      return *this;
      for(int i=0;i<timovi.size();i++)
      delete timovi[i];
      if(l.timovi.size()==0){
          timovi.resize(0);
          return *this;
      }
      
     std::vector<Tim*>iskra ;
     iskra.resize(l.timovi.size());
    try {
        for(int i=0;i<iskra.size();i++){
        iskra[i] = new Tim(*l.timovi[i]);
      }

      timovi = iskra;
      for(int i=0;i<iskra.size();i++)
        iskra[i] =nullptr;
        

    } catch (...) {
      for (int i = 0; i < timovi.size(); i++) {
        delete iskra[i];
      }
      
      for(int i=0;i<iskra.size();i++)
        iskra[i] =nullptr;
      throw;
    }
    return *this;
  }
  Liga &operator=(Liga &&l) {
    if (&l == this)
      return *this;
      for(int i=0;i<timovi.size();i++)
      delete timovi[i];
      
    timovi = l.timovi;
    for(int i=0;i<l.timovi.size();i++){
        l.timovi[i] = nullptr;
    }
    l.timovi.resize(0);
    return *this;
  }
  void DodajNoviTim(const char ime_tima[]) {
      
    if (timPostoji(ime_tima))
      std::__throw_logic_error("Tim vec postoji");
    try {
      timovi.resize(timovi.size()+1);
      timovi[timovi.size() - 1] = new Tim(ime_tima);

    } catch (...) {
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
    std::sort(timovi.begin(), timovi.end(), kriteri);
    for (int i = 0; i < timovi.size(); i++)
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