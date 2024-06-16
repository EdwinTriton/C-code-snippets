#include <algorithm>
#include <iostream>
int main() {
    std::cout<<"Unesite recenicu: "<<std::endl;
    char s[1000] {'\0'};
    std::cin.getline(s,1000);
    char *q(s),*poc(s);
    int r(0);
    while (*q!='\0') {
        if (*q==' ' && ++q) {if(r) {poc=q;break;}continue;}
        r++;
        q++;
        if (*q=='\0') poc=q;
    }
    while (*poc==' ' && *poc!='\0') {
        poc++;
    }
    std::cout<<"Recenica bez prve rijeci glasi: ";
    while (*poc!='\0') {
        std::cout<<*poc;
        poc++;
    }
    std::cout<<std::endl;
  return 0;
}