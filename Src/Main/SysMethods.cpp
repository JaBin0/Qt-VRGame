// System headers
#include <iostream>

// Own headers
#include <SysMethods.h>

SysMethods::SysMethods()
{

}

void SysMethods::errorCheck(const uint err) {
    if(!err) {
        std::cout << "Success" << std::endl;
    }
    else {
        std::cout << "Faild with error - " << err << std::endl;
    }
}
