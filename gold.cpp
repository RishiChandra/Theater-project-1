#include "gold.h"
#include <string>

gold::gold()
{
    //ctor
}
// Overloaded Constructor
gold::gold(std::string f, std::string l, std::string i, float s, float d)
{
    first = f;
    last = l;
    id = i;
    spent = s;
    discount = d;
}
