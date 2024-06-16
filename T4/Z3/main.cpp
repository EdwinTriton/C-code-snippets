// TP 2021/2022: LV 4, Zadatak 3
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

void IzdvojiKrajnjeRijeci(std::vector<std::string> s, std::string &a,
                          std::string &b) {
  if (s.size() == 0) {
    a = '\0';
    b = '\0';
    return;
  }
  a = s[0];
  b = s[0];
  char f = a[0], l = b[0];
  l = std::toupper(l);
  f = l;

  for (int i = 0; i < s.size(); i++) {
    std::string x = s[i];
    for (int k = 0; k < x.size(); k++)
      x[k] = std::toupper(x[k]);
    if (x[0] == f) {
      int k = 0;
      while (x[k] == std::toupper(a[k])) {
        k++;
        if (a.size() == k) {
          break;
        }
        if (k == x.size() || x[k] < std::toupper(a[k])) {
          a = s[i];
          break;
        }
        if (std::toupper(a[k]) < x[k]) {
          break;
        }
      }
    }
    if (x[0] < f) {
      f = x[0];
      a = s[i];
    }
    if (x[0] == l) {
      int k = 0;
      while (x[k] == std::toupper(b[k])) {
        k++;
        if (b.size() == k) {
          break;
        }
        if (k == x.size() || x[k] > std::toupper(b[k])) {
          b = s[i];
          break;
        }
        if (std::toupper(b[k]) > x[k]) {
          break;
        }
      }
    }
    if (x[0] > l) {
      l = x[0];
      b = s[i];
    }
  }
}

void ZadrziDuplikate(std::vector<std::string> &s) {
  std::vector<std::string> q;
  for (int i = 0; i < s.size(); i++) {
    for (int j = i + 1; j < s.size(); j++) {
      if (s[i] == s[j]) {
        bool t = true;
        for (std::string f : q) {
          if (f == s[i]) {
            t = false;
            break;
          }
        }
        if (t)
          q.push_back(s[i]);
      }
    }
  }
  s = move(q);
}

int main() {
    using namespace std;
    cout<<"Koliko zelite unijeti rijeci: ";
    int n;cin >>n;
    cout<<"Unesite rijeci: ";
    vector<string> s(n);
    cin>>ws;
    for (int i=0; i<n; i++) {
        cin>>s[i];
    }
    cout<<"Prva rijec po abecednom poretku je: ";
    string a,b;
    IzdvojiKrajnjeRijeci(s,a,b);
    cout<<a<<endl<<"Posljednja rijec po abecednom poretku je: "<<b<<endl<<"Rijeci koje se ponavljaju su: ";
    ZadrziDuplikate(s);
    for (int i=0; i<s.size(); i++)
    cout<<s[i]<<" ";
  return 0;
}
