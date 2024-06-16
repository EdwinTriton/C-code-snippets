/* 
    TP 2018/2019: LV 5, Zadatak 6
	
	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.
	
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
bool Cifre(int x,int y) {
    int suma1(0),suma2(0);
    int a=abs(x),b=abs(y);
    do  {
        suma1+=a%10;a/=10;
    }while(a!=0);
    do  {
        suma2+=b%10;b/=10;
    }while(b!=0);
    if (suma1==suma2) return x<y;
    return suma1<suma2;
}
void Ispis(int a) {
    std::cout<<" "<<a;
    return ;
}
int main ()
{
    std::cout<<"Unesite broj elemenata: "<<std::endl;
    int n(0);
    std::cin>>n;
    std::cout<<"Unesite elemente: "<<std::endl;
    std::vector<int> v;
    int i(0);
    while (i<n) {
        int x(0);
        std::cin>>x;
        v.push_back(x);
        i++;
    }
    std::vector<int>::iterator q(&v);
    auto s(q+n-1);
    while (q<&v+n) {
        auto y=*s;
        *s=*max_element(q,&v+n,Cifre);
        *max_element(q,&v+n,Cifre)=y;
        s--;
        q++;
    }
    std::cout<<"Niz sortiran po sumi cifara glasi:";
    for_each(&v,&v+10,Ispis);
    std::cout<<std::endl<<"Unesite broj koji trazite: ";
    int p(0),t(0);std::cin>>p;
    s=&v;
    while (s<&v+n) {
        if (*s==p) t=
    }
	return 0;
}