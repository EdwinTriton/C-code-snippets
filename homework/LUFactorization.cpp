// TP 2021/2022: Zadaća 1, Zadatak 2
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

const double eps(0.0000000001);
typedef std::vector<std::vector<double>> Matrica;

//Checks the Format of the Matrix
bool IspravniFormat(Matrica A) {
  for (int i = 0; i < A.size() - 1; i++) {
    if (A.at(i).size() != A.at(i + 1).size()) {
      throw std::domain_error("Neispravna matrica!");
    }
  }
  return true;
}

bool IspravniFormatM(Matrica A) {
    if (A.size()==0) throw std::domain_error("Matrice nisu saglasne za mnozenje!");
    if (A.at(0).size()==0) throw std::domain_error("Matrice nisu saglasne za mnozenje!");
  for (int i = 0; i < A.size() - 1; i++) {
    if (A.at(i).size() != A.at(i + 1).size()) {
      throw std::domain_error("Matrice nisu saglasne za mnozenje!");
    }
  }
  return true;
}

//Multiplies Matrices
Matrica MnozenjeMatrica(Matrica A, Matrica B) {
if (A.size()==0 && B.size()==0) return A;
if (!A.size() || !B.size()) throw std::domain_error("Matrice nisu saglasne za mnozenje!");
  IspravniFormat(A);
  IspravniFormat(B);
  if (A.at(0).size() != B.size()) {
    throw std::domain_error("Matrice nisu saglasne za mnozenje!");
  }
  Matrica m(A.size(), std::vector<double>(B.at(0).size()));
  for (int i = 0; i < A.size(); i++) {
    for (int j = 0; j < B.at(0).size(); j++) {
      double suma = 0;
      for (int k = 0; k < B.size(); k++)
        suma += A.at(i).at(k) * B.at(k).at(j);
      m.at(i).at(j) = suma;
    }
  }
  return m;
}

//LU decomposition using the Doolittle algorithm
std::array<std::vector<std::vector<double>>, 2> DoolittleLU(Matrica H) {
    if (!H.size()) return std::array<std::vector<std::vector<double>>, 2> {{H,H}};
  IspravniFormat(H);
  if (H.size() != H.at(0).size()) {
    throw std::domain_error("Matrica mora biti kvadratna!");
  }
  Matrica L(H.size(), std::vector<double>(H.size())),
      U(H.size(), std::vector<double>(H.size()));
  for (int i = 0; i < H.size(); i++) {
    for (int j = 0; j < H.size(); j++) {
      if (j == i)
        L.at(i).at(j) = 1;
    }
  }
  for (int i = 0; i < H.size(); i++) {
    for (int j = 0; j < H.size(); j++) {
      double suma(0);
      if (j < i) {
        for (int k = 0; k < j; k++) {
          suma += L.at(i).at(k) * U.at(k).at(j);
        }
        if (fabs(U.at(j).at(j)) < eps)
          throw std::domain_error("Matrica je singularna!");
        L.at(i).at(j) = (H.at(i).at(j) - suma) / U.at(j).at(j);
      } else {
        for (int m = 0; m < i; m++) {
          suma += L.at(i).at(m) * U.at(m).at(j);
        }
        U.at(i).at(j) = H.at(i).at(j) - suma;
      }
      if (i == H.size() - 1 && i == j && fabs(U.at(j).at(j)) < eps)
        throw std::domain_error("Matrica je singularna!");
    }
  }
  return std::array<std::vector<std::vector<double>>, 2>{{L, U}};
}

//Checks if the factorisation is correct
bool ProvjeriFaktorizaciju(Matrica H,
                           std::array<std::vector<std::vector<double>>, 2> LU) {
  try {
      if (H.size()==0 && LU.at(0).size()==0 && LU.at(1).size()==0) return true;
      if (!H.size() || LU.at(0).size()==0 || LU.at(1).size()==0) return false;
    IspravniFormat(H);
    IspravniFormat(LU.at(0));
    IspravniFormat(LU.at(1));
    Matrica H2(MnozenjeMatrica(LU.at(0), LU.at(1)));
    if (H.size() != H.at(0).size() ||
        LU.at(0).size() != LU.at(0).at(0).size() ||
        LU.at(1).size() != LU.at(1).at(0).size())
      return false;
    for (int i = 0; i < H.size(); i++) {
      for (int j = 0; j < H.size(); j++) {
        if (!(fabs(H2.at(i).at(j) - H.at(i).at(j)) < eps))
          return false;
      }
    }
  } catch (std::domain_error izuzetak) {
    return false;
  }
  return true;
}

void IspisiMatricu(Matrica m) {
  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m.size(); j++)
      std::cout << m.at(i).at(j) << " ";
    std::cout << std::endl;
  }
}

//Testing the code
int main() {
   
  std::cout << "Broj redova/kolona matrice: " << std::endl;
  int n(0);
  std::cin >> n;
  Matrica M(n, std::vector<double>(n));
  std::cout << "Elementi matrice: " << std::endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int x = 0;
      std::cin >> x;
      M.at(i).at(j) = x;
    }
  }
  std::array<std::vector<std::vector<double>>, 2> LU;
  try {
    LU = DoolittleLU(M);
  } catch (std::domain_error izuzetak) {
    std::cout << "LU faktorizacija ne postoji, jer je matrica singularna!";
    return 1;
  }
  if (!ProvjeriFaktorizaciju(M, LU)) {
    std::cout << "LU faktorizacija ne postoji, jer je matrica singularna!";
  } else {
    std::cout << "Matrica L:" << std::endl;
    IspisiMatricu(LU.at(0));
    std::cout << "Matrica U:" << std::endl;
    IspisiMatricu(LU.at(1));
  }
  return 0;
}
