#include <iostream>
#include <cstring>
#include <algorithm>
#include <memory>
int main ()
{
    std::cout<<"Koliko zelite recenica: ";
    int x{};
    std::cin>>x;
    std::cin.ignore(1000,'\n');
    std::cout<<"Unesite recenice: "<<std::endl;
    using quirky=std::shared_ptr<std::string>;
    try {
    std::unique_ptr<quirky[]> s=std::unique_ptr<quirky[]>(new quirky[x]{});//
    try {
    for (int i=0; i<x; i++) {
        s[i]=std::make_shared<std::string>();
        std::getline(std::cin,* s[i]);
    }
    std::sort(s.get(),s.get()+x,[](auto s1,auto s2)->bool {return *s1<*s2;} );
    std::cout<<"Sortirane recenice:\n";
    for (int i=0; i<x; i++) {
        std::cout<<*s[i]<<std::endl;
    }
    for (int i=0; i<x; i++) {
        s[i]=nullptr;
    }
    }
    catch (...) {
        for (int i=0; i<x;i++) s[i]=nullptr;
        s=nullptr;
        throw; 
    }
    s=nullptr;
    }
    catch (...) {
        std::cout<<"Problemi s memorijom!";
    }
	return 0;
}
//[](std::string::iterator s1,std::string::iterator s2)->bool {while (*s1!='\0' && *s2!='\0' && *s1==*s2) {s1++;s2++;}return *s1<*s2;} 
/*
#include <iostream>
#include <cstring>
#include <algorithm>
int main ()
{
    std::cout<<"Koliko zelite recenica: ";
    int x{};
    std::cin>>x;
    std::cin.ignore(1000,'\n');
    std::cout<<"Unesite recenice: "<<std::endl;
    try {
    std::string *s=new std::string [x] {};
    try {
    for (int i=0; i<x; i++) {
        std::string a{};
        std::getline(std::cin,a);
        s[i]=a;
    }
    std::sort(s,s+x);
    std::cout<<"Sortirane recenice:\n";
    for (int i=0; i<x; i++) {
        std::cout<<s[i]<<std::endl;
    }
    }
    catch (...) {
        delete [] s;
        throw; 
    }
    delete [] s;
    }
    catch (...) {
        std::cout<<"Problemi s memorijom!";
    }
	return 0;
}
//[](std::string::iterator s1,std::string::iterator s2)->bool {while (*s1!='\0' && *s2!='\0' && *s1==*s2) {s1++;s2++;}return *s1<*s2;} */