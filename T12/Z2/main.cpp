#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <utility>


template <typename Nekitip>
auto operator*(std::set<Nekitip> a, std::set<Nekitip> b) {
  std::set<Nekitip> c;
  for (auto x : a)
    for (auto y : b)
      if (x == y)
        c.emplace(x);
  return c;
}

template <typename Nekitip>
auto operator*=(std::set<Nekitip> &a, std::set<Nekitip> b) {
  std::set<Nekitip> c;
  for (auto x : a)
    for (auto y : b)
      if (x == y)
        c.emplace(x);
        a=c;
}

template <typename Nekitip>
auto operator+(std::set<Nekitip> a, std::set<Nekitip> b) {
  std::set<Nekitip> c;
  for (auto x : a)
    c.emplace(x);
  for (auto x : b)
    c.emplace(x);
  return c;
}

template <typename Nekitip>
auto operator+=(std::set<Nekitip> &a, std::set<Nekitip> b) {
  std::set<Nekitip> c;
  for (auto x : a)
    c.emplace(x);
  for (auto x : b)
    c.emplace(x);
  a=c;
}

template <typename Nekitip,typename Nekitip2>
auto operator%(std::set<Nekitip> &a, std::set<Nekitip2> b){
    
    
    std::set<std::pair<Nekitip,Nekitip2>>k;
    
    std::pair<Nekitip,Nekitip2> r;
    for (Nekitip x : a){
    for (Nekitip2 y : b){
        r.first=x;
        r.second=y;
        k.insert(r);
       }
    }
    return k;
}

template <typename Nekitip>
std::ostream &operator<<(std::ostream &tok, const std::set<Nekitip> &v) {
  tok << "{";
  int i = 0;
  for (auto x : v) {
    tok << x;
    if (i != v.size() - 1)
      tok << ",";
    i++;
  }
  
  tok << "}";
  return tok;
}

template <typename Nekitip,typename Nekitip2>
std::ostream &operator<<(std::ostream &tok, const std::set<std::pair<Nekitip, Nekitip2>> &v) {
  tok << "{";
  int i=0;
  for(auto x:v) {
    tok <<"("<<x.first<<","<<x.second<<")";
        if(i+1!=v.size())
      tok << ",";
      i++;
    
  }
  tok << "}";
  return tok;
}

int main() {
//AT4 testiranje Dekartovog proizvoda
std::set<char> s3{'A', 'B'};
std::set<int> s4{1, 2, 3};
std::cout << s3 % s4 << std::endl;
  return 0;
}