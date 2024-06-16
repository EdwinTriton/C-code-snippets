#include <iostream>
#include <cmath>
#include <iomanip>
#include <array>
double TrapeznoPravilo(double f(double),double a,double b,double n) {
    double suma(0);
    int k(1);
    while (k<n) {
        suma+=f(a+(b-a)*k/n);
        k++;
    }
    return (b-a)*(0.5*f(a)+0.5*f(b)+suma)/n;
}


int main ()
{
    std::cout<<"Unesite broj podintervala: "<<std::endl;
    int n;
    std::cin>>n;
    const std::array<char[10],4> colour = { "Blue", "Red",
                             "Orange", "Yellow" };
 
    // Printing Strings stored in 2D array
    for (int i = 0; i < 4; i++)
        std::cout << colour.at(i) << "\n";
    std::cout<<"Za taj broj podintervala priblizne vrijednosti integrala iznose:";
    std::cout << std::fixed;
    std::cout<<std::endl<<"- Za funkciju sin x na intervalu (0,pi): "<<std::setprecision(5)<<TrapeznoPravilo(sin,0,4*atan(1),n);
    std::cout<<std::endl<<"- Za funkciju x^3 na intervalu (0,10): "<<std::setprecision(2)<<TrapeznoPravilo([] (double x) {return x*x*x;},0,10,n);
    std::cout<<std::endl<<"- Za funkciju 1/x na intervalu (1,2): "<<std::setprecision(5)<<TrapeznoPravilo([] (double x) {return 1/x;},1,2,n);
	return 0;
}