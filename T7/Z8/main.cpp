#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
std::string IzvrniBezRazmaka(std::string s) {
    std::string q;
    remove_copy(s.rbegin(),s.rend(),std::back_inserter(q),' ');
    return q;
}
int main ()
{
	return 0;
}