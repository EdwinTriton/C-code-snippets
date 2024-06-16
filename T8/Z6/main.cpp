//TP 2021/2022: LV 8, Zadatak 6
#include <iostream>
#include <cmath>
#include <memory>
template <typename Tip>
struct Cvor {
    Tip element;
    Cvor<Tip> *veza=nullptr;
};

template <typename TipElemenata>
Cvor<TipElemenata> *KreirajPovezanuListu(TipElemenata zavrsni) {
    Cvor<TipElemenata> *pocetak = nullptr, *prethodni;
    for(;;) {
    TipElemenata broj{};
    std::cin >> broj;
    if(broj == zavrsni) break;
    Cvor<TipElemenata> *novi = new Cvor<TipElemenata>{broj, nullptr}; 
    if(!pocetak) pocetak = novi; 
    else prethodni->veza = novi; 
    prethodni = novi;
    }
    return pocetak;
}
template <typename TipElemenata>
int BrojElemenata(Cvor<TipElemenata> *pocetak) {
    for (int i=0; ; i++,pocetak=pocetak->veza) if (!pocetak) return i;
}
template <typename TipElemenata>
TipElemenata SumaElemenata(Cvor<TipElemenata> *pocetak) {
    for (TipElemenata i{}; ; i+=pocetak->element,pocetak=pocetak->veza) if (!pocetak) return i;
}
template <typename TipElemenata>
int BrojVecihOd(Cvor<TipElemenata> *pocetak, TipElemenata prag) {
    for (int i=0; ;pocetak=pocetak->veza) {
        if (!pocetak) return i;
        if (pocetak->element>prag) i++;
    }
}
template <typename TipElemenata>
void UnistiListu(Cvor<TipElemenata> *pocetak) {
    if (!pocetak) return;
    for (auto q=pocetak->veza;pocetak;) {
        delete pocetak;
        pocetak=q;
        if (pocetak) q = pocetak->veza;
        }
}

int main () {
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    auto stvar=KreirajPovezanuListu<double>(0);
    std::cout<<"U slijedu ima "<<BrojVecihOd(stvar,SumaElemenata(stvar)/BrojElemenata(stvar))<<" brojeva vecih od njihove aritmeticke sredine";
	UnistiListu(stvar);
    return 0;
}
