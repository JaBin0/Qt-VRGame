#ifndef SYSTEMMETHODS_H
#define SYSTEMMETHODS_H
// Qt headers
#include <QtGlobal>


class SysMethods
{
public:
    SysMethods();

    // Check if there was errror and print it, success otherwise
    static void errorCheck(const uint err);
};

#endif // SYSTEMMETHODS_H
