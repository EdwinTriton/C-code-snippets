#include <iostream>
#include <cmath>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <sstream>


/*Rational number class*/
class Razlomak {
    long long int up,dn;
    //Biggest common denominator
    long long int NZD(long long int a,long long int b) const;
    //Checks to ensure the format of the rational is correct
    static bool Provjeram(long long int a,long long int b);
    public:
    //giveNumerator
    long long int DajBrojnik() const {return up;}
    //giveDenominator
    long long int DajNazivnik() const {return dn;}
    Razlomak(long long int up,long long int dn=1); 
    Razlomak() {up=0;dn=1;}
    Razlomak(std::initializer_list<long long int> l);
    Razlomak operator+(const Razlomak &r) const;
    Razlomak operator-(const Razlomak &r) const;
    const Razlomak& operator+() const {return *this;}
    Razlomak operator-() const {return Razlomak(-up,dn);}
    Razlomak operator*(const Razlomak &r) const;
    Razlomak operator/(const Razlomak &r2) const;
    friend std::ostream &operator<<(std::ostream &tok ,const Razlomak &r) ;
    friend std::istream &operator>>(std::istream &tok ,Razlomak &r) ;
    inline Razlomak& operator+=(const Razlomak &r) {return *this=*this+r;}
    inline Razlomak& operator-=(const Razlomak &r) {return *this=*this-r;}
    inline Razlomak& operator*=(const Razlomak &r) {return *this=*this*r;}
    inline Razlomak& operator/=(const Razlomak &r) {return *this=*this/r;}
    Razlomak& operator++() {return *this=*this+Razlomak(1);} //moze efikasnije ++ bez sabiranje
    Razlomak& operator--() {return *this=*this-Razlomak(1);}
    Razlomak operator++(int) {Razlomak helper=*this;*this=*this+Razlomak(1);return helper;}
    Razlomak operator--(int) {Razlomak helper=*this;*this=*this-Razlomak(1);return helper;}
    operator long double() const {return static_cast<long double>(DajBrojnik())/DajNazivnik();}
    friend bool operator!=(const Razlomak &r1,const Razlomak &r2) {return double(r1)!=double(r2);}
    friend bool operator==(const Razlomak &r1,const Razlomak &r2) {return double(r1)==double(r2);}
    friend bool operator<(const Razlomak &r1,const Razlomak &r2) {return double(r1)<double(r2);}
    friend bool operator>(const Razlomak &r1,const Razlomak &r2) {return double(r1)>double(r2);}
    friend bool operator<=(const Razlomak &r1,const Razlomak &r2) {return double(r1)<=double(r2);}
    friend bool operator>=(const Razlomak &r1,const Razlomak &r2) {return double(r1)>=double(r2);}
};

long long int Razlomak::NZD(long long int a,long long int b) const {
    if (!b) return a;
    return NZD(b, a%b);
}

bool Razlomak::Provjeram(long long int x,long long int y) {
    long long int m=std::numeric_limits<long long int>::min(),M=std::numeric_limits<long long int>::max();
    return (y>=0 && (x<m/y || x>M/y) || y<0 && (x==m || -x>M/(-y) || -x<m/(-y) ));
}

Razlomak::Razlomak(long long int up,long long int dn) {
    if (!dn) throw std::logic_error("Nekorektan razlomak");
    long long int c=NZD(up,dn);
    if (dn/c<0 && up/c>=0) {dn*=-1;up*=-1;}
    Razlomak::up=up/c;
    Razlomak::dn=dn/c;
}

Razlomak::Razlomak(std::initializer_list<long long int> l) {
    if (!l.size()) {
        up=0;
        dn=1;
    }
    else if (l.size()==1) {
        this->up=Razlomak(*l.begin()).DajBrojnik();
        this->dn=Razlomak(*l.begin()).DajNazivnik();
        }
    else if (l.size()==2) {
        this->up=Razlomak(*l.begin(),*(l.begin()+1)).DajBrojnik();
        this->dn=Razlomak(*l.begin(),*(l.begin()+1)).DajNazivnik();
        }
    else throw std::logic_error("Nekorektan razlomak");
}

Razlomak Razlomak::operator+(const Razlomak &r2) const{
    long long int r=(NZD(this->DajNazivnik(),r2.DajNazivnik()));
    if (Provjeram((this->DajNazivnik()/r),r2.DajBrojnik()) || Provjeram((this->DajBrojnik()/r),r2.DajNazivnik()) || r2.DajBrojnik()>=0 && this->DajBrojnik()*(r2.DajNazivnik()/r)>std::numeric_limits<long long int>::max()-(this->DajNazivnik()/r)*r2.DajBrojnik() || r2.DajBrojnik()<0 &&this->DajBrojnik()*(r2.DajNazivnik()/r)<std::numeric_limits<long long int>::min()-(this->DajNazivnik()/r)*r2.DajBrojnik())
    throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    return Razlomak(this->DajBrojnik()*(r2.DajNazivnik()/r)+(this->DajNazivnik()/r)*r2.DajBrojnik(),(r2.DajNazivnik()/r)*this->DajNazivnik());
}

Razlomak Razlomak::operator-(const Razlomak &r2) const{ //provjeri ovo oduzimanje malo sus
    long long int r=(NZD(this->DajNazivnik(),r2.DajNazivnik()));
    if (Provjeram((this->DajNazivnik()/r),r2.DajBrojnik()) || Provjeram((this->DajBrojnik()),r2.DajNazivnik()/r) || r2.DajBrojnik()<0 && this->DajBrojnik()*(r2.DajNazivnik()/r)>std::numeric_limits<long long int>::max()+(this->DajNazivnik()/r)*r2.DajBrojnik() || r2.DajBrojnik()>=0 &&this->DajBrojnik()*(r2.DajNazivnik()/r)<std::numeric_limits<long long int>::min()+(this->DajNazivnik()/r)*r2.DajBrojnik())
    throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    return Razlomak(this->DajBrojnik()*(r2.DajNazivnik()/r)-(this->DajNazivnik()/r)*r2.DajBrojnik(),(r2.DajNazivnik()/r)*this->DajNazivnik());
}

Razlomak Razlomak::operator*(const Razlomak &r2) const {
    const Razlomak& r1=*this;
    long long int s=NZD(r1.DajBrojnik(),r2.DajNazivnik()),t=NZD(r2.DajBrojnik(),r1.DajNazivnik()),m=std::numeric_limits<long long int>::min(),M=std::numeric_limits<long long int>::max();
    if (r2.DajBrojnik()/t>=0 && (r1.DajBrojnik()/s< m/(r2.DajBrojnik()/t) || r1.DajBrojnik()/s>M/(r2.DajBrojnik()/t))  ||r2.DajBrojnik()/t<0 && (r1.DajBrojnik()/s==m || -r1.DajBrojnik()/s>M/(-r2.DajBrojnik()/t) || -r1.DajBrojnik()/s<m/(-r2.DajBrojnik()/t)) )
    throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    if (r2.DajNazivnik()/s>=0 && (r1.DajNazivnik()/t< m/(r2.DajNazivnik()/s) || r1.DajNazivnik()/t>M/(r2.DajNazivnik()/s))  ||r2.DajNazivnik()/s<0 && (r1.DajNazivnik()/t==m || -r1.DajNazivnik()/t>M/(-r2.DajNazivnik()/s) || -r1.DajNazivnik()/t<m/(-r2.DajNazivnik()/s)) ) 
    throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    return Razlomak( (r1.DajBrojnik()/s)*(r2.DajBrojnik()/t) , (r1.DajNazivnik()/t)*(r2.DajNazivnik()/s) );
}

Razlomak Razlomak::operator/(const Razlomak &r2) const { //moze efikasnije ako rucno 
    if (!r2.DajNazivnik()) throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    return (*this)*Razlomak(r2.DajNazivnik(),r2.DajBrojnik());
}

std::ostream &operator<<(std::ostream &tok ,const Razlomak &r) {
    if (r.DajNazivnik()!=1)
    return tok<<r.DajBrojnik()<<'/'<<r.DajNazivnik();
    return tok<<r.DajBrojnik();
}

std::istream &operator>>(std::istream &tok ,Razlomak &r) {
    long long int a=0,b=0;
    tok>>a;
    if (tok.peek()!='/' && ((tok.peek()=='\n' || tok.peek()=='\t' || tok.peek()=='\0' || tok.peek()==' ' ) && tok || tok.peek()==EOF)) r=Razlomak(a);
    else if (tok.get() && (tok.peek()>='0' && tok.peek()<='9') && tok>>b && (tok.peek()=='\n' || tok.peek()=='\t' || tok.peek()=='\0' || tok.peek()==' ' || tok.peek()==EOF)) r=Razlomak(a,b);
    else tok.setstate(std::ios::badbit);
    return tok;
}




int main ()
{

	return 0;
}
