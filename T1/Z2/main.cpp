//TP 2016/2017: Tutorijal 1, Zadatak 2
#include <iostream>
#include <cmath>
int main ()
{
    using namespace std;
    const double pi=atan(1)*4;
    cout<<"Unesite tri broja: ";
    double a,b,c;
    cin>>a>>b>>c;
    if (a<=0 || b<=0 || c<=0 || a+b<=c || a+c<=b || b+c<=a) {
        cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!";
        return 0;
    }
    double s=(a+b+c)/2;
    double p=sqrt( s*(s-a)*(s-b)*(s-c) );
    cout<<"Obim trougla sa duzinama stranica "<<a<<", "<<b<<" i "<<c<<" iznosi "<<s*2<<"."<<endl;
    cout<<"Njegova povrsina iznosi "<<p<<"."<<endl;
    double gamma;
    gamma=acos(0.5*(a*a+b*b-c*c)/(a*b));
    double alfa;
    alfa=acos(0.5*(c*c+b*b-a*a)/(c*b));
    double beta;
    beta=acos(0.5*(a*a+c*c-b*b)/(a*c));
    double min=370;
    if (alfa<=beta) {
        min=alfa;
    }
    else {
        min=beta;
    }
    if (min>gamma) {
        min=gamma;
    }
    min*=180/pi;
    cout<<"Njegov najmanji ugao ima "<<int(min)<<" stepeni, "<<int((min-int(min))*60)<<" minuta i "<<int(((min-int(min))*60-int((min-int(min))*60))*60)<<" sekundi."<<endl;
	return 0;
}