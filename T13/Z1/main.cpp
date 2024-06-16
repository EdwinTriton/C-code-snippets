#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
const double pi=atan(1)*4;

class Lik{
    public:
    virtual void IspisiSpecificnosti() {};
    virtual double DajPovrsinu() {return -1;};
    virtual double DajObim() {return -1;};
    virtual ~Lik() {};
    void Ispisi() {IspisiSpecificnosti();std::cout<<"Obim: "<<DajObim()<<" Povrsina: "<<DajPovrsinu()<<std::endl;}
};

class Krug: public Lik {
    double r=0;
    public:
    Krug(double x) : r(x) {if (x<=0) throw std::domain_error("Neispravni parametri");}
    void IspisiSpecificnosti() override {std::cout<<"Krug poluprecnika "<<r<<std::endl;}
    double DajPovrsinu() override {return r*r*pi;}
    double DajObim() override {return 2*r*pi;}
};

class Pravougaonik: public Lik {
    double a=0,b=0;
    public:
    Pravougaonik(double a,double b) :a(a), b(b) {if(a<=0 || b<=0) throw std::domain_error("Neispravni parametri");}
    void IspisiSpecificnosti() override {std::cout<<"Pravougaonik sa stranicama duzine "<<a<<" i "<<b<<std::endl;}
    double DajPovrsinu() override {return a*b;}
    double DajObim() override {return 2*a+2*b;}
};

class Trougao: public Lik {
    double a,b,c;
    public:
    Trougao(double a,double b,double c) :a(a),b(b),c(c) {if (a<=0 || b<=0 || c<=0 || !(a+b>c && b+c>a && a+c>b)) throw std::domain_error("Neispravni parametri");}
    double DajObim() override {return a+b+c;}
    double DajPovrsinu() override {double s=(a+b+c)/2;return sqrt(s*(s-a)*(s-b)*(s-c));}
    void IspisiSpecificnosti() override {std::cout<<"Trougao sa stranicama duzine "<<a<<", "<<b<<" i "<<c<<std::endl;}
};

int main ()
{
    std::cout<<"Koliko zelite likova: ";
    int n=0;std::cin>>n;
    std::vector<std::shared_ptr<Lik> > cray(n);std::cin.get();
    for (int i=0,l=0,t=0,d=0; i<n; i++,l=0,t=0,d=0) {
        std::cout<<"Lik "<<i+1<<": ";double b=0;
        std::vector<double> veq;
        char c=0;
        while (c=std::cin.get(),c!='\n' && c!='\0') {
            if (!l && (c=='K' || c=='T' || c=='P')) l=c;
            else if (l && c==',') {
                d=0;
                if (l=='K') b=0;
                if (!b) {t=1;break;}
                veq.push_back(b);
                b=0;
                continue;
                }
            else if (l && c=='.') d=1;
            else if (l && c>='0' && c<='9' && !d) b=b*10+c-'0';
            else if (l && c>='0' && c<='9' && d) {
                b=b*10+c-'0';b/=10;
                }
            else {
                t=1;
                break;
                }
        }
        if (t || !b) {
            i--;
            std::cout << "Pogresni podaci, ponovite unos!\n";
            while (c!='\n') c=std::cin.get();
            continue;
            }
        veq.push_back(b);
        if (l=='K') cray.at(i)=std::make_shared<Krug>(veq.at(0));
        else if (l=='P') cray.at(i)=std::make_shared<Pravougaonik>(veq.at(0),veq.at(1));
        else try {cray.at(i)=std::make_shared<Trougao>(veq.at(0),veq.at(1),veq.at(2));}
        catch (...) {
            i--;
            std::cout << "Pogresni podaci, ponovite unos!\n";
            while (c!='\n') c=std::cin.get();
            }
    }
    for (auto p: cray) p->Ispisi();
	return 0;
}