#include <iostream>
#include <stdexcept>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory>

/*The provided C++ program defines a class Kugla (Sphere) that encapsulates the properties
and operations related to a sphere in 3D space*/

const double e=0.0000000001;
const double pi=4*atan(1);
class Kugla {
double x,y,z,r;
  public:
  explicit Kugla(double r = 0) {x=y=z=0;Kugla::r=r;}
Kugla(double x, double y, double z, double r = 0) {Kugla::x=x;Kugla::y=y;Kugla::z=z;Kugla::r=r;}
explicit Kugla(const std::tuple<double, double, double> &centar, double r = 0) {Kugla::x=std::get<0>(centar);Kugla::y=std::get<1>(centar);Kugla::z=std::get<2>(centar);Kugla::r=r;}
double DajX() const;
double DajY() const;
double DajZ() const;
std::tuple<double, double, double> DajCentar() const;
double DajPoluprecnik() const;
double DajPovrsinu() const;
double DajZapreminu() const;
Kugla &PostaviX(double x);
Kugla &PostaviY(double y);
Kugla &PostaviZ(double z);
Kugla &PostaviCentar(double x, double y, double z);
Kugla &PostaviCentar(const std::tuple<double, double, double> &centar);
Kugla &PostaviPoluprecnik(double r);
void Ispisi() const;
void Transliraj(double delta_x, double delta_y, double delta_z);
friend bool DaLiSuIdenticne(const Kugla &k1, const Kugla &k2);
friend bool DaLiSuPodudarne(const Kugla &k1, const Kugla &k2);
friend bool DaLiSuKoncentricne(const Kugla &k1, const Kugla &k2);
friend bool DaLiSeDodirujuIzvana(const Kugla &k1, const Kugla &k2);
friend bool DaLiSeDodirujuIznutra(const Kugla &k1, const Kugla &k2);
friend bool DaLiSePreklapaju(const Kugla &k1, const Kugla &k2);
friend bool DaLiSeSijeku(const Kugla &k1, const Kugla &k2);
bool DaLiSadrzi(const Kugla &k) const;
friend double RastojanjeCentara(const Kugla &k1, const Kugla &k2);
};

int main() {

    bool DaLiSeSijeku(const Kugla &k1, const Kugla &k2);
  std::cout<<"Unesite broj kugla: ";
  int n{};std::cin>>n;
  std::vector<std::shared_ptr<Kugla> > vektor(n),v(n);
  for (double i=0,x=0,y=0,z=0,r=0; i<n; i++) {
    std::cout<<"Unesite centar "<<i+1<<". kugle: ";
    std::cin>>x>>y>>z;
    if ((!std::cin  )) {std::cin.clear();std::cin.ignore(100,'\n');i--;std::cout<<"Ilegalan centar\n";continue;}
    std::cout<<"Unesite poluprecnik "<<i+1<<". kugle: ";
    std::cin>>r;
    if ((!std::cin || r<0)) {std::cin.clear();std::cin.ignore(100,'\n');i--;std::cout<<"Ilegalan poluprecnik\n";continue;}
    vektor.at(i)=std::make_shared<Kugla>(x,y,z,r); 
  }
  std::cout<<"Unesite parametre translacije (delta_x,delta_y,delta_z): ";
  double dx=0,dy=0,dz=0;
  std::cin>>dx>>dy>>dz;
  std::transform(vektor.begin(),vektor.end(),v.begin(),[dx,dy,dz](std::shared_ptr<Kugla> q) {q->Transliraj(dx,dy,dz);return q;});
  std::cout<<"Kugle nakon obavljenje transformacije imaju sljedece vrijednosti: \n";
  std::sort(v.begin(),v.end(),[](std::shared_ptr<Kugla> a,std::shared_ptr<Kugla> b)->bool {return a->DajZapreminu()<b->DajZapreminu();});
  std::for_each(v.begin(), v.end(), [](std::shared_ptr<Kugla> a) {a->Ispisi();});
  std::cout<<"Kugla sa najvecom povrsinom je: ";
  (*std::max_element(v.begin(), v.end(), [](std::shared_ptr<Kugla> a,std::shared_ptr<Kugla> b) {return a->DajPovrsinu()<b->DajPovrsinu();} ))->Ispisi();
  bool t=true;
  for (int j=0; j<n; j++)
  for (int i=j; i<n; i++) {
    if ( j!=i && DaLiSeSijeku(*v.at(i),*v.at(j)) ) {
        t=false;
        std::cout<<"Presjecaju se kugle: ";
        v.at(j)->Ispisi();
        v.at(i)->Ispisi();
    }
  }
  if (t) std::cout<<"Ne postoje kugle koje se presjecaju!";
  return 0;
}

bool Isti (double a,double b) {return fabs(a-b)<e;}

double Kugla::DajX() const{
  return x;
}
double Kugla::DajY() const {
  return y;
}
double Kugla::DajZ() const {
  return z;
}
std::tuple<double, double, double> Kugla::DajCentar() const{
  return {x,y,z};
}
double Kugla::DajPoluprecnik() const {
    return r;
}
double Kugla::DajPovrsinu() const {
  return 4*pi*r*r;
}
double Kugla::DajZapreminu() const {
  return 4*pi*r*r*r/3;
}
Kugla &Kugla::PostaviX(double x) {
    Kugla::x=x;
    return *this;
}
Kugla &Kugla::PostaviY(double x) {
    Kugla::y=x;
    return *this;
}
Kugla &Kugla::PostaviZ(double x) {
    Kugla::z=x;
    return *this;
}
Kugla &Kugla::PostaviCentar(double x, double y, double z) {
    Kugla::x=x;Kugla::y=y;Kugla::z=z;
    return *this;
}
Kugla &Kugla::PostaviCentar(const std::tuple<double, double, double> &centar) {
    Kugla::x=std::get<0>(centar);
    Kugla::y=std::get<1>(centar);
    Kugla::z=std::get<2>(centar);
    return *this;
}
Kugla &Kugla::PostaviPoluprecnik(double r) {
    Kugla::r=r;
    return *this;
}
void Kugla::Ispisi() const {
    std::cout<<"{("<<DajX()<<','<<DajY()<<','<<DajZ()<<"),"<<DajPoluprecnik()<<'}'<<std::endl;
}
void Kugla::Transliraj(double delta_x, double delta_y, double delta_z) {
    Kugla::x+=delta_x;
    Kugla::y+=delta_y;
    Kugla::z+=delta_z;
}

bool DaLiSuIdenticne(const Kugla &k1, const Kugla &k2) {
    return (Isti(k1.DajPoluprecnik(),k2.DajPoluprecnik()) && Isti(k1.DajX(),k2.DajX()) && Isti(k1.DajY(),k2.DajY()) && Isti(k1.DajZ(),k2.DajZ()));
}

bool DaLiSuPodudarne(const Kugla &k1, const Kugla &k2) {
    return (Isti(k1.DajPoluprecnik(),k2.DajPoluprecnik()));
}

bool DaLiSuKoncentricne(const Kugla &k1, const Kugla &k2) {
    return Isti(k1.DajX(),k2.DajX()) && Isti(k1.DajY(),k2.DajY()) && Isti(k1.DajZ(),k2.DajZ());
}

double Duzina(double a,double b,double c,double x,double y,double z) {
    return sqrt((a-x)*(a-x)+(b-y)*(b-y)+(c-z)*(c-z));
}

bool DaLiSeDodirujuIzvana(const Kugla &k1, const Kugla &k2) {
    return Isti(Duzina(k1.DajX(),k1.DajY(),k1.DajZ(),k2.DajX(),k2.DajY(),k2.DajZ()),fabs(k1.DajPoluprecnik()-k2.DajPoluprecnik()));
}

bool DaLiSeDodirujuIznutra(const Kugla &k1, const Kugla &k2) {
    return Isti(Duzina(k1.DajX(),k1.DajY(),k1.DajZ(),k2.DajX(),k2.DajY(),k2.DajZ()),fabs(k1.DajPoluprecnik()-k2.DajPoluprecnik()));
}

bool DaLiSePreklapaju(const Kugla &k1, const Kugla &k2) {
    return Duzina(k1.DajX(),k1.DajY(),k1.DajZ(),k2.DajX(),k2.DajY(),k2.DajZ())<k1.DajPoluprecnik() +k2.DajPoluprecnik();
}
bool Kugla::DaLiSadrzi(const Kugla &k) const {
    double v{},m{};
    {v=DajPoluprecnik();m=k.DajPoluprecnik();}
    
    return Duzina(DajX(),DajY(),DajZ(),k.DajX(),k.DajY(),k.DajZ())+m<v || Isti(Duzina(DajX(),DajY(),DajZ(),k.DajX(),k.DajY(),k.DajZ())+m,v);
}
bool DaLiSeSijeku(const Kugla &k1, const Kugla &k2) {
    double m=k1.DajPoluprecnik(),v=k2.DajPoluprecnik();
    if (k1.DajPoluprecnik()>k2.DajPoluprecnik()) {m=k2.DajPoluprecnik();v=k1.DajPoluprecnik();}
    return DaLiSePreklapaju(k1,k2) && Duzina(k1.DajX(),k1.DajY(),k1.DajZ(),k2.DajX(),k2.DajY(),k2.DajZ())+m>v;
}