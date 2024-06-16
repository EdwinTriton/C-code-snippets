#include <iostream>
#include <vector>
#include <algorithm>
class ApstraktniStudent{
    std::string ime,prezime;
    int indeks,pol;
    double prosjek;
    public:
    ApstraktniStudent(std::string ime,std::string prezime,int indeks) : ime(ime), prezime(prezime) ,indeks(indeks), pol(0), prosjek(5) {};
    std::string DajIme() const {return ime;}
    std::string DajPrezime() const {return prezime;}
    int DajBrojIndeksa() const {return indeks;}
    int DajBrojPolozenih() const {return pol;}
    double DajProsjek() const {return prosjek;}
    void RegistrirajIspit(int ispit) {if (ispit<5 || ispit>10) throw std::domain_error("Neispravna ocjena");if (ispit==5) return;pol++;prosjek=(prosjek*(pol-1)+ispit)/pol;}
    void PonistiOcjene() {pol=0;prosjek=5;}
    virtual void IspisiPodatke() const =0;
    virtual ApstraktniStudent *DajKopiju() const=0;
    virtual ~ApstraktniStudent() {};
};

class StudentBachelor : public ApstraktniStudent {
    public:
    StudentBachelor(std::string ime,std::string prezime,int indeks) :ApstraktniStudent(ime,prezime,indeks) {};
    void IspisiPodatke() const override {std::cout<<"Student bachelor studija "<<DajIme()<<' '<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<",\nima prosjek "<<DajProsjek()<<'.'<<std::endl;}
    StudentBachelor *DajKopiju() const override {return new StudentBachelor(*this);}

};

class StudentMaster : public ApstraktniStudent {
    int godina;
    public:
    StudentMaster(std::string ime,std::string prezime,int indeks, int godina) :ApstraktniStudent(ime,prezime,indeks), godina(godina) {};
    void IspisiPodatke() const override {std::cout<<"Student master studija "<<DajIme()<<' '<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<",\nzavrsio bachelor studij godine "<<godina<<",ima prosjek "<<DajProsjek()<<'.'<<std::endl;}
    StudentMaster *DajKopiju() const override {return new StudentMaster(*this);}
};

class Student {
    ApstraktniStudent *p=nullptr;
    public:
    Student(const ApstraktniStudent &s) : p(s.DajKopiju()) {};
    ~Student() {delete p;p=nullptr;}
    Student() {};
    std::string DajIme() const {return p->DajIme();}
    std::string DajPrezime() const {return p->DajPrezime();}
    int DajBrojIndeksa() const {return p->DajBrojIndeksa();}
    int DajBrojPolozenih() const {return p->DajBrojPolozenih();}
    double DajProsjek() const {return p->DajProsjek();}
    void RegistrirajIspit(int ispit) {p->RegistrirajIspit(ispit);}
    void PonistiOcjene() {p->PonistiOcjene();}
    void IspisiPodatke() {p->IspisiPodatke();}
    ApstraktniStudent *DajKopiju() const {return p->DajKopiju();}
    void operator=(const Student &s) {delete this->p;this->p=s.p->DajKopiju();}
    void operator=(Student &&s) {std::swap(this->p,s.p);}
    Student(Student &&s) : p(s.p) {s.p=nullptr;}
    Student(Student &s) :p(s.p->DajKopiju()) {};
    void operator=(const ApstraktniStudent &s) {delete this->p;this->p=s.DajKopiju();}
};

int main ()
{
	return 0;
}