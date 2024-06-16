#include <iomanip>
#include <cmath>
#include <iostream>
const double pi=4*atan(1);

class Ugao {
    int st,m,se;
    public:
    Ugao(double r = 0) ;
    Ugao(int stepeni, int minute, int sekunde);
    void Postavi(double radijani);
    void Postavi(int stepeni, int minute, int sekunde);
    double DajRadijane() const {return (st+m/60.+se/3600.)*pi/180;}
    void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde) {stepeni=st;minute=m;sekunde=se;}
    int DajStepene() const {return st;}
    int DajMinute() const {return m;}
    int DajSekunde() const {return se;}
    void Ispisi() const {std::cout<<std::setprecision(5)<<std::fixed<<DajRadijane();}
    void IspisiKlasicno() const {std::cout<<DajStepene()<<"deg "<<DajMinute()<<"min "<<DajSekunde()<<"sec";}
    Ugao &SaberiSa(const Ugao &u) {Postavi(st+u.st,m+u.m,se+u.se);return *this;}
    Ugao &PomnoziSa(double x) {Postavi(DajRadijane()*x);return *this;}
    friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2) {Ugao v(u1);return v.SaberiSa(u2);}
    friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x) {Ugao v(u); return v.PomnoziSa(x);}
};

Ugao::Ugao(double r) {
    st=r*180/pi;m=(r*180/pi-int(r*180/pi))*60;se=((r*180/pi-int(r*180/pi))*60-int((r*180/pi-int(r*180/pi))*60))*60.000001;
    while (se<0) {se+=60;m--;}
    while (m<0) {m+=60;st--;}
    while (st<0) {st+=360;}
    while (se>=60) {se-=60;m++;}
    while (m>=60) {m-=60;st++;}
    while (st>=360) {st-=360;}
}

Ugao::Ugao(int stepeni, int minute, int sekunde){
    st=stepeni;se=sekunde;m=minute;
    while (se<0) {se+=60;m--;}
    while (m<0) {m+=60;st--;}
    while (st<0) {st+=360;}
    while (se>=60) {se-=60;m++;}
    while (m>=60) {m-=60;st++;}
    while (st>=360) {st-=360;}
}
void Ugao::Postavi(double r) {
    st=r*180/pi;m=(r*180/pi-int(r*180/pi))*60;se=((r*180/pi-int(r*180/pi))*60-int((r*180/pi-int(r*180/pi))*60))*60.000001;
    while (se<0) {se+=60;m--;}
    while (m<0) {m+=60;st--;}
    while (st<0) {st+=360;}
    while (se>=60) {se-=60;m++;}
    while (m>=60) {m-=60;st++;}
    while (st>=360) {st-=360;}
}
void Ugao::Postavi(int stepeni, int minute, int sekunde) {
    st=stepeni;se=sekunde;m=minute;
    while (se<0) {se+=60;m--;}
    while (m<0) {m+=60;st--;}
    while (st<0) {st+=360;}
    while (se>=60) {se-=60;m++;}
    while (m>=60) {m-=60;st++;}
    while (st>=360) {st-=360;}
}
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