#include <iostream>
#include <functional>
std::function<int(int)> IteriranaFunkcija(std::function <int (int)> f,int n) {
    if (n<=0) return [](int x) {return x;} ;
    if (n==1) return f;
    return [f, n](int x){return f(IteriranaFunkcija(f, n-1)(x));};
}
int main ()
{
    std::cout<<"Koliko puta zelite oduzet jedan od broja i koji broj: \n";
    int x{},y{};
    std::cin>>x>>y;
    std::cout<<"Rezultat je : "<<IteriranaFunkcija([] (int c) {return c-1;},x)(y);
	return 0;
}