// TP 2021/2022: LV 4, Zadatak 5
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

template <typename tip>
std::vector<tip> Presjek(std::vector<tip> v1, std::vector<tip> v2) {
  std::vector<tip> izlaz;
  for (int i = 0; i < v1.size(); i++) {
    for (int j = 0; j < v2.size(); j++) {
      if (v1[i] == v2[j]) {
        bool t = true;
        for (int k = 0; k < izlaz.size(); k++) {
          if (v1[i] == izlaz[k]) {
            t = false;
            break;
          }
        }
        if (t) {
          izlaz.push_back(v1[i]);
        }
      }
    }
  }
  return izlaz;
}

int main() {
  using namespace std;
  cout << "Test za realne brojeve...\nUnesite broj elemenata prvog vektora: "
          "Unesite elemente prvog vektora: Unesite broj elemenata drugog "
          "vektora: Unesite elemente drugog vektora: Zajednicki elementi su: ";
  int n1, n2;
  vector<double> v1, v2;
  cin >> n1;
  for (int i = 0; i < n1; i++) {
    double q;
    cin >> ws >> q;
    cin >> ws;
    v1.push_back(q);
  }
  cin >> n2;
  for (int i = 0; i < n2; i++) {
    double q;
    cin >> q;
    v2.push_back(q);
  }
  vector<double> p = Presjek(v1, v2);
  for (int i = 0; i < p.size(); i++) {
    cout << " " << p[i];
  }
  cout << "\n\nTest za stringove...\nUnesite broj elemenata prvog vektora: "
          "Unesite elemente prvog vektora (ENTER nakon svakog unosa): Unesite "
          "broj elemenata drugog vektora: Unesite elemente drugog vektora "
          "(ENTER nakon svakog unosa): Zajednicki elementi su: ";
  int d1, d2;
  vector<string> s1, s2;
  cin >> d1;
  cin.ignore(100, '\n');
  for (int i = 0; i < d1; i++) {
    string q;
    getline(cin,q);
    s1.push_back(q);
  }
  cin >> d2;
  cin.ignore(100, '\n');
  for (int i = 0; i < d2; i++) {
    string q;
    getline(cin,q);
    s2.push_back(q);
  }
  vector<string> u = Presjek(s1, s2);
  for (int i = 0; i < u.size(); i++) {
    cout << "\n" << u[i];
  }
  return 0;
}
