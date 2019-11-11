#include "customer.h"
#include <string>

customer::customer(){

}
// Overloaded constructor
customer::customer(std::string f, std::string l, std::string i, float s)
{
    first = f;
    last = l;
    id = i;
    spent = s;
}

/*customer::customer(const customer& other)
{
    //copy ctor
}*/
