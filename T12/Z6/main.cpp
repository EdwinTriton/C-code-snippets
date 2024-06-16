#include <cstring>
#include <iomanip>
#include <iostream>
#include <list>
#include <new>
#include <stdexcept>
#include <cstring>

template <typename TipEl> class Matrica {
  char ime_matrice;
  int br_redova, br_kolona;
  TipEl **elementi;
  static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
  static void DealocirajMemoriju(TipEl **elementi, int br_redova);
  void KopirajElemente(TipEl **elementi);

public:
  Matrica(int br_redova, int br_kolona, char ime = 0);
  Matrica(const Matrica &m);
  Matrica(Matrica &&m);
  Matrica();
  ~Matrica() { DealocirajMemoriju(elementi, br_redova); }
  Matrica &operator=(const Matrica &m);
  Matrica &operator=(Matrica &&m);

  friend std::istream &operator>>(std::istream &tok, Matrica &v) {
    for (int i = 0; i < v.br_redova; i++)
      for (int j = 0; j < v.br_kolona; j++) {
        std::cout << v.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
        tok >> v.elementi[i][j];
      }
    return tok;
  }

  friend std::ostream &operator<<(std::ostream &tok, const Matrica &v) {
    int a = std::cout.width();
    for (int i = 0; i < v.br_redova; i++) {
      for (int j = 0; j < v.br_kolona; j++) {

        tok << std::right << std::setw(a) << v.elementi[i][j];
      }
      tok << std::endl;
    }
    return tok;
  }



  template <typename Tip2>
  friend Matrica<Tip2> operator*(const Matrica<Tip2> &m1,
                                 const Matrica<Tip2> &m2);

  template <typename Tip2>
  friend Matrica<Tip2> operator*(const Matrica<Tip2> &m1, int a);

  template <typename Tip2>
  friend Matrica<Tip2> operator*(int a, const Matrica<Tip2> &m1);

  template <typename Tip2>
  friend Matrica<Tip2> operator+(const Matrica<Tip2> &m1,
                                 const Matrica<Tip2> &m2);

  template <typename Tip2>
  friend Matrica<Tip2> operator-(const Matrica<Tip2> &m1,
                                 const Matrica<Tip2> &m2);

  template <typename Tip2>
  friend Matrica<Tip2> operator+=(const Matrica<Tip2> &m1,
                                  const Matrica<Tip2> &m2);

  template <typename Tip2>
  friend Matrica<Tip2> operator-=(const Matrica<Tip2> &m1,
                                  const Matrica<Tip2> &m2);

  template <typename Tip2>
  friend Matrica<Tip2> operator*=(const Matrica<Tip2> &m1,
                                  const Matrica<Tip2> &m2);

  template <typename Tip2>
  friend Matrica<Tip2> operator*=(const Matrica<Tip2> &m1, int a);                              

  TipEl *operator[](int index) const { return elementi[index]; }

  TipEl *operator[](int index) { return elementi[index]; }

  TipEl &operator()(int indeks1, int indeks2) {
    if (indeks1 < 1 || indeks2 < 1 || indeks1 > br_redova ||
        indeks2 > br_kolona)
      std::__throw_range_error("Neispravan indeks");
    return elementi[indeks1 - 1][indeks2 - 1];
  }

  TipEl operator()(int indeks1, int indeks2) const {
    if (indeks1 < 1 || indeks2 < 1 || indeks1 > br_redova ||
        indeks2 > br_kolona)
      std::__throw_range_error("Neispravan indeks");
    return elementi[indeks1 - 1][indeks2 - 1];
  }
operator std::string();

};

  template <typename Tip2>
  Matrica<Tip2>::operator std::string(){
      std::string ret;
      ret="{";
      for(int i=0;i<br_redova;i++){
          ret+="{";
          for(int j=0;j<br_kolona;j++){
            ret+=std::to_string(int (elementi[i][j]));
            if(j+1!=br_kolona)
            ret+=","; 
          }
          ret+="}";
         if(i+1!=br_kolona)
         ret+=",";  
      }
      ret+="}";
      return ret;
  }


template <typename TipEl>
TipEl **Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona) {
  TipEl **elementi = new TipEl *[br_redova] {};
  try {
    for (int i = 0; i < br_redova; i++)
      elementi[i] = new TipEl[br_kolona];
  } catch (...) {
    DealocirajMemoriju(elementi, br_redova);
    throw;
  }
  return elementi;
}

template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova) {
  for (int i = 0; i < br_redova; i++)
    delete[] elementi[i];
  delete[] elementi;
}

template <typename TipEl>
Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime)
    : br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime),
      elementi(AlocirajMemoriju(br_redova, br_kolona)) {}


template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elementi) {
  for (int i = 0; i < br_redova; i++)
    for (int j = 0; j < br_kolona; j++)
      Matrica::elementi[i][j] = elementi[i][j];
}

template <typename TipEl>
Matrica<TipEl>::Matrica(const Matrica<TipEl> &m)
    : br_redova(m.br_redova), br_kolona(m.br_kolona),
      ime_matrice(m.ime_matrice),
      elementi(AlocirajMemoriju(m.br_redova, m.br_kolona)) {
  KopirajElemente(m.elementi);
}



template <typename TipEl>
Matrica<TipEl>::Matrica(Matrica<TipEl> &&m)
    : br_redova(m.br_redova), br_kolona(m.br_kolona), elementi(m.elementi),
      ime_matrice(m.ime_matrice) {
  m.br_redova = 0;
  m.elementi = nullptr;
}



template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator=(const Matrica<TipEl> &m) {
  if (br_redova < m.br_redova || br_kolona < m.br_kolona) {
    TipEl **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);
    DealocirajMemoriju(elementi, br_redova);
    elementi = novi_prostor;
  } else if (br_redova > m.br_redova)
    for (int i = m.br_redova; i < br_redova; i++)
      delete elementi[i];
  br_redova = m.br_redova;
  br_kolona = m.br_kolona;
  ime_matrice = m.ime_matrice;
  KopirajElemente(m.elementi);
  return *this;
}



template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator=(Matrica<TipEl> &&m) {
  std::swap(br_redova, m.br_redova);
  std::swap(br_kolona, m.br_kolona);
  std::swap(ime_matrice, m.ime_matrice);
  std::swap(elementi, m.elementi);
  return *this;
}



template <typename Tip2>
Matrica<Tip2> operator*(const Matrica<Tip2> &m1, const Matrica<Tip2> &m2) {

  if (m1.br_redova != m2.br_kolona || m2.br_redova != m1.br_kolona)
    std::__throw_domain_error("Matrice nisu saglasne za mnozenje");

  Matrica<Tip2> ret(m1.br_redova, m2.br_kolona);

  for (int i = 0; i < m1.br_redova; i++) {
    int k = 0;
    for (int l = 0; l < m2.br_kolona; l++) {
      Tip2 a = 0;
      for (int j = 0; j < m1.br_kolona; j++)
        a = a + m1.elementi[i][j] * m2.elementi[j][l];
      ret.elementi[i][k] = a;
      k++;
    }
  }
  return ret;
}



template <typename Tip2>
Matrica<Tip2> operator*(const Matrica<Tip2> &m1, int a) {
  Matrica<Tip2> ret = m1;
  for (int i = 0; i < m1.br_redova; i++) {
    for (int j = 0; j < m1.br_kolona; j++) {
      ret.elementi[i][j] = m1.elementi[i][j] * a;
    }
  }
  return ret;
}



template <typename TipEl>
Matrica<TipEl> operator+(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
  if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
  Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
  for (int i = 0; i < m1.br_redova; i++)
    for (int j = 0; j < m1.br_kolona; j++)
      m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
  return m3;
}



template <typename Tip2>
Matrica<Tip2> operator*(int a, const Matrica<Tip2> &m1) {
  return m1 * a;
}



template <typename Tip2>
Matrica<Tip2> operator*=(const Matrica<Tip2> &m1, int a) {

  for (int i = 0; i < m1.br_redova; i++) {
    for (int j = 0; j < m1.br_kolona; j++) {
      m1.elementi[i][j] = m1.elementi[i][j] * a;
    }
  }
  return m1;
}



template <typename Tip2>
Matrica<Tip2> operator-(const Matrica<Tip2> &m1, const Matrica<Tip2> &m2) {
  if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
  Matrica<Tip2> m3(m1.br_redova, m1.br_kolona);
  for (int i = 0; i < m1.br_redova; i++)
    for (int j = 0; j < m1.br_kolona; j++)
      m3.elementi[i][j] = m1.elementi[i][j] - m2.elementi[i][j];
  return m3;
}

template <typename Tip2>
Matrica<Tip2> operator+=(const Matrica<Tip2> &m1, const Matrica<Tip2> &m2) {
  if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
  for (int i = 0; i < m1.br_redova; i++)
    for (int j = 0; j < m1.br_kolona; j++)
      m1.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
  return m1;
}
template <typename Tip2>
Matrica<Tip2> operator-=(const Matrica<Tip2> &m1, const Matrica<Tip2> &m2) {
  if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
  for (int i = 0; i < m1.br_redova; i++)
    for (int j = 0; j < m1.br_kolona; j++)
      m1.elementi[i][j] = m1.elementi[i][j] - m2.elementi[i][j];
  return m1;
}
template <typename Tip2>
Matrica<Tip2> operator*=(const Matrica<Tip2> &m1, const Matrica<Tip2> &m2) {
 if (m1.br_redova != m2.br_kolona || m2.br_redova != m1.br_kolona)
    std::__throw_domain_error("Matrice nisu saglasne za mnozenje");

  Matrica<Tip2> ret(m1.br_redova, m2.br_kolona);

  for (int i = 0; i < m1.br_redova; i++) {
    int k = 0;
    for (int l = 0; l < m2.br_kolona; l++) {
      Tip2 a = 0;
      for (int j = 0; j < m1.br_kolona; j++)
        a = a + m1.elementi[i][j] * m2.elementi[j][l];
      ret.elementi[i][k] = a;
      k++;
    }
  }
   for (int i = 0; i < m1.br_redova; i++) {
    for (int j = 0; j < m1.br_kolona; j++) {
        m1.elementi[i][j]=ret.elementi[i][j];
    }
   }

  return m1;
}

int main() {

  int m, n;
  std::cout << "Unesi broj redova i kolona za matrice:\n";
  std::cin >> m >> n;
  try {

    Matrica<double> a(m, n, 'A'), b(m, n, 'B');
    std::cout << "Unesi matricu A:\n";
    std::cin >> a;
    std::cout << "Unesi matricu B:\n";
    std::cin >> b;
    std::cout << "Zbir ove dvije matrice je:\n";
    std::cout << std::setw(7) << a + b;

    /*
    Matrica<double> a(m, n, 'A'), b(m, n, 'B');
    std::cout << "Unesi matricu A:\n";
    a.Unesi();
    std::cout << "Unesi matricu B:\n";
    b.Unesi();
    std::cout << "Zbir ove dvije matrice je:\n";
    ZbirMatrica(a, b).Ispisi(7);
    */
  } catch (std::bad_alloc) {
    std::cout << "Nema dovoljno memorije!\n";
  }
  return 0;
}

