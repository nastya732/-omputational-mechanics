#include "library/KeplerovToRV.hpp"
#include "library/RVToKeplerov.hpp"
#include <iostream>

int main(){
    const double mu = 3.986004418e14;
    const KeplerovElements kep{
        7.0e6,  // a
        0.5,    // i
        0.3,    // Omega
        0.7,    // w
        1.0,    // nu
        0.1     // e
    };
    const Cartesian state = KeplerovToRV(kep, mu);
    const KeplerovElements result = RVToKeplerov(state, mu);
    std::cout << "a = " << result.a << '\n';
    std::cout << "e = " << result.e << '\n';
    std::cout << "i = " << result.i << '\n';
    return 0;
}