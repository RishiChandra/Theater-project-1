#include "plat.h"

plat::plat()
{
    //ctor
}
// Overloaded Cunstructor
plat::plat(std::string f, std::string l, std::string i, float s, float d)
{
    first = f;
    last = l;
    id = i;
    spent = s;
    discount = d;
}
