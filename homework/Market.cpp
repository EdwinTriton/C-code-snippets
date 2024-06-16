//TP 2021/2022: Zadaća 5, Zadatak 2
#include <functional>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>

//Stock market class
class Berza {
    int min,max;
    std::vector<int> veq;
    public:
    explicit Berza(int a) : max(a), min(0) {if (a<0) throw std::range_error("Ilegalne granicne cijene");}
    Berza(int b,int a) : max(a), min(b) {if (a<0 || b<0) throw std::range_error("Ilegalne granicne cijene");}
    void RegistrirajCijenu(int a) {if (a<0 || a>max || a<min) throw std::range_error("Ilegalna cijena");veq.push_back(a);}
    int DajBrojRegistriranihCijena() {return veq.size();}
    void BrisiSve() {veq={};}
    int DajMinimalnuCijenu() const {if (!veq.size()) throw std::range_error("Nema registriranih cijena");std::vector<int> vek=veq;return *std::min_element(vek.begin(),vek.end());}
    int DajMaksimalnuCijenu() const {if (!veq.size()) throw std::range_error("Nema registriranih cijena");std::vector<int> vek=veq;return *std::max_element(vek.begin(),vek.end());}
    bool operator!() const {return !veq.size();}
    int DajBrojCijenaVecihOd(int a) const ; 
    void Ispisi() const;
    const int& operator[](int a) const {if (veq.size()<=a-1 || a-1<0) throw std::range_error("Neispravan indeks"); return veq.at(a-1);}
    Berza operator-() const {std::vector<int> vek(veq.size());std::transform(veq.begin(),veq.end(),vek.begin(),std::bind(std::minus<int>(), max+min, std::placeholders::_1));Berza q(*this);q.veq=vek;return q;}
    Berza operator+(int a) const;
    friend Berza operator+(int x,const Berza &a) {return a+x;}
    inline Berza operator-(int a) {return this->operator+(-a);}
    friend Berza operator-(int x,const Berza &a);
    Berza operator+(const Berza &a) const;
    Berza operator-(const Berza &a) const;
    bool operator==(const Berza &a) const {return (this->veq==a.veq);}
    bool operator!=(const Berza &a) const {return !this->operator==(a);};
    Berza& operator++();
    Berza operator++(int);
    Berza& operator--();
    Berza operator--(int);
    Berza& operator+=(const Berza &a) {return *this=*this+a;}
    Berza& operator-=(const Berza &a) {return *this=*this-a;}
    Berza& operator+=(int a) {return *this=*this+a;}
    Berza& operator-=(int a) {return *this=*this-a;}
};

//give # of values greater than a
int Berza::DajBrojCijenaVecihOd(int a) const {
    if (!(*this)) throw std::range_error("Nema registriranih cijena");
    return std::count_if(veq.begin(),veq.end(),std::bind(std::greater<int>(), std::placeholders::_1, a));
}

//Print
void Berza::Ispisi() const {
    std::vector<int> vek=veq;
    std::sort(vek.begin(),vek.end(),std::greater<int>());
    std::cout.precision(2);
    std::cout<<std::fixed;
    std::transform(vek.begin(), vek.end(), std::ostream_iterator<double>(std::cout,"\n"), std::bind(std::divides<double>(), std::placeholders::_1, 100));
}

Berza Berza::operator+(int a) const {
    auto izlav=this->veq;
    std::transform(this->veq.begin(),this->veq.end(), izlav.begin(), std::bind(std::plus<int>(), std::placeholders::_1, a));
    if (count_if(izlav.begin(), izlav.end(),std::bind(std::less<int>(), this->max, std::placeholders::_1)) || count_if(izlav.begin(), izlav.end(),std::bind(std::greater<int>(), this->min, std::placeholders::_1))) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    Berza izlaz(this->min,this->max);
    izlaz.veq=izlav;
    return izlaz;
}

Berza operator-(int x,const Berza &a) {
    auto izlav=a.veq;
    std::transform(a.veq.begin(),a.veq.end(),izlav.begin(), std::bind(std::minus<int>(), x, std::placeholders::_1));
    if (count_if(izlav.begin(), izlav.end(),std::bind(std::less<int>(), a.max, std::placeholders::_1)) || count_if(izlav.begin(), izlav.end(),std::bind(std::greater<int>(), a.min, std::placeholders::_1))) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    Berza izlaz(a.min,a.max);
    izlaz.veq=izlav;
    return izlaz;
}

Berza Berza::operator+(const Berza &a) const {
    if (a.max!=this->max || a.min!=this->min || a.veq.size()!=this->veq.size()) throw std::domain_error("Nesaglasni parametri");
    Berza izlaz(*this);
    std::transform(a.veq.begin(),a.veq.end(),this->veq.begin(),izlaz.veq.begin(),std::plus<int>());
    if (count_if(izlaz.veq.begin(), izlaz.veq.end(),std::bind(std::less<int>(), a.max, std::placeholders::_1)) || count_if(izlaz.veq.begin(), izlaz.veq.end(),std::bind(std::greater<int>(), a.min, std::placeholders::_1))) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    return izlaz;
}

Berza Berza::operator-(const Berza &a) const {
    if (a.max!=this->max || a.min!=this->min || a.veq.size()!=this->veq.size()) throw std::domain_error("Nesaglasni parametri");
    Berza izlaz(*this);
    std::transform(a.veq.begin(),a.veq.end(),this->veq.begin(),izlaz.veq.begin(),std::minus<int>());
    if (count_if(izlaz.veq.begin(), izlaz.veq.end(),std::bind(std::less<int>(), a.max, std::placeholders::_1)) || count_if(izlaz.veq.begin(), izlaz.veq.end(),std::bind(std::greater<int>(), a.min, std::placeholders::_1))) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    return izlaz;
}

Berza Berza::operator++(int) {
    Berza izlaz(*this);
    std::transform(izlaz.veq.begin(), izlaz.veq.end(),this->veq.begin(), std::bind(std::plus<int>(), std::placeholders::_1, 100));
    if (DajBrojCijenaVecihOd(this->max) || count_if(this->veq.begin(), this->veq.end(),std::bind(std::less<int>(), this->max, std::placeholders::_1)) ) throw std::range_error("Prekoracen dozvoljeni opseg cijena");
    return izlaz;
}

Berza Berza::operator--(int) {
    Berza izlaz(*this);
    std::transform(izlaz.veq.begin(), izlaz.veq.end(),this->veq.begin(), std::bind(std::minus<int>(), std::placeholders::_1, 100));
    if (DajBrojCijenaVecihOd(this->max) || count_if(this->veq.begin(), this->veq.end(),std::bind(std::less<int>(), this->max, std::placeholders::_1)) ) throw std::range_error("Prekoracen dozvoljeni opseg cijena");
    return izlaz;
}

Berza& Berza::operator--() {
    std::transform(this->veq.begin(), this->veq.end(),this->veq.begin(), std::bind(std::minus<int>(), std::placeholders::_1, 100));
    if (DajBrojCijenaVecihOd(this->max) || count_if(this->veq.begin(), this->veq.end(),std::bind(std::less<int>(), this->max, std::placeholders::_1)) ) throw std::range_error("Prekoracen dozvoljeni opseg cijena");
    return *this;
}

Berza& Berza::operator++() {
    std::transform(this->veq.begin(), this->veq.end(),this->veq.begin(), std::bind(std::plus<int>(), std::placeholders::_1, 100));
    if (DajBrojCijenaVecihOd(this->max) || count_if(this->veq.begin(), this->veq.end(),std::bind(std::less<int>(), this->max, std::placeholders::_1)) ) throw std::range_error("Prekoracen dozvoljeni opseg cijena");
    return *this;
}



int main ()
{
Berza b(100000);
        b.RegistrirajCijenu(30000);
        b.RegistrirajCijenu(39900);
        b.RegistrirajCijenu(43242);
        b.Ispisi();
        std::cout << "b1 = b++:" << std::endl;
        Berza b1 = b++;
        b1.Ispisi();
        std::cout << "b:" << std::endl;
        b.Ispisi();
	return 0;
}