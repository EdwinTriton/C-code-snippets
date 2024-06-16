/* 
    TP 2018/2019: LV 5, Zadatak 2
	
	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.
	
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <iostream>
template <typename tip,typename tip2>
tip2 RazmijeniBlokove(tip p1,tip p2,tip2 p3) {
    while (p1<p2) {
        auto c(*p1);
        *p1++=*p3;
        *p3++=c;
    }
    return p3;
}
int main ()
{
    int a[10] {1,2,3,4,5,6,7,8,9,10};
    char s[10]="Hello yal";
    RazmijeniBlokove(a,a+10,s);
	return 0;
}