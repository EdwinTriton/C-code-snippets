#include <iostream>
#include <functional>
std::function<double(double)> f(double x) {return [x](double y) {return x+y;};}
auto g(double x) {return [x](double y) {return [x,y](double z) {return x+y+z;};};}
std::function<double(double)> plus2(double x) {return f(x);}
std::function<std::function<double(double)> (double)>  plus3(double x) {return g(x);}
int main ()
{
    std::cout<<"Unesi dva broja za sabiranje: "<<std::endl;
    int x,y;
    std::cin>>x>>y;
    std::cout<<"Rezultat: "<<plus2(x)(y)<<std::endl;
    std::cout<<"Unesi tri broja za sabiranje: "<<std::endl;
    int a,b,c;
    std::cin>>a>>b>>c;
    std::cout<<"Rezultat: "<<plus3(a)(b)(c)<<std::endl;
	return 0;
}