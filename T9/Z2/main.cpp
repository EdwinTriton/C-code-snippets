/* 
    TP 16/17 (LV 9, Zadatak 1)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cmath>
class Vektor3d {
double kordinate[3];
public:
void Postavi(double x, double y, double z) {
kordinate[0] = x; kordinate[1] = y; kordinate[2] = z;
}
void PostaviX(double x) {
kordinate[0] = x;}
void PostaviY(double y) {
kordinate[1] = y;}
void PostaviZ(double z) {
kordinate[2] = z;}
void Ocitaj(double &x, double &y, double &z) const {
x = kordinate[0]; y = kordinate[1]; z = kordinate[2];
}
void Ispisi() const { std::cout << "{" << kordinate[0] << "," << kordinate[1] << "," << kordinate[2] << "}"; }
double DajX() const { return kordinate[0]; }
double DajY() const { return kordinate[1]; }
double DajZ() const { return kordinate[2]; }
double DajDuzinu() const { return std::sqrt(kordinate[0] * kordinate[0] + kordinate[1] * kordinate[1] + kordinate[2] * kordinate[2]); }
Vektor3d &PomnoziSaSkalarom(double s) { kordinate[0] *= s; kordinate[1] *= s; kordinate[2] *= s; return *this;}
Vektor3d SaberiSa(const Vektor3d &v) { kordinate[0] += v.kordinate[0]; kordinate[1] += v.kordinate[1]; kordinate[2] += v.kordinate[2];return *this; }
};
Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) {
Vektor3d v3;
v3.Postavi(v1.DajX() + v2.DajX(), v1.DajY() + v2.DajY(), v1.DajZ() + v2.DajZ());
return v3;
}
int main ()
{
    double a=0,b=0,c=0;
    std::cout<<"Unesite kordinate prvog vektora: "<<std::endl;
    std::cin>>a>>b>>c;
    Vektor3d v1;
    v1.Postavi(a,b,c);
    std::cout<<"Unesite kordinate drugog vektora: "<<std::endl;
    std::cin>>a>>b>>c;
    Vektor3d v2;
    v2.Postavi(a,b,c);
    std::cout<<"Zbir vektora jednak je: ";
    ZbirVektora(v1,v2).Ispisi();
    std::cout<<std::endl<<"Prvi vektor pomnozen sa -1 i sabran sa drugim je: "<<std::endl;
    v1.PomnoziSaSkalarom(-1).SaberiSa(v2).Ispisi();
	return 0;
}