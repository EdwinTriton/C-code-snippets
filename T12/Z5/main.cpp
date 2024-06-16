#include <vector>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <iostream>
int main ()
{
    int n;
    std::cout<<"Koliko zelite elemenata: ";
    std::cin>>n;
    std::vector<double> v(n);
    std::vector<double> k(n);
    std::cout<<"Unesite elemente: ";
    for(int i=0; i<n; i++)
    std::cin>>v[i];
    std::cout<<"Transformirani elementi: ";
    std::transform(v.begin(), v.end(), k.begin(), std::bind1st(std::divides<double>(), 1));
    for(int i=0; i<n; i++)
    std::cout<<k[i]<<" ";
	return 0;
}