#include <iostream>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>

int main() {   
    using namespace boost::units;
    using namespace boost::units::si;

    quantity<force>     F(1.55*newton);
    quantity<length>    dx(2.6*meter);
    quantity<energy>    E = F*dx;
    
    std::cout << "F  = " << F << std::endl
              << "dx = " << dx << std::endl
              << "E  = " << E << std::endl
              << std::endl;
}
