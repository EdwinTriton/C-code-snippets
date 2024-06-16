#include <iostream>
#include <cmath>
#include <functional>
#include <fstream>

//sort binary file
template <typename TipElemenata>
void SortirajBinarnuDatoteku(const char ime_datoteke[],std::function<bool(TipElemenata, TipElemenata)> kriterij= std::less<TipElemenata>()) {
    std::fstream tok(ime_datoteke,std::ios::binary | std::ios::in | std::ios::out);
    if (!tok) throw std::logic_error("Datoteka ne postoji");
    tok.seekg(0,std::ios::end);
    int duz_bajt=tok.tellg(),broj_el=tok.tellg()/sizeof(TipElemenata);
    for (int j=0; j<broj_el-1; j++) {
        if (!tok) throw std::logic_error("Problemi u pristupu datoteci");
        for (int i=0; i<broj_el-j-1; i++) {
            tok.seekg(i*int(sizeof(TipElemenata)));
            TipElemenata helpy{};
            TipElemenata rn{};
            tok.read(reinterpret_cast<char*>(&rn), sizeof rn);
            tok.read(reinterpret_cast<char*>(&helpy), sizeof helpy);
            //if (i==broj_el-1 && tok.eof()) tok.clear();
            if (!tok) throw std::logic_error("Problemi u pristupu datoteci");
            if (!kriterij(rn,helpy)) {
                tok.seekp(i*int(sizeof(TipElemenata)));
                tok.write(reinterpret_cast<char*>(&helpy), sizeof helpy);
                tok.write(reinterpret_cast<char*>(&rn), sizeof rn);
                if (!tok) throw std::logic_error("Problemi u pristupu datoteci");
            }
        }
    }
}

struct Student {
char ime[20], prezime[20]; 
int indeks, broj_ocjena;
int ocjene[30]; 
};

int main() {
    int broj_studenata;
    std::cout << "Koliko ima studenata? ";
    std::cin >> broj_studenata;
    std::ofstream studenti("STUDENTI.DAT", std::ios::binary);
    for(int i = 1; i <= broj_studenata; i++) {
        std::cin.ignore(1000, '\n');
        Student neki_student;
        std::cout << "Unesite podatke za " << i << ". studenta:\n";
        std::cout << "Ime: ";
        std::cin.getline(neki_student.ime, sizeof neki_student.ime);
        std::cout << "Prezime: ";
        std::cin.getline(neki_student.prezime, sizeof neki_student.prezime);
        std::cout << "Broj indeksa: ";
        std::cin >> neki_student.indeks;
        std::cout << "Broj ocjena: ";
        std::cin >> neki_student.broj_ocjena;
        for(int j = 0; j < neki_student.broj_ocjena; j++) {
            std::cout << "Ocjena iz " << j + 1 << ". predmeta: ";
            std::cin >> neki_student.ocjene[j];
            }
        studenti.write(reinterpret_cast<char*>(&neki_student), sizeof neki_student);
        }
    studenti.close();
    SortirajBinarnuDatoteku<Student>("STUDENTI.DAT",[](Student a,Student b) {return a.ime[0]<b.ime[0];});
    std::ifstream tok("STUDENTI.DAT", std::ios::binary);
    Student helpex;
    while (tok.read(reinterpret_cast<char*>(&helpex), sizeof helpex)) {
        std::cout<<helpex.ime<<' '<<helpex.prezime<<std::endl;
    }
    return 0;
}