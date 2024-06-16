#include <iostream>
#include <cstring>
#include <algorithm>


int main ()
{
    std::cout<<"Koliko zelite recenica: ";
    int x{};
    std::cin>>x;
    std::cin.ignore(1000,'\n');
    std::cout<<"Unesite recenice:"<<std::endl;
    try {
        char **recenice=new char*[x]{};
        try {
            for (int i=0; i<x; i++) {
                char t[1000]={};
                std::cin.getline(t,1000);
                recenice[i]=new char[strlen(t)+1];
                strcpy(recenice[i],t);
            }
        std::sort(recenice,recenice+x,[](char* a, char* b){int j{};while (a[j]!='\0' && b[j]!='\0' &&a[j]==b[j]) j++;return a[j]<b[j];});
            std::cout<<"Sortirane recenice: "<<std::endl;
            for (int i=0; i<x; i++) std::cout<<recenice[i]<<std::endl;
            for (int i=0; i<x; i++) delete[] recenice[i];
            delete[] recenice;
        } catch(...) {std::cout<<"Problemi s memorijom!";for (int i=0; i<x; i++) delete[] recenice[i];delete[] recenice;}
    } catch(...) {std::cout<<"Problemi s memorijom!";}
    return 0;
}