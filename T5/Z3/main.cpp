#include <iostream>
#include <algorithm>
#include <cmath>
void Unos(int &a) {
    std::cin>>a;
    return ;
}

bool Kvadrat(int a) {
    double s(sqrt(a));
    if (s-int(s)<0.0001) return true;
    return false;
}

bool Cif(int a,int b) {
    return (int(log(abs(a))/log(10))<int(log(abs(b))/log(10)));
}
bool Ci3(int a) {
    if (abs(a)==100) return true;
    if (abs(a)==1000) return false;
    if (int(log(abs(a))/log(10))==2) return true;
    return false;
}

void Ispis(int a) {
    std::cout<<" "<<a;
    return ;
}

int main ()
{
    using namespace std;
    cout<<"Unesite broj elemenata (max. 1000): ";
    int n(0);cin>>n;if(n>1000) return 1;
    cout<<"Unesite elemente: ";
    int a[1000]={0};
    for_each(a,a+n,Unos); 
    cout<<"Najveci element niza je "<<*max_element(a,a+n)<<endl;
    cout<<"Najmanji element niza se pojavljuje "<<count(a,a+n,*min_element(a,a+n))<<" puta u nizu"<<endl;
    cout<<"U nizu ima "<<count_if(a,a+n,Kvadrat)<<" brojeva koji su potpuni kvadrati"<<endl;
    cout<<"Prvi element sa najmanjim brojem cifara je "<<*min_element(a,a+n,Cif)<<endl;
    int b[1000]={0};
    auto c(remove_copy_if(a,a+n,b,Ci3));
    cout<<"Elementi koji nisu trocifreni su: ";
    for_each(b,c,Ispis);
	return 0;
}