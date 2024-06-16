//TP 2021/2022: Zadaća 2, Zadatak 3
#include <iostream>
#include <cmath>
#include <type_traits>
#include <vector>

template<typename Tip,typename Tiq>
auto ZbirKontejnera(Tip k1,Tiq k2) -> std::vector<decltype(*k1.begin() + *k2.begin())> {
    int s{},w{};
    for (auto f=k1.begin(); f!=k1.end(); f++) s++;
    for (auto f=k2.begin(); f!=k2.end(); f++) w++;
    int a(s);
    if (w>s) a=w;
    std::vector <decltype(*k1.begin() + *k2.begin()) > v (a);
    auto b1=k1.begin();
    auto b2=k2.begin();
    for (s=0; b1!=k1.end(); b1++,s++) v.at(s)=(*b1);
    for (w=0; b2!=k2.end();b2++,w++) v.at(w)+=*b2;
    return v;
}

int main ()
{
    int n1(0),n2(0);
    std::cout<<"Duzina prvog kontejnera: "<<std::endl;
    std::cin>>n1;
    std::cout<<"Elementi prvog kontejnera: "<<std::endl;
    std::vector<double> a{},b{};
    for (int i=0; i<n1; i++) {
        double q;
        std::cin>>q;
        a.push_back(q);
    }
    std::cout<<"Duzina drugog kontejnera: "<<std::endl;
    std::cin>>n2;
    std::cout<<"Elementi drugog kontejnera: "<<std::endl;
    for (int i=0; i<n2; i++) {
        double q;
        std::cin>>q;
        b.push_back(q);
    }
    auto q ( ZbirKontejnera(a,b) );
    std::cout<<"Zbir kontejnera: ";
    for (int i=0; i<q.size(); i++) {
        std::cout<<q.at(i)<<" ";
    }
	return 0;
}
