/* 
    TP 2018/2019: LV 6, Zadatak 1
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <limits>
template<typename Tip>
Tip *GenerirajStepeneDvojke(Tip a) {
    if (a<=0) throw std::domain_error("Broj elemenata mora biti pozitivan");
    Tip *q(nullptr);
    auto b((unsigned long long int) a);
    try {
        q=new Tip[b]{0};
    }
    catch (...) {
        delete [] q;
        throw std::runtime_error("Alokacija nije uspjela");
    }
    q[0]=1;
    for (int i=1; i<b; i++) {
        if (std::numeric_limits<Tip>::max()<q[i-1]*2 || q[i-1]*2<0) {
            delete [] q;
            throw std::overflow_error("Prekoracen dozvoljeni opseg");
            }
        q[i]=q[i-1]*2;
    }
    return q;
}

int main ()
{
    try {
        long long int a{};
        std::cout<<"Koliko zelite elemenata: ";
        std::cin>>a;
        auto s=GenerirajStepeneDvojke(a);
        for (int i=0; i<a; i++)
        std::cout<<" "<<s[i];
        delete [] s;
    }
    catch (std::exception &e) {
        std::cout<<"Izuzetak: "<<e.what();
    }
    
	return 0;
}