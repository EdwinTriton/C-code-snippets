#include <iostream>
enum Dani {Ponedjeljak, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja};
static const char *enum_str[] =
        { "Ponedjeljak", "Utorak", "Srijeda", "Cetvrtak", "Petak", "Subota", "Nedjelja"};

Dani &operator ++(Dani &d) {
 return d = Dani((int(d) + 1) % 7);
}
Dani operator ++(Dani &d, int) {
 Dani pomocni = d; ++d; return pomocni;
}

std::ostream &operator<<(std::ostream &tok, const Dani &v){
    std::string x (enum_str[v]);
    tok<<x;
    return tok;    
}
int main (){
    for(Dani d = Ponedjeljak; d <= Nedjelja; d++) {
        std::cout << d << std::endl;
        if(d==Nedjelja)
        break;
    }

	return 0;
}