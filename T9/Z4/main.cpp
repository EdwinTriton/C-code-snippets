#include <iostream>
#include <list>
#include <iomanip>


class Sat{
    int sati,minuta,sekundi;
    public:
    static bool DaLiJeIspravno(int sati,int minuta,int sekundi){
        if(sati>23 || sati<0 || minuta>59 || minuta<0 || sekundi>59 || sekundi<0)
        return false;
        return true;
    }
    void Postavi(int sati,int minuta,int sekundi) {
        
        if(!DaLiJeIspravno(sati, minuta, sekundi))
        std::__throw_domain_error("Neispravno vrijeme");
        Sat::sati = sati; Sat::minuta = minuta; Sat::sekundi = sekundi;
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
        Sat::sati = sati; Sat::minuta = minuta; Sat::sekundi = sekundi;
    }
    Sat Sljedeci(){
        sekundi++;
        if(sekundi>59){
            sekundi-=60;
            minuta++;
            if(minuta>59){
                minuta-=60;
                sati++;
                if(sati>23)
                sati-=24;
            }
        }
        Sat x;
        x.minuta=minuta;
        x.sati=sati;
        x.sekundi=sekundi;
        return x;
    }
    Sat Prethodni(){
        sekundi--;
        if(sekundi<0){
            sekundi+=60;
            minuta--;
            if(minuta<0){
                minuta+=60;
                sati--;
                if(sati<0)
                sati+=24;
            }
        }
        Sat x;
        x.minuta=minuta;
        x.sati=sati;
        x.sekundi=sekundi;
        return x;
    }
    
    Sat PomjeriZa(int pom){
        if (pom>0){
           sekundi+=pom;
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
        }else{
           sekundi+=pom;
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
        }
        Sat x;
        x.minuta=minuta;
        x.sati=sati;
        x.sekundi=sekundi;
        return x;
    
    }


 void Ispisi() const { std::cout<<std::right<<std::setw(2)<<std::setfill('0')<<sati<<":"<<std::right<<std::setw(2)<<std::setfill('0')<<minuta<<":"<<std::right<<std::setw(2)<<std::setfill('0')<<sekundi; }
 int DajSate() const { return sati; }
 int DajMinute() const { return minuta; }
 int DajSekunde() const { return sekundi; }
 
 
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
    
	return 0;
}