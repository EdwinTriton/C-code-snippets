//TP 2021/2022: LV 4, Zadatak 2
#include <iostream>
#include <cmath>
#include <string>

void IzvrniString(std::string &s) {
    int v=s.size();
    for (int i=0; i<v/2;i++) {
        char x=s[i];
        s[i]=s[v-i-1];
        s[v-i-1]=x;
    }
}

int main ()
{
    using namespace std;
    cout<<"Unesi string: ";
    string s;
    getline(cin,s);
    IzvrniString(s);
    cout<<"Izvrnuti string je: "<<s;
	return 0;
}
