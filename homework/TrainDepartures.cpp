//TP 2021/2022: Zadaća 4, Zadatak 3

/*This code aims to create a system for managing train departures (Polazak) and a schedule of train departures (RedVoznje). */

#include <initializer_list>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <memory>
#include <iomanip>
#include <stdexcept>
class Polazak {
    std::string s;
    int broj_voza,broj_perona,sat_polaska,minute_polaska,trajanje_voznje,kasnjenje;
    bool brzi_voz;
    public:
    Polazak(std::string odrediste, int broj_voza, int broj_perona, bool brzi_voz,
    int sat_polaska, int minute_polaska, int trajanje_voznje):kasnjenje(0), s(odrediste),broj_voza(broj_voza),broj_perona(broj_perona),brzi_voz(brzi_voz),sat_polaska(sat_polaska),minute_polaska(minute_polaska),trajanje_voznje(trajanje_voznje){if (broj_voza>=10000) throw std::range_error("Prevelik broj voza");if (broj_perona>6 || broj_perona<1) throw std::range_error("Neispravan broj perona");
    if (sat_polaska<0 || minute_polaska<0) throw std::logic_error ("Neispravno vrijeme");};
    void PostaviKasnjenje(int kasnjenje) {Polazak::kasnjenje=kasnjenje;}
    bool DaLiKasni() const {return kasnjenje;}
    int DajTrajanjeVoznje() const {return trajanje_voznje;}
    std::pair<int, int> DajOcekivanoVrijemePolaska() const {int a=sat_polaska,b=minute_polaska+kasnjenje;while (b>=60) {b-=60;a++;}while (a>=24) a-=24;return {a,b};}
    std::pair<int, int> DajOcekivanoVrijemeDolaska() const {int a=sat_polaska,b=minute_polaska+DajTrajanjeVoznje()+kasnjenje;while (b>=60) {b-=60;a++;}while (a>=24) a-=24;return {a,b};}
    void Ispisi() const;
};

void Polazak::Ispisi() const {
    if (!brzi_voz) std::cout<<"Lokalni voz broj ";
    else std::cout<<"Brzi voz broj ";
    if (!DaLiKasni()) std::cout<<broj_voza<<", odrediste "<<s<<", polazi sa perona "<<broj_perona<<" u "<<std::setfill('0') << std::setw(2)<<DajOcekivanoVrijemePolaska().first<<':'<<std::setfill('0') << std::setw(2)<<DajOcekivanoVrijemePolaska().second<<", a na odrediste stize u "<<std::setfill('0') << std::setw(2)<<DajOcekivanoVrijemeDolaska().first
    <<':'<<std::setfill('0') << std::setw(2)<<DajOcekivanoVrijemeDolaska().second<<". Putnicima i voznom osoblju zelimo ugodno putovanje.";
    else std::cout<<broj_voza<<", odrediste "<<s<<", sa predvidjenim vremenom polaska u "<<std::setfill('0') << std::setw(2)<<sat_polaska<<':'<<std::setfill('0') << std::setw(2)<<minute_polaska<<", kasni oko "<<kasnjenje<<" minuta"<<", te ce poci oko "<<std::setfill('0') << std::setw(2)<<DajOcekivanoVrijemePolaska().first<<':'<<std::setfill('0') << std::setw(2)<<DajOcekivanoVrijemePolaska().second
    <<". Ocekuje se da voz stigne na odrediste oko "<<std::setfill('0') << std::setw(2)<<DajOcekivanoVrijemeDolaska().first<<':'<<std::setfill('0') << std::setw(2)<<DajOcekivanoVrijemeDolaska().second<<". Izvinjavamo se putnicima zbog eventualnih neugodnosti.";
    }

class RedVoznje {
    int max_broj_polazaka=0,stvrn=0;
    Polazak **pok=nullptr;
    bool vece(std::pair<int,int> a,std::pair<int,int> b) const {if (a.first<b.first) return true;if (a.first==b.first) return a.second<b.second; return false;}
    public:
    explicit RedVoznje(int max_broj_polazaka): max_broj_polazaka(max_broj_polazaka) {pok=new Polazak*[max_broj_polazaka]{};}
    RedVoznje(std::initializer_list<Polazak> lista_polazaka);
    ~RedVoznje() ;
    RedVoznje(const RedVoznje &red_voznje) ;
    RedVoznje(RedVoznje &&red_voznje) {max_broj_polazaka=red_voznje.max_broj_polazaka;pok=red_voznje.pok;red_voznje.pok=nullptr;red_voznje.max_broj_polazaka=0;stvrn=red_voznje.stvrn;}
    RedVoznje &operator =(const RedVoznje &red_voznje) ;
    RedVoznje &operator =(RedVoznje &&red_voznje);
    void RegistrirajPolazak(std::string odrediste, int broj_voza, bool brzi_voz,
    int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje) ;
    void RegistrirajPolazak(Polazak *polazak) {if (stvrn<max_broj_polazaka)RedVoznje::pok[RedVoznje::stvrn]=polazak;else {throw std::range_error ("Dostignut maksimalni broj polazaka");};stvrn++;}
    int DajBrojPolazaka() const {return stvrn;}
    int DajBrojPolazakaKojiKasne() const {if (!stvrn) return 0;return std::count_if(pok,pok+stvrn,[](Polazak *p) {return p->DaLiKasni();});}
    int DajProsjecnoTrajanjeVoznji() const {double sum=0; for (int i=0; i<stvrn; i++) sum+=pok[i]->DajTrajanjeVoznje();if (!stvrn) return 0;return sum/stvrn;}
    Polazak &DajPrviPolazak() const {if (!stvrn) throw std::domain_error("Nema registriranih polazaka");return **std::min_element(pok,pok+stvrn,[](Polazak *a,Polazak *b) {return a->DajOcekivanoVrijemePolaska()<b->DajOcekivanoVrijemePolaska();});}
    Polazak &DajPosljednjiPolazak() const {if (!stvrn) throw std::domain_error("Nema registriranih polazaka");return **std::max_element(pok,pok+stvrn,[](Polazak *a,Polazak *b) {return a->DajOcekivanoVrijemePolaska()<b->DajOcekivanoVrijemePolaska();});}
    void IsprazniRedVoznje() {for (int i=0; i<stvrn; i++) {delete pok[i];pok[i]=nullptr;stvrn=0;}}
    void Ispisi(int sati, int minute) const ;
};

RedVoznje::~RedVoznje() {
    for (int j=0; j<max_broj_polazaka; j++) delete pok[j];
    delete[] pok;
    pok=nullptr;
    max_broj_polazaka=0;
    stvrn=0;
    }

RedVoznje::RedVoznje(const RedVoznje &red_voznje) {
    pok=new Polazak*[red_voznje.max_broj_polazaka]();
        try {
            for (int i=0; i<red_voznje.stvrn; i++) pok[i]=new Polazak(*red_voznje.pok[i]);
            }
        catch (...) {
            for (int j=0; j<red_voznje.stvrn; j++) delete pok[j];
            delete[] pok;
            pok=nullptr;
            throw;
            }
        max_broj_polazaka=red_voznje.max_broj_polazaka;
        stvrn=red_voznje.stvrn;
    }

RedVoznje &RedVoznje::operator =(const RedVoznje &red_voznje) {
    if (&red_voznje==this) return *this;
    auto pok1=new Polazak*[red_voznje.max_broj_polazaka]();
        try {
            for (int i=0; i<red_voznje.stvrn; i++) pok1[i]=new Polazak(*red_voznje.pok[i]);
            }
        catch (...) {
            for (int j=0; j<red_voznje.stvrn; j++) delete pok1[j];
            delete[] pok1;
            pok1=nullptr;
            throw;
            }
        this->~RedVoznje();
        pok=pok1;
        max_broj_polazaka=red_voznje.max_broj_polazaka;
        stvrn=red_voznje.stvrn;
    return *this;
}

RedVoznje &RedVoznje::operator =(RedVoznje &&red_voznje) {
    if (this==&red_voznje) return *this;
    auto m=max_broj_polazaka;auto p=pok;
    max_broj_polazaka=red_voznje.max_broj_polazaka;
    pok=red_voznje.pok;
    red_voznje.pok=p;
    red_voznje.max_broj_polazaka=m;
    stvrn=red_voznje.stvrn;
    return *this;
    }

RedVoznje::RedVoznje(std::initializer_list<Polazak> lista_polazaka) {
    max_broj_polazaka=lista_polazaka.size(); // mozda skloni ovo 
    pok=new Polazak*[max_broj_polazaka]();
    stvrn=lista_polazaka.size();
    int i=0;
    try {
    for (auto p=lista_polazaka.begin(); i<max_broj_polazaka; i++,p++) pok[i]=new Polazak(*p);
    }
    catch (...) {for (int j=0; j<max_broj_polazaka; j++) delete pok[j];delete[] pok;pok=nullptr;max_broj_polazaka=0;throw;}
}

void RedVoznje::Ispisi(int sati, int minute) const {
    std::sort(pok,pok+stvrn,[](Polazak *a,Polazak *b) {return a->DajOcekivanoVrijemePolaska()<b->DajOcekivanoVrijemePolaska();});
    int i=0;
    for (; i<stvrn; i++) if (vece(std::pair<int,int> (sati,minute),pok[i]->DajOcekivanoVrijemePolaska())) break;
    for (; i<stvrn; i++) {pok[i]->Ispisi();std::cout<<std::endl;}
    }

void RedVoznje::RegistrirajPolazak(std::string odrediste, int broj_voza, bool brzi_voz,
    int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje) {
        if (stvrn<max_broj_polazaka)RedVoznje::pok[RedVoznje::stvrn]=new Polazak(odrediste,broj_voza,broj_perona,brzi_voz,sat_polaska,minute_polaska,trajanje_voznje);
        else throw std::range_error ("Dostignut maksimalni broj polazaka");
        stvrn++;
        }

int main ()
{
       Polazak polazak("Sarajevo", 123, 5, true, 10, 2, 125);
      Polazak polazak2("Bihac", 124, 1, false, 9, 2, 125);
    Polazak polazak3("Mostar", 125, 2, true, 15, 2, 600);
    RedVoznje red{polazak,polazak2,polazak3};
    std::cout<<"Zdravo za informacije o polascima unesite\n1 za Sarajevo\n2 za Bihac\n3za Monstar\n4 za red voznje"<<std::endl;
    int a{};std::cin>>a;
    switch (a) {
        case 1:polazak.Ispisi();break;
        case 2:polazak2.Ispisi();break;
        case 3:polazak3.Ispisi();break;
        case 4:red.Ispisi(0, 0);
    }
	return 0;
}
