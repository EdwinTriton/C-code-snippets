#include <iostream>
#include <algorithm>
#include <cmath>
#include <deque>

int main ()
{
    using namespace std;
    cout<<"Unesite broj elemenata: ";
    int n(0);cin>>n;
    cout<<"Unesite elemente: ";
    std::deque<int> a(n);
    for_each(a.begin(),a.end(),[](int &a) {
    std::cin>>a;
    return ;
}); 
    cout<<"Najveci element deka je "<<*max_element(a.begin(),a.end())<<endl;
    cout<<"Najmanji element deka se pojavljuje "<<count(a.begin(),a.end(),*min_element(a.begin(),a.end()))<<" puta u deku"<<endl;
    cout<<"U deku ima "<<count_if(a.begin(),a.end(),[](int a) {
    double s(sqrt(a));
    if (s-int(s)<0.0001) return true;
    return false;
})<<" brojeva koji su potpuni kvadrati"<<endl;
    cout<<"Prvi element sa najmanjim brojem cifara je "<<*min_element(a.begin(),a.end(),[](int a,int b) {
    return (int(log(abs(a))/log(10))<int(log(abs(b))/log(10)));
})<<endl;
    int b[1000]={0};
    auto c(remove_copy_if(a.begin(),a.end(),b,[](int a) {
    if (abs(a)==100) return true;
    if (abs(a)==1000) return false;
    if (int(log(abs(a))/log(10))==2) return true;
    return false;
}));
    cout<<"Elementi koji nisu trocifreni su:";
    for_each(b,c,[](int a) {
    std::cout<<" "<<a;
    return ;
});
	return 0;
}