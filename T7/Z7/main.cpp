#include <iostream>
#include <set>
template<typename tip>
std::set<tip> Unija(std::set<tip> a,std::set<tip> b) {
    for (tip s:b) a.insert(s);
    return a;
}
template<typename tip>
std::set<tip> Presjek(std::set<tip> a,std::set<tip> b) {
    std::set<tip> c{};
    for (tip s:b) for (tip q:a) if (q==s) c.insert(s);
    return c;
}
int main ()
{
    std::set<std::string> a{"Salve","Hi Y'all"};
    std::set<std::string> b{"Zdravo","Rijec","Salve"};
    for (auto q:Unija(a,b)) std::cout<<q<<" ";
    std::cout<<"\nPresjek: ";
    for (auto q:Presjek(a,b)) std::cout<<q<<"";
	return 0;
}