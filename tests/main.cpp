#include "library/KeplerovToRV.hpp"
#include "library/RVToKeplerov.hpp"
#include <iostream>

int main(){
    const double mu = 3.986004418e14;
    const KeplerovElements kep{
        7.0e6,  // a
        0.1,    // e
        0.5,   // i
        0.3,    // Omega
        0.7,    // w
        1.0,    // nu

    };

    const Cartesian state = KeplerovToRV(kep, mu);
    std::cout << "r = " << state.r.transpose() << "\n";
    std::cout << "v = " << state.v.transpose() << "\n";
    const KeplerovElements result = RVToKeplerov(state, mu);
    std::cout << "a = " << result.a << '\n';
    std::cout << "w = " << result.w << '\n';
    std::cout << "i = " << result.i << '\n';
    return 0;
}