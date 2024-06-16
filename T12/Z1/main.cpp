#include <iostream>
#include <list>
#include <iomanip>


class Sat{
    int sati,minuta,sekundi;
    public:

    Sat(){
        sati=0;
        minuta=0;
        sekundi=0;
    }
    
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
    Sat(int sati,int minuta,int sekundi){
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
    friend Sat &operator++(Sat &v){
        v.sekundi++;
        if(v.sekundi>59){
            v.sekundi-=60;
            v.minuta++;
            if(v.minuta>59){
                v.minuta-=60;
                v.sati++;
                if(v.sati>23)
                v.sati-=24;
            }
        }
        return v;
    }

    friend Sat operator++(Sat &v,int){
        Sat x;
        x=v;
        v.sekundi++;
        if(v.sekundi>59){
            v.sekundi-=60;
            v.minuta++;
            if(v.minuta>59){
                v.minuta-=60;
                v.sati++;
                if(v.sati>23)
                v.sati-=24;
            }
        }

        return x;
    }

    friend Sat &operator--(Sat &v){
        v.sekundi--;
        if(v.sekundi<0){
            v.sekundi+=60;
            v.minuta--;
            if(v.minuta<0){
                v.minuta+=60;
                v.sati--;
                if(v.sati<0)
                v.sati+=24;
            }
        }
        return v;
    }

    friend Sat operator--(Sat &v,int){
        Sat x;
        x=v;
        v.sekundi--;
        if(v.sekundi<0){
            v.sekundi+=60;
            v.minuta--;
            if(v.minuta<0){
                v.minuta+=60;
                v.sati--;
                if(v.sati<0)
                v.sati+=24;
            }
        }

        return x;
    }
    
    Sat operator +=(int pom){
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


    Sat operator -=(int pom){
        pom*=-1;
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


 friend std::ostream &operator <<(std::ostream &tok, const Sat &v) { 
    tok<<std::right<<std::setw(2)<<std::setfill('0')<<v.sati<<":"<<std::right<<std::setw(2)<<std::setfill('0')<<v.minuta<<":"<<std::right<<std::setw(2)<<std::setfill('0')<<v.sekundi;
    return tok;
 }
 int DajSate() const { return sati; }
 int DajMinute() const { return minuta; }
 int DajSekunde() const { return sekundi; }
 
 
friend Sat operator-(Sat &v,int a){
    Sat x;
    x=v;
    x.sekundi-=a;
     while(x.sekundi<0){
                x.minuta--;
                x.sekundi+=60;
            }
            while(x.minuta<0){
                x.sati--;
                x.minuta+=60;
            }
            while(x.sati<0){
                x.sati+=24;
            }

      while(x.sekundi>59){
                x.minuta++;
                x.sekundi-=60;
            }
            while(x.minuta>59){
                x.sati++;
                x.minuta-=60;
            }
            while(x.sati>23){
                x.sati-=24;
            }      
            return x;

}

friend Sat operator+(Sat &v,int a){
    Sat x;
    x=v;
    x.sekundi+=a;
     while(x.sekundi<0){
                x.minuta--;
                x.sekundi+=60;
            }
            while(x.minuta<0){
                x.sati--;
                x.minuta+=60;
            }
            while(x.sati<0){
                x.sati+=24;
            }
      while(x.sekundi>59){
                x.minuta++;
                x.sekundi-=60;
            }
            while(x.minuta>59){
                x.sati++;
                x.minuta-=60;
            }
            while(x.sati>23){
                x.sati-=24;
            }      
            return x;

}

friend int operator-(Sat &v,Sat a){
    int a1,a2;
    a1=v.sati*3600+v.minuta*60+v.sekundi;
    a2=a.sati*3600+a.minuta*60+a.sekundi;
    return a1-a2;


}

friend int operator+(Sat &v,Sat a){
    int a1,a2;
    a1=v.sati*3600+v.minuta*60+v.sekundi;
    a2=a.sati*3600+a.minuta*60+a.sekundi;
    return a1+a2;

}};



int main (){

Sat s1(10, 4, 39);
  (--(++(++(++(++s1)))));
  std::cout << s1 << std::endl;
	return 0;
}