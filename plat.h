#ifndef PLAT_H
#define PLAT_H

#include "customer.h"

// Derrived class
class plat : public customer
{
    public:
        plat();
        plat(std::string, std::string, std::string, float, float); // Overloaded constructor
        float get_discount(){return discount;}
        void change_discount(float n) {discount = n;}
        std::string get_status() {return status;}


    protected:

    private:
        float discount;
        std::string status = "plat";
};

#endif // PLAT_H
