//TP 2021/2022: LV 8, Zadatak 4
#include <iostream>
#include <cmath>
#include <map>
#include <string>

std::string ZamijeniPremaRjecniku(std::string a,std::map<std::string,std::string> mapa) {
    std::string izlaz,h;
    bool razmak=true;
    for (std::string::iterator p=a.begin(); p!=a.end(); p++) {
        if (!(*p>='a' && *p<='z') && razmak) {
            izlaz.push_back(*p);
            continue;
        }
        else if (*p!=' ') {
            h.push_back(*p);
            razmak=false;
            continue;
        }
        if (mapa.count(h)) {
            izlaz+=mapa[h];
            izlaz.push_back(*p);
            h={};
            razmak=true;
            continue;
        }
        else {
            izlaz+=h;
            izlaz.push_back(*p);
            h={};
            razmak=true;
        }
    }
    if (mapa.count(h)) {
            izlaz+=mapa[h];
            h={};
            razmak=true;
        }
        else if (h.size()) {
            izlaz+=h;
            h={};
            razmak=true;
        }
    return izlaz;
}

int main ()
{
    std::map<std::string,std::string> karta {{"kva","sta"},{"kvakva","bilo"},{"kve","je"},{"kvakvakva","danas"}};
    std::cout<<"Unesite recenicu za prijevod: "<<std::endl;
    std::string s;
    std::getline(std::cin,s);
    std::cout<<"Prijevod: "<<ZamijeniPremaRjecniku(s,karta);
	return 0;
}
