#include <iostream>
#include <cmath>
#include <iomanip>
const double pi=4*atan(1);

class Ugao {
    double r;
    public:
    Ugao(double radijani = 0) {r=radijani;while (r>2*pi) {r-=2*pi;}while (r<0) {r+=2*pi;}}
    Ugao(int stepeni, int minute, int sekunde) {r=(stepeni+minute/60.+sekunde/3600.)*pi/180;while (r>=2*pi-0.0001) {r-=2*pi;}while (r<0) {r+=2*pi;}}
    void Postavi(double radijani) {r=radijani;while (r>2*pi) {r-=2*pi;}while (r<0) {r+=2*pi;}}
    void Postavi(int stepeni, int minute, int sekunde) {r=(stepeni+minute/60.+sekunde/3600.)*pi/180;while (r>2*pi) {r-=2*pi;}while (r<0) {r+=2*pi;}}
    double DajRadijane() const {return r;}
    void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde) {stepeni=r*180/pi;minute=(r*180/pi-stepeni)*60;sekunde=((r*180/pi-stepeni)*60-minute)*60;}
    int DajStepene() const {if (r*180/pi>=359.99) return 0;return r*180/pi;}
    int DajMinute() const {return (r*180/pi-int(r*180/pi))*60;}
    int DajSekunde() const {if (((r*180/pi-int(r*180/pi))*60-int((r*180/pi-int(r*180/pi))*60))*60.000001>=60-0.001) return 59;return ((r*180/pi-int(r*180/pi))*60-int((r*180/pi-int(r*180/pi))*60))*60.000001;}
    void Ispisi() const {std::cout<<std::setprecision(5)<<std::fixed<<r;}
    void IspisiKlasicno() const {std::cout<<DajStepene()<<"deg "<<DajMinute()<<"min "<<DajSekunde()<<"sec";}
    Ugao &SaberiSa(const Ugao &u) {Postavi((DajRadijane()+u.DajRadijane()));return *this;}
    Ugao &PomnoziSa(double x) {Postavi(r*x);return *this;}
    friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2) {Ugao v(u1);return v.SaberiSa(u2);}
    friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x) {Ugao v(u); return v.PomnoziSa(x);}
};

int main ()
{
    Ugao u(50, 25, 12);
    u.SaberiSa(1).IspisiKlasicno();
    Ugao i;
    std::cout<<"Unesi prvi ugao u radijanima: \n";
    double a=0;std::cin>>a;
    Ugao prvi(a);
    std::cout<<"Unesi drugi ugao u stepenima(stepeni,minute,sekunde): \n";
    int x=0,y=0,z=0;
    std::cin>>x>>y>>z;
    Ugao drugi(x,y,z);
    std::cout<<"Zbir ova dva ugla je: ";
    ZbirUglova(prvi,drugi).IspisiKlasicno();
    std::cout<<"\nUnesi skalar da se pomnozi sa prvim uglom: \n";
    std::cin>>a;
    prvi.PomnoziSa(a).Ispisi();
	return 0;
}