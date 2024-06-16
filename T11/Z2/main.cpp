#include <iostream>
class StedniRacun {
    double racun;
    public:
    static int ba,bkr;
    StedniRacun() {racun=0;ba++;bkr++;}
    StedniRacun(const StedniRacun &v ) :racun(v.racun) {ba++;bkr++;}
    StedniRacun(double br) {if (br<0) throw std::logic_error("Nedozvoljeno pocetno stanje");racun=br;ba++;bkr++;}
    void Podigni(double br) {if(racun-br<0) throw std::logic_error("Transakcija odbijena");racun-=br;}
    void Ulozi(double br) {Podigni(-br);}
    double DajStanje() const {return racun;}
    ~StedniRacun() {ba--;}
    static int DajBrojKreiranih() {return bkr;}
    static int DajBrojAktivnih() {return ba;}
    void ObracunajKamatu(double kam) {if (kam<=0) throw std::logic_error("Nedozvoljena kamatna stopa");racun+=racun*kam/100;}
};

int StedniRacun::ba=0;int StedniRacun::bkr=0;

int main ()
{
    std::cout<<"Uneai stedni racun :\n";
    int a{};std::cin>>a;
    const StedniRacun r=a;
    std::cout<<"Stanje racuna : "<<r.DajStanje();
	return 0;
}