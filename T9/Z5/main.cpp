#include <iostream>
#include <list>
#include <iomanip>
class Sat{
    int sekundi;
    public:
    static bool DaLiJeIspravno(int sati,int minuta,int sekundi){
        if(sati>23 || sati<0 || minuta>59 || minuta<0 || sekundi>59 || sekundi<0)
        return false;
        return true;
    }
    void Postavi(int sati,int minuta,int sekundi) {
        
        if(!DaLiJeIspravno(sati, minuta, sekundi))
        std::__throw_domain_error("Neispravno vrijeme");
        Sat::sekundi = sekundi+60*minuta+3600*sati;
    }
    void PostaviNormalizirano(int sati,int minuta,int sekundi){
        while(sekundi>59){
            minuta++;
            sekundi-=60;
        }
        while(minuta>59){
            sati++;
            minuta-=60;
        }
        while(sati>23){
            sati-=24;
        }
        while(sekundi<0){
            minuta--;
            sekundi+=60;
        }
        while(minuta<0){
            sati--;
            minuta+=60;
        }
        while(sati<0){
            sati+=24;
        }
        Sat::sekundi = sekundi+60*minuta+3600*sati;
    }
    Sat Sljedeci(){
        sekundi++;
        
        Sat x;
        if(sekundi>86399)
        sekundi-=86400;
        x.sekundi=sekundi;
        return x;
    }
    Sat Prethodni(){
        sekundi--;
        
        Sat x;
        if(sekundi<0)
        sekundi+=86400;
        x.sekundi=sekundi;
        return x;
    }
    
    Sat PomjeriZa(int pom){
           sekundi+=pom;
         if(sekundi>86399)
        sekundi-=86400; 
         if(sekundi<0)
        sekundi+=86400; 
        Sat x;
        x.sekundi=sekundi;
        return x;
    
    }


 void Ispisi() const { 
     std::cout<<std::right<<std::setw(2)<<std::setfill('0')<<sekundi/3600<<":"<<std::right<<std::setw(2)<<std::setfill('0')<<(sekundi/60)-sekundi/3600*60<<":"<<std::right<<std::setw(2)<<std::setfill('0')<<sekundi-((sekundi/60)-sekundi/3600*60)*60-(sekundi/3600)*3600; 
     }
 int DajSate() const { return sekundi/3600; }
 int DajMinute() const { return sekundi/60-sekundi/3600*60; }
 int DajSekunde() const { return sekundi-((sekundi/60)-sekundi/3600*60)*60-(sekundi/3600)*3600; }
 
 
 static int  Razmak(Sat s1,Sat s2){
    int sek1,sek2;
    sek1=s1.DajSate()*3600+s1.DajMinute()*60+s1.DajSekunde();
    sek2=s2.DajSate()*3600+s2.DajMinute()*60+s2.DajSekunde();
    return sek1-sek2;
}
};

int  BrojSekundiIzmedju(Sat s1,Sat s2){
    int sek1,sek2;
    sek1=s1.DajSate()*3600+s1.DajMinute()*60+s1.DajSekunde();
    sek2=s2.DajSate()*3600+s2.DajMinute()*60+s2.DajSekunde();
    return sek1-sek2;
}

int main (){

  Sat s;
  s.Postavi(10,15,30);
  s.Ispisi();
  std::cout << std::endl;
  s.Postavi(0,4,3);
  s.Ispisi();

	return 0;
}