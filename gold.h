#ifndef GOLD_H
#define GOLD_H
#include <string>

#include "customer.h"

// Derrived Class
class gold : public customer
{
    public:
        gold();
        gold(std::string, std::string, std::string, float, float); // Overloaded constructor
        float get_discount(){return discount;}
        void change_discount(float n) {discount = n;}
        std::string get_status() {return status;}

    protected:

    private:
        float discount;
        std::string status = "gold";
};

#endif // GOLD_H
