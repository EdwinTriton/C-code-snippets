//TP 2021/2022: Zadaća 3, Zadatak 3
#include <iomanip>
#include <iostream>
#include <cmath>
#include <vector>
template <typename TipElemenata>
struct Matrica {
char ime_matrice; 
int br_redova, br_kolona;
TipElemenata **elementi = nullptr;
};

template <typename tip>
void UnistiMatricu(Matrica<tip> &mat) {
    if (!mat.elementi) return;
    for (int i=0; i<mat.br_redova; i++) delete[] mat.elementi[i];
    delete [] mat.elementi;
    mat.elementi=nullptr;
}
template <typename TipElemenata>
void UnesiMatricu(Matrica<TipElemenata> &mat) {
for(int i = 0; i < mat.br_redova; i++)
for(int j = 0; j < mat.br_kolona; j++) {
std::cout << mat.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
std::cin >> mat.elementi[i][j];
}
}
template <typename tip>
Matrica<tip> StvoriMatricu(int br_redova,int br_kolona, char ime=0) {
    Matrica<tip> mat;
    mat.br_kolona=br_kolona;mat.br_redova=br_redova;mat.ime_matrice=ime;
    try{//DODAN TRY !!!
    mat.elementi=new tip*[br_redova]{};
    }
    catch (...) {throw;}
    try{
        for (int i=0; i<br_redova; i++) {
            mat.elementi[i]=new tip[br_kolona]{};
        }
    }
    catch (...) {
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}

template <typename tip>
void UnesiMatricu (char ime, Matrica<tip> &m) { //mozda da vratim kako je bilo sa predavanje kod al tad testovi nevaljaju ili je ne valjaju
    for (int i=0; i<m.br_redova;i++)
        for (int j=0; j<m.br_kolona; j++) {
            std::cout << ime << "(" << i+1 << "," << j+1 << ") = ";
            std::cin >> m.elementi[i][j];
        }
}

template <typename tip> /*pitaj poslijne profesora ustvr ne njega nego predavanje dal & vrsi kopiranje jer const & vrsi sig & ne vrsi al et*/
void IspisiMatricu(Matrica<tip> &mat, int sirina_ispisa, int preciznosti=6, bool treba_brisati=false) {
    for (int i=0; i<mat.br_redova; i++) {
        for (int j=0; j<mat.br_kolona; j++) {
            std::cout <<std::setprecision(preciznosti)<< std::setw(sirina_ispisa) << mat.elementi[i][j];
        }
        std::cout<<std::endl;
    }
    if (treba_brisati) UnistiMatricu(mat);
}

template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1,
const Matrica<TipElemenata> &m2) {
if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
throw std::domain_error("Matrice nemaju jednake dimenzije!");
try {
auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
for(int i = 0; i < m1.br_redova; i++)
for(int j = 0; j < m1.br_kolona; j++)
m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
return m3;
}
catch (...) {throw;}
}
template <typename tip>
Matrica<tip> ProduktMatrica(const Matrica<tip> &a,const Matrica<tip> &b) {
    auto &A=a.elementi;
    auto &B=b.elementi;
    if (a.br_redova==0 && b.br_redova==0) return a;
    if (!a.br_redova || !b.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    if (a.br_kolona != b.br_redova) {
        throw std::domain_error("Matrice nisu saglasne za mnozenje");
    }
    Matrica<tip> m;
    try{
    m=StvoriMatricu<tip>(a.br_redova,b.br_kolona);
    for (int i = 0; i < a.br_redova; i++) {
        for (int j = 0; j < b.br_kolona; j++) {
        double suma = 0;
        for (int k = 0; k < b.br_redova; k++)
            suma += A[i][k] * B[k][j];
        m.elementi[i][j] = suma;
        }
    }
  return m;
    }
    catch (...) {throw;}
}
template <typename tip>
void Jedinicna(tip **elementi, int x,double p) {
    for (int i=0; i<x; i++) {
        for (int j=0; j<x; j++) {
            if (i==j) elementi[i][j]=p;
            else elementi[i][j]=0;//vjrv ne treba jer stvorimatricu vjrv stavi sve na 0
        }
    }
}

template <typename tip>
void FunZbir(Matrica<tip> &izlaz,const Matrica<tip> &a) {
    for (int i=0; i<izlaz.br_redova; i++) {
        for (int j=0; j<izlaz.br_redova; j++) {
            izlaz.elementi[i][j]+=a.elementi[i][j];
        }
    }
}

template <typename tip>
void FunMnozenje(Matrica<tip> &izlaz,double a) {
    for (int i=0; i<izlaz.br_redova; i++) {
        for (int j=0; j<izlaz.br_redova; j++) {
            izlaz.elementi[i][j]*=a;
        }
    }
}

template <typename tip>
Matrica<tip> MatricniPolinom(Matrica<tip> mat,std::vector<double> v) {
    if (mat.br_kolona!=mat.br_redova) throw std::domain_error("Matrica mora biti kvadratna");
    Matrica<tip> izlaz;
    try {
        izlaz=StvoriMatricu<tip>(mat.br_redova, mat.br_kolona);
        if (!v.size()) {return izlaz;}
        for (int i=0; i<v.size(); i++) {
            Matrica<tip> pomocna;
            if (!i) {
                pomocna=StvoriMatricu<tip>(mat.br_redova, mat.br_kolona);
                Jedinicna(pomocna.elementi,pomocna.br_redova,v.at(i));
                FunZbir(izlaz,pomocna);
                UnistiMatricu(pomocna);
            }
            else {
                pomocna=StvoriMatricu<tip>(mat.br_redova, mat.br_kolona);
                FunZbir(pomocna,mat);
                for (int q=1; q<i; q++) {
                    Matrica<tip> pomocna2=pomocna;
                    pomocna=ProduktMatrica(pomocna, mat);
                    UnistiMatricu(pomocna2);
                }
                FunMnozenje(pomocna,v.at(i));
                FunZbir(izlaz,pomocna);
                UnistiMatricu(pomocna);
            }
        }
        return izlaz;
    }
    catch(...) {UnistiMatricu(izlaz);throw;}
}

int main ()
{
    Matrica<double> a,b,c;
    int m{},n{};
    std::cout<<"Unesite dimenziju kvadratne matrice: ";
    std::cin >> m ;n=m;
    try {
    a = StvoriMatricu<double>(m, n, 'A');
    std::cout << "Unesite elemente matrice A: "<<std::endl;
    UnesiMatricu(a);
    std::cout << "Unesite red polinoma: ";
    int x{};std::cin>>x;
    std::cout<<"Unesite koeficijente polinoma: ";
    std::vector<double> v;
    for (int i=0; i<=x; i++) {
        double q{};
        std::cin>>q;
        v.push_back(q);
    }
    auto qwerk=MatricniPolinom<double>(a,v);
    IspisiMatricu(qwerk, 10, 6, true);
    }
    catch(std::bad_alloc) {
    std::cout << "Nema dovoljno memorije!\n";
    }
    UnistiMatricu(a);
	return 0;
}
