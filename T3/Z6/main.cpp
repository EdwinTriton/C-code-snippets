//TP 2021/2022: LV 3, Zadatak 6
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
std::vector<std::vector<int>> KroneckerovProizvod(std::vector<int> a,std::vector<int>b) {
    std::vector<std::vector<int>> izlaz;
    for (int i:a) {
        std::vector<int> v;
        for (int j:b) {
            v.push_back(i*j);
        }
        izlaz.push_back(v);
    }
    return izlaz;
}

int NajvecaSirina(std::vector<std::vector<int>> a) {
    int max=0;
    bool q=false;
    for (std::vector<int> i:a) {
        for (int j:i) {
            int t=0,m=j;
            do {t++;j/=10;}while (j!=0);
            if (m<0) t++;
            if (t>max ) max=t;
        }
    }
    return max;
}
    

int main ()
{
    std::cout<<"Unesite broj elemenata prvog vektora: "<<std::endl;
    int n1;
    std::cin>>n1;
    std::cout<<"Unesite elemente prvog vektora: "<<std::endl;
    std:: vector<int> v1;
    for(int i=0;i<n1;i++) {
        int n;
        std::cin>>n;
        v1.push_back(n);
    }
    std::cout<<"Unesite broj elemenata drugog vektora: "<<std::endl;
    int n2;
    std::cin>>n2;
    std::cout<<"Unesite elemente drugog vektora: "<<std::endl;
    std:: vector<int> v2;
    for(int i=0;i<n2;i++) {
        int n;
        std::cin>>n;
        v2.push_back(n);
    }
    std::vector<std::vector<int>> k=KroneckerovProizvod(v1,v2);
    for (std::vector<int> i:k) {
        for (int j:i) {
            std::cout<<std::right<<std::setw(NajvecaSirina(k)+1)<<j;
        }
        std::cout<<std::endl;
    }
	return 0;
}
