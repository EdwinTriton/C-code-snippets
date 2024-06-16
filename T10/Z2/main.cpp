#include <iostream>
#include <cmath>
#include <iomanip>
const double pi=atan(1)*4;
class Krug {
    double r;
    public:
    explicit Krug(double r) {if (r<=0) throw std::domain_error("Neispravan poluprecnik");Krug::r=r;}//probat bez krug
    void Postavi(double r) {if (r<=0) throw std::domain_error("Neispravan poluprecnik");Krug::r=r;}
    double DajPoluprecnik() const {return r;}
    double DajObim() const {return DajPoluprecnik()*2*pi;}
    double DajPovrsinu() const {return DajPoluprecnik()*DajPoluprecnik()*pi;}
    void Skaliraj (double s) {if (s<=0) throw std::domain_error("Neispravan faktor skaliranja");Krug::r*=s;}
    void Ispisi() const {std::cout<<std::setprecision(5)<<std::fixed<<"R="<<DajPoluprecnik()<<" O="<<DajObim()<<" P="<<DajPovrsinu();}
};

class Valjak {
    Krug baza;
    double visina;
    public:
    Valjak(double r,double h):baza(r) {if (r<=0) throw std::domain_error("Neispravan poluprecnik");if (h<=0) throw std::domain_error("Neispravna visina");visina=h;}
    void Postavi(double r,double h) {if (r<=0) throw std::domain_error("Neispravan poluprecnik");if (h<=0) throw std::domain_error("Neispravna visina");visina=h;baza.Postavi(r);}
    Krug DajBazu() const {return baza;}
    double DajPoluprecnikBaze() const {return DajBazu().DajPoluprecnik();}
    double DajVisinu() const {return visina;}
    double DajPovrsinu() const {return DajBazu().DajPovrsinu()*2+DajBazu().DajObim()*DajVisinu();}
    double DajZapreminu() const {return DajBazu().DajPovrsinu()*DajVisinu();}
    void Skaliraj (double s) {if (s<=0) throw std::domain_error("Neispravan faktor skaliranja");baza.Skaliraj(s);visina*=s;}
    void Ispisi() const {std::cout<<std::setprecision(5)<<std::fixed<<"R="<<DajPoluprecnikBaze()<<" H="<<DajVisinu()<<" P="<<DajPovrsinu()<<" V="<<DajZapreminu();}
};

int main ()
{
    try {
        std::cout<<"Unesi poluprecnik baze valjka i visinu valjka: "<<std::endl;
        double r{},h{};
        std::cin>>r>>h;
        Valjak boi(r,h);
        std::cout<<"Unesi faktor skaliranja valjka: "<<std::endl;
        std::cin>>r;
        boi.Skaliraj(r);
        boi.Ispisi();
    }
    catch (std::domain_error e) {
        std::cout<<e.what();
    }
	return 0;
}