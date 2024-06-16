//TP 2016/2017: LV 1, Zadatak 3
#include <iostream>
#include <cmath>
#include <iomanip>
int main ()
{
    using namespace std;
    cout<<"Unesite pocetnu i krajnju vrijednost: \n";
    int a,b;
    cin>>a>>b;
    cout<<"+---------+----------+----------+-----------+"<<endl
        <<"| Brojevi | Kvadrati | Korijeni | Logaritmi |"<<endl
        <<"+---------+----------+----------+-----------+"<<endl;
        while (a<=b) {
            cout<<"| "<<left<<setw(8)<<a<<"|"<<right<<setw(9)<<a*a<<" |"<<setw(9)<<fixed<<setprecision(3)<<sqrt(a)<<" |"<<setw(10)<<fixed<<setprecision(5)<<log(a)<<" |"<<endl;
            a++;
        }
        cout<<"+---------+----------+----------+-----------+"<<endl;
	return 0;
}