//TP 2021/2022: Zadaća 3, Zadatak 4
/*The provided program takes a list of children's names and divides them into a specified number of teams*/

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <set>
#include <list>
#include <cmath>
#include <algorithm>

int main ()
{
    std::vector<std::set<std::string> > Razvrstavanje(const std::vector<std::string> &imena_str,int br_teams);
    std::cout<<"Unesite broj djece: \n";
    int x{};std::cin>>x;
    char q='t';q=std::cin.get();
    std::cout<<"Unesite imena djece: "<<std::endl;
    std::vector<std::string> imena;
    for (int i=0; i<x; i++) {
        std::string prva_pomoc;
        std::getline(std::cin,prva_pomoc);
        if (!prva_pomoc.size()) std::getline(std::cin,prva_pomoc);
        imena.push_back(prva_pomoc);
    }
    std::cout<<"Unesite broj timova: \n";
    std::cin>>x;
    try {
    std::vector<std::set<std::string> > teams=Razvrstavanje(imena, x);
    for (int i=0; i<teams.size(); i++) {
        std::cout<<"Tim "<<i+1<<": ";
        for (std::set<std::string>:: iterator p=teams.at(i).begin(); p!=teams.at(i).end(); p++) {
            std::cout<<*p;
            auto q=p;q++;
            if (q!=teams.at(i).end()) std::cout<<", ";
        }
        std::cout<<std::endl;
    }
    }
    catch (std::logic_error e) {std::cout<<"Izuzetak: "<<e.what();}
	return 0;
}
std::vector<std::set<std::string> > Razvrstavanje(const std::vector<std::string> &imena_str,int br_teams) {
    if (br_teams<1 || br_teams>imena_str.size()) throw std::logic_error("Razvrstavanje nemoguce");
    std::list<std::string> imena;
    for (auto ime:imena_str) imena.push_back(ime);
    std::vector<std::set<std::string> > izlaz(br_teams);//
    std::list<std:: string>::iterator p=imena.begin();
    int br_slova=0;
    for (int i=0; i<br_teams; i++) {//std::cout<<std::endl<<"!!!"<<int (imena_str.size()/br_teams)<<"!!!"<<int(imena_str.size()%br_teams>i); 
        int br_cln=int (imena_str.size()/br_teams) + int(imena_str.size()%br_teams>i);//skloni int zagrade kod prvog
        for (int j=0; j<br_cln; j++) {
            /*if (p==imena.end()) p=imena.begin();
            if (!j && !i) izlaz.at(i).insert(*p);*/
            for (int k=0; k<br_slova; k++,p++) if (p==imena.end()) {p=imena.begin();}
            if (p==imena.end()) {p=imena.begin();}
            br_slova=std::count_if(p->begin(),p->end(),[](char c)->bool {return (c>='a' && c<='z' || c>='A' && c<='Z' || c>='0' && c<='9');});
            if (!br_slova) std::cout<<"ILEGALAN POTEZ";
            izlaz.at(i).insert(*p);
            p=imena.erase(p);br_slova--;
        }
    }
    return izlaz;
}