#include <iostream>
#include <string>

class ApstraktniStudent {
    std::string Ime,Prezime;
    int Index,Polozeni;
    double Prosjek;
    public:
    ApstraktniStudent(std::string Ime,std::string Prezime,int Index): Ime(Ime),Prezime(Prezime), Index(Index),Prosjek(5),Polozeni(0) {}
    std::string DajPrezime() const {return Prezime;}
    std::string DajIme() const {return Ime;}
    int DajBrojIndeksa() const {return Index;}
    int DajBrojPolozenih() const {return Polozeni;}
    double DajProsjek() const {return Prosjek;}
    ApstraktniStudent& RegistrirajIspit(int ispit) {if (ispit<5 || ispit>10) throw std::domain_error("Neispravna ocjena");if (ispit==5) return *this;Polozeni++;Prosjek=((Polozeni-1)*Prosjek+ispit)/Polozeni;return *this;}
    ApstraktniStudent& PonistiOcjene() {Prosjek=5;Polozeni=0;return *this;}
    virtual void IspisiPodatke() const=0;
    virtual ApstraktniStudent* DajKopiju() const=0;
    virtual ~ApstraktniStudent() {};
};

class StudentBachelor:public ApstraktniStudent {
    public:
    void IspisiPodatke() const override;
    StudentBachelor(std::string ime,std::string prezime,int indeks) :ApstraktniStudent(ime,prezime,indeks) {};
    ApstraktniStudent* DajKopiju()const override {return new StudentBachelor(*this);}
    ~StudentBachelor() override {}
};

void StudentBachelor::IspisiPodatke() const {
    std::cout<<"Student bachelor studija "<<DajIme()<<' '<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<",\nima prosjek "<<DajProsjek()<<".\n";
}

class StudentMaster: public ApstraktniStudent {
    int Godina;
    public:
    StudentMaster(std::string Ime,std::string Prezime,int Index, int Godina): ApstraktniStudent(Ime,Prezime,Index), Godina(Godina) {}
    void IspisiPodatke() const override {std::cout<<"Student master studija "<<DajIme()<<' '<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<",\nzavrsio bachelor studij godine "<<Godina<<",ima prosjek "<<DajProsjek()<<'.'<<std::endl;}
    ApstraktniStudent* DajKopiju()const override {return new StudentMaster(*this);}
    ~StudentMaster() override {}
};


int main() {
    return 0;
}