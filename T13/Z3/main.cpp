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

class Fakultet {
    std::vector<ApstraktniStudent *> studenti;
    public:
    Fakultet() {};
    ~Fakultet() {for (ApstraktniStudent *a :studenti) {delete a;a=nullptr;}}
    Fakultet(const Fakultet &fax) {for (int i=0; i<fax.studenti.size(); i++) studenti.push_back(fax.studenti.at(i)->DajKopiju());}
    Fakultet(Fakultet &&fax) {studenti=std::move(fax.studenti);}
    Fakultet operator=(const Fakultet &fax);
    Fakultet operator=(Fakultet &&fax);
    ApstraktniStudent& operator[](int index);
    const ApstraktniStudent& operator[](int index) const;
    void UpisiStudenta(std::string name, std::string sur,int x) {bool t=0;try {(*this)[x];t=1;} catch (...) {studenti.push_back(new StudentBachelor(name,sur,x));}if (t) throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");}
    void UpisiStudenta(std::string name, std::string sur,int x, int y) {bool t=0;try {(*this)[x];t=1;} catch (...) {studenti.push_back(new StudentMaster(name,sur,x,y));}if (t) throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");}
    void ObrisiStudenta(int x) ;
    void IspisiSveStudente() const ;
};

Fakultet Fakultet::operator=(const Fakultet &fax) {
    if (&fax==this) return *this;
    int b=fax.studenti.size(), a=this->studenti.size();
    for (auto s :this->studenti) delete s;
    this->studenti.resize(b);
    for (int i=0; i<b; i++) this->studenti.at(i)=fax.studenti.at(i)->DajKopiju();
    return *this;
}

Fakultet Fakultet::operator=(Fakultet &&fax) {
    if (&fax==this) return *this;
    for (auto s :this->studenti) delete s;
    this->studenti=std::move(fax.studenti);
    return *this;
}

ApstraktniStudent& Fakultet::operator[](int index) {
    int i;
    for (i=0; i<this->studenti.size(); i++) if (index==this->studenti.at(i)->DajBrojIndeksa()) break;
    if (i==this->studenti.size()) throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
    return *this->studenti.at(i);
}

void Fakultet::ObrisiStudenta(int x) {
    int i;
    for (i=0; i<this->studenti.size(); i++) {
        if (this->studenti.at(i)->DajBrojIndeksa() == x) break;
    }
    if (i == this->studenti.size()) throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
    delete this->studenti.at(i);
    if (this->studenti.size() == 1) {this->studenti={};return;}
    this->studenti.at(i)=this->studenti.at(this->studenti.size()-1);
    this->studenti.resize(this->studenti.size()-1);
}
const ApstraktniStudent& Fakultet::operator[](int index) const {
    int i;
    for (i=0; i<this->studenti.size(); i++) if (index==this->studenti.at(i)->DajBrojIndeksa()) break;
    if (i==this->studenti.size()) throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
    return *this->studenti.at(i);
}

void Fakultet::IspisiSveStudente() const {
    std::vector<ApstraktniStudent *> vec=this->studenti;
    std::sort(vec.begin(),vec.end(),[](ApstraktniStudent* b,ApstraktniStudent* a)->bool {return a->DajProsjek()<b->DajProsjek() || a->DajProsjek()==b->DajProsjek() && a->DajBrojIndeksa()>b->DajBrojIndeksa();});
    for (int i=0; i<vec.size(); i++) vec.at(i)->IspisiPodatke();
}

int main ()
{
    std::cout<<"Unesite broj studenata na fakultet :\n";
    int n=0;std::cin>>n;
    Fakultet fake;
    for (int i=0,q=0; i<n; i++) {
        std::string a,b;
        std::cout<<"Unesi ime i prezime\n";
        std::cin>>a>>b;
        std::cout<<"Unesi broj indeksa";
        std::cin>>q;
        fake.UpisiStudenta(a,b,q);
    }
	return 0;
}