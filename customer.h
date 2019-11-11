#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

// Base customer class
class customer
{
    public:
        customer();
        customer(std::string, std::string, std::string, float);//Overloaded constructor
        // Acessor and mutator methods
        std::string get_first(){return first;}
        std::string get_last() {return last;}
        std::string get_id() {return id;}
        float get_spent() {return spent;}
        void add_spent(float add) {spent += add;}
        virtual std::string get_status() {return status;}
        virtual void change_discount(float n) {n++;}
        virtual float get_discount() {return -1;}
        virtual ~customer(){};

    protected:
        std::string first;
        std::string last;
        std::string id;
        float spent;
        std::string status = "";
    private:

};

#endif // CUSTOMER_H
