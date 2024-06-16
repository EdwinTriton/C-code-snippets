//TP 2021/2022: LV 8, Zadatak 1
#include <iostream>
#include <cmath>
#include <iomanip>
struct Vrijeme {
    int sati,minute,sekunde;
};
int main ()
{
    try{
    Vrijeme v1{},v2{};
    void IspisiVrijeme(Vrijeme v),TestirajVrijeme(Vrijeme v);
    Vrijeme SaberiVrijeme(Vrijeme v,Vrijeme q);
    std::cout<<"Unesite prvo vrijeme (h m s): ";
    std::cin>>v1.sati>>v1.minute>>v1.sekunde;
    TestirajVrijeme(v1);
    std::cout<<"Unesite drugo vrijeme (h m s): ";
    std::cin>>v2.sati>>v2.minute>>v2.sekunde;
    TestirajVrijeme(v2);
    std::cout<<"Prvo vrijeme: ";
    IspisiVrijeme(v1);
    std::cout<<std::endl<<"Drugo vrijeme: ";
    IspisiVrijeme(v2);
    std::cout<<std::endl<<"Zbir vremena: ";
    IspisiVrijeme(SaberiVrijeme(v1,v2));
    }
    catch (std::domain_error e) {std::cout<<e.what();}
	return 0;
}

void TestirajVrijeme(Vrijeme v) {
    if (!(v.sati>=0 && v.sati<24 && v.minute>=0 && v.minute<60 && v.sekunde>=0 && v.sekunde <60))
    throw (std::domain_error("Neispravno vrijeme"));
}

void IspisiVrijeme(Vrijeme v) {//مۉژە لىِ ۉوۉ ىِقآقۉ درۆغآچىِيە
    try {TestirajVrijeme(v);}
    catch (...) {throw;}
    std::cout<<std::setw(2)<<std::setfill('0')<<v.sati<<':';
    std::cout<<std::setw(2)<<std::setfill('0')<<v.minute<<':';
    std::cout<<std::setw(2)<<std::setfill('0')<<v.sekunde;
}

Vrijeme SaberiVrijeme(Vrijeme v1,Vrijeme v2) {
    try{
    TestirajVrijeme(v1);
    TestirajVrijeme(v2);
    }
    catch (...) {throw;}
    int x(v2.sekunde+v2.minute*60+v2.sati*60*60);
    v1.sekunde+=x;
    while (v1.sekunde>59) {
        v1.sekunde-=60;
        v1.minute++;
    }
    while (v1.minute>59) {
        v1.minute-=60;
        v1.sati++;
    }
    while (v1.sati>23) {
        v1.sati-=24;
    }
    return v1;
}