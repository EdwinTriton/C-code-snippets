/* 
    TP 2018/2019: LV 6, Zadatak 5
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <vector>
#include <deque>
#include <type_traits>
template <typename tip>
auto KreirajDinamickuKopiju2D(tip m) {
    std::remove_reference_t<decltype(m[0][0])> **a;
    try {
        a=new std::remove_reference_t<decltype(m[0][0])> *[m.size()];
        try {
            for (int i=0; i<m.size(); i++) {
                a[i]=new std::remove_reference_t<decltype(m[0][0])>[m[0].size()];
            }
            for (int i=0; i<m.size(); i++) {
                for (int j=0; j<m[i].size();j++) {
                    a[i][j]=m[i][j];
                }
            }
        }
        catch (...) {
            for (int i=0; i<m.size(); i++) {
                delete [] a[i];
            }
            throw;
        }
    }
    catch (...) {
        delete[] a;
        throw;iju2D(matrica);
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                std::cout<<t[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
        for (int i=0; i<n; i++) delete[] t[i];
        delete[] t;
    }
    catch (...) {
        std::cout<<"Nedovoljno memorije";
    }
	return 0;
}