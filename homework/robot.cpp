#include <iostream>
#include <limits>
#include <array>
enum class Smjer {Nalijevo, Nadesno};
enum class Pravci {Sjever, Sjeveroistok, Istok, Jugoistok, Jug, Jugozapad, Zapad,
Sjeverozapad};
enum class KodoviGresaka {PogresnaKomanda, NedostajeParametar, SuvisanParametar,
NeispravanParametar};
enum class Komande {Aktiviraj, Deaktiviraj, Nalijevo, Nadesno, Idi, Kraj};

bool Robot(true);

const std::array<char[13],8> smer={"sjever","sjeveroistok","istok","jugoistok","jug","jugozapad","zapad","sjeverozapad"};

void AktivirajRobota() {
    Robot=true;
}
void DeaktivirajRobota() {
    Robot=false;
}
void Rotiraj (Pravci &pravac, Smjer smjer) {
    pravac=Pravci((int(pravac)+int(smjer)+8)%8);
    if (!int(smjer)) pravac=Pravci((int(pravac)+7)%8);
}
void Idi(int &x, int &y, Pravci orijentacija, int korak) {
    if (int(orijentacija)<4 && int(orijentacija)) x+=korak;
    else if (!(int(orijentacija)%4==0)) x-=korak;
    if (int(orijentacija)>2 && int(orijentacija)<6) y-=korak;
    else if(int(orijentacija)!=6 && int(orijentacija)!=2) y+=korak;
}

void IspisiPoziciju(int x, int y, Pravci orijentacija) {
    const std::array<char[10],2> s={"neaktivan","aktivan"};
    int i(0);
    if (Robot) i=1;
    std::cout<<"Robot je "<<s.at(i)<<", nalazi se na poziciji ("<<x<<","<<y<<") i gleda na "<<smer[int(orijentacija)]<<"."<<std::endl;
}

void PrijaviGresku(KodoviGresaka kod_greske) {
    std::array<char[100],4> mistakes={"Nerazumljiva komanda!","Komanda trazi parametar koji nije naveden!","Zadan je suvisan parametar nakon komande!","Parametar komande nije ispravan!"};
    std::cout<<mistakes.at(int(kod_greske))<<std::endl;
    std::cin.clear();
    std::cin.ignore(100,'\n');

}

void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y,Pravci &orijentacija) {
    switch (int(komanda)) {
        case 0: AktivirajRobota();
            break;
        case 1: DeaktivirajRobota();
            break;
        case 2: case 3: Rotiraj(orijentacija,Smjer(int(komanda)-2));
            break;
        case 4: Idi(x, y,orijentacija,parametar);
            break;
        case 5: std::cout<<"Dovidjenja!";
            exit(0);
    }
}

bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske) {
    for (char q={}; q=std::cin.get(),1; ) {
        if (q==' ' || q=='\n') continue;
        if (q=='A') while (q=std::cin.get(),1) {
                    if (q==' ') continue;
                    if (q=='+') komanda=Komande::Aktiviraj;
                    else if (q=='-') komanda=Komande::Deaktiviraj;
                    else {
                        kod_greske=KodoviGresaka::NedostajeParametar;
                        return false;
                    }
                    break;
                }
        else if(!Robot) break;
        else if (q=='D' && std::cin.peek()=='\n') komanda=Komande::Nadesno;
        else if (q=='L' && std::cin.peek()=='\n') komanda=Komande::Nalijevo;
        else if (q=='D' || q=='L') kod_greske=KodoviGresaka::SuvisanParametar;
        else if (q=='I') for (int korak=0,t(1),w(0);q=std::cin.get(),1;) {
            if (q=='-' && !korak) {t*=-1;continue;} /*mozda zatreba + */
            if (q>='0' && q<='9') {
                korak=korak*10+(q-'0')*t;
                w=1;
                continue;
                }
            if (q==' ' && !korak) continue;
            if (w) {
                komanda=Komande::Idi;
                parametar=korak;
                break;
            }
            else {
                if (q=='\0' || q=='\n') kod_greske=KodoviGresaka::NedostajeParametar;
                else kod_greske=KodoviGresaka::NeispravanParametar;
                return false;  
            }
        }
        else if (q=='K') komanda=Komande::Kraj;
        else {
            kod_greske=KodoviGresaka::PogresnaKomanda;
            return false;
        }
        break;
    }
    return true;
}

int main () {
    Pravci orijentacija(Pravci::Sjever);
    int x(0),y(0);
    Komande komanda=Komande::Idi;
    KodoviGresaka kod_greske=KodoviGresaka::NedostajeParametar;
    IspisiPoziciju(x, y,orijentacija);
    for (int parametar=0;1;) {
        std::cout<<"Unesi komandu: "<<std::endl;
        bool t = UnosKomande(komanda, parametar, kod_greske);
        /*std::cin.ignore(100,'\n');
        std::cin.clear();*/
        if (!t) {PrijaviGresku(kod_greske);continue;}
        IzvrsiKomandu(komanda, parametar, x, y, orijentacija);
        IspisiPoziciju(x, y,orijentacija);
    }
    return 0;
}