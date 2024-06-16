#include <iostream>
#include <list>
template <typename tip>
void SortirajListu(std::list<tip> &a) {
    for (auto q=a.begin(),t=++a.begin(); t!=a.end(); q++,t++) 
        if (*t<*q) {
            a.insert(q,*t);
            a.erase(t);
            t=a.begin();
            q=--a.begin();
        }
}
int main ()
{
    int x{};
    std::list<int> list;
    std::cout<<"Koliko ima elemenata: "<<std::endl;
    std::cin>>x;
    std::cout<<"Unesite elemente: "<<std::endl;
    for (int i=0,t=0; std::cin>>t,i<x; i++) list.push_front(t);
    SortirajListu(list);
    std::cout<<"Sortirana lista:";
    for (int i:list) std::cout<<" "<<i;
	return 0;
}