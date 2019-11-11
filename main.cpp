// Name: Rishi Chandra
// NetID: rxc170008
// List of libraries to include
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>      // to use std::setprecision when displaying the report

// List of class headers to add
#include "customer.h"
#include "gold.h"
#include "plat.h"

using namespace std;

// Function prototype header for function that processes the order
void process(customer *&cust, customer **&pre, string id, char siz, string type, float si_price, int quant, int &c, int &p);


int main()
{
    string name; // Var to store the read of each file
    int c = 0; // Var to count the number of customers
    int p = 0; // Var to count the number of customers

    ifstream input("customer.dat"); // Open the file of regular customers
    customer *cust = nullptr; // Create pointer to a customer objects

    // Validate that the file exists
    if (input.good()){

        // Loop over the file to find the size of the array
        while(!input.eof()){
            getline(input, name);
            c++;
        }
        // Reset file reading flag
        input.seekg(0);

        cust = new customer[c]; // Dynamically allocate the array of customers

        // Loop over the customer lines to get the customer data
        for (int i = 0; i < c; i++){
            getline(input, name); // Read the line
            istringstream ss(name); // Var to store the line as a stream

            // Initialize vars to store
            string first;
            string last;
            string id;
            float spent;

            // Read in the data
            ss >> id;
            ss >> first;
            ss >> last;
            ss >> spent;

            // Create temp customer object
            customer temp(first, last, id, spent); // Create a temp object with the customer data

            // Populate the dynamic array
            cust[i] = temp;
        }
    }

    // Reset the reading var
    input.close();
    input.clear();

    customer **pre = nullptr; // Create pointer to the preferred objects
    input.open("preferred.dat"); // Open file of preferred objects

    // Validate that the file exists
    if (input.good()){

        // Loop over the file to find the size of the array
        while(!input.eof()){
            getline(input, name);
            p++;
        }

        // Reset the flag for reading the file
        input.seekg(0);

        // Validate that the file is not empty
        if (name.size() > 0){
            pre = new customer*[c]; // Dynamically allocate the array of pointers to preferred customers

            // Loop over the customer lines to get the customer data
            for (int i = 0; i < p; i++){
                getline(input, name); // Read in the next line
                istringstream ss(name); // Var to store the line as a stream

                // Initialize vars to store the customer data
                string first;
                string last;
                string id;
                float spent;
                float discount;

                // Read in the data
                ss >> id;
                ss >> first;
                ss >> last;
                ss >> spent;

                // Check if the customer is plat or gold
                if (name.find("%") < 10000){
                    // Parse the discount string
                    string temp;
                    ss >> temp;
                    discount = stof(temp.substr(0, temp.size()-1));

                    // Create temp gold object
                    gold *tem = new gold(first,last,id,spent,discount);
                    // Populate array of preferred customers
                    pre[i] = tem;
                }
                else {
                    ss >> discount;

                    // Create temp plat object
                    plat *tem = new plat(first,last,id,spent,discount);
                    // Populate array of preferred customers
                    pre[i] = tem;
                }

            }
        }
    }

    // Reset the input variable
    input.close();
    input.clear();

    // Open the files of orders
    input.open("orders.dat");
    if (input.good()){

        // Counter var for orders
        int o = 0;
        string name; // Var to store the order info

        // Loop over the file to find the size of the array
        while(!input.eof()){
            getline(input, name);
            o++;
        }

        // Reset flag for reading file
        input.seekg(0);

        for (int i = 0; i < o; i++){
            bool valid = false;
            getline(input, name);
            istringstream ss(name); // Var to store the line as a stream

            // Initialize vars to store order data
            string id;
            char siz;
            string type;
            float si_price;
            int quant = 0;
            string test;

            // Take in the id and make sure its valid
            if((ss >> id).fail()){
                cout << "invalid1";
                continue;
            }

            // Validate that the id exists in the files
            for (int i = 0; i < c; i++){
                if (id == cust[i].get_id()){
                    valid = true;
                }
            }
            for (int i = 0; i < p; i++){
                if (id == pre[i]->get_id()){
                    valid = true;
                }
            }
            if (!valid){
                cout << "invalid2";
                continue;
            }

            // Take in the size and drink type and make sure its valid
            if((ss >> siz).fail()){
                cout << "invalid3";
                continue;
            }
            if((ss >> type).fail()){
                cout << "invalid4";
                continue;
            }
            if (!(siz == 'S' || siz == 'M' || siz == 'L') || !(type == "soda" || type == "tea" || type == "punch")){
                cout << "invalid5";
                continue;
            }

            // Take in the si price and make sure its valid
            if((ss >> si_price).fail()){
                cout << "invalid6";
                continue;
            }

            // Take in the quantity of drinks and make sure its valid
            if((ss >> quant).fail()){
                cout << "invalid7";
                continue;
            }

            // Validate there are not extra inputs
            ss >> test;
            if (test.size() > 0){
                cout << "invalid8";
                continue;
            }

            // Process the customer data
            process(cust, pre, id, siz, type, si_price, quant, c, p);

            // Output the processed customer data
            ofstream out("customer.dat");

            // Loop through all of the regular customers
            for (int i = 0; i < c; i++){
                // Output the customer data with formating
                out << cust[i].get_id() << " " << cust[i].get_first() << " " << cust[i].get_last() << " " << setprecision(2) << fixed << cust[i].get_spent();
                if (i < c-1){
                        out << endl;
                }
            }

            // Reset the ofstream variable
            out.close();
            out.clear();

            // Output the processed preferred customer data
            out.open("preferred.dat");

            // Loop through the preferred customers
            for (int i = 0; i < p; i++){
                // Output the formatted data
                out << pre[i]->get_id() << " " << pre[i]->get_first() << " " << pre[i]->get_last() << " " << setprecision(2) << fixed << pre[i]->get_spent() << " ";
                if (pre[i]->get_status() == "gold"){
                    out << pre[i]->get_discount() << "%";
                }
                else {
                    out << pre[i]->get_discount();
                }
                if (i < p-1){
                    out << endl;
                }
            }
            out.close();

        }
    }
    input.close();
    input.clear();

    return 0;
}

// Function  that processes the order
void process(customer *&cust, customer **&pre, string id, char siz, string type, float si_price, int quant, int &c, int &p){

    float price_drink; // var to store the price / oz of the drink
    // Determine the price of the drink
    if (type == "soda"){
        price_drink = .2f;
    }
    else if (type == "tea"){
        price_drink = .12f;
    }
    else if (type == "punch"){
        price_drink = .15f;
    }

    float sized; // Var to store the oz of the drink
    float surface; // Var to store the surface are of the cup
    // Calculate the surface area and oz of the drink
    if (siz == 'S'){
        sized = 12;
        surface = 4.5f * 2 *3.14159265358979323846f;
    }
    else if (siz == 'M'){
        sized = 20;
        surface = 5.75f * 2.25f *3.14159265358979323846f;
    }
    else if (siz == 'L'){
        sized = 32;
        surface = 7 * 2.75f *3.14159265358979323846f;
    }

    float price = sized * price_drink * static_cast<float>(quant); // Calculate the price of the actual drink
    surface *= si_price * static_cast<float>(quant); // Calculate the price of the cup

    float total = price + surface; // Get the total price of the drink


    int index = -1; // Var to store the index of the customer object in either of the arrays

    // Loop through the customer array and check if the id is a regular customers
    for (int i = 0; i < c; i++){
        if (id == cust[i].get_id()){
            index = i;
        }
    }

    // If the customer is regular
    if (index != -1){
        float new_discount = 0; // Var to store a potential new discount rate
        float new_total = total; // Var to store the total after a potential discount is applied
        float bonus_bucks = -1; // Var to store potential bonus bucks

        // Series of if statements to determine if the order makes the customer eligible for an upgrade
        if (cust[index].get_spent() + new_total >= 50){
            new_discount = 5;
            new_total = ((100-new_discount)/100) * total;
        }
        if (cust[index].get_spent() + new_total >= 100){
            new_discount = 10;
            new_total = ((100-new_discount)/100) * total;
        }
        if (cust[index].get_spent() + new_total >= 150){
            new_discount = 15;
            new_total = ((100-new_discount)/100) * total;
        }
        if (cust[index].get_spent() + new_total >= 200){
            bonus_bucks = static_cast<float>(static_cast<int>(((cust[index].get_spent() + new_total) - 200) / 10)); // Calculate the number of bonus bucks earned
        }

        //check if needs to be upgraded
        //upgrade to plat
        if (bonus_bucks != -1){
            customer *newcust = new customer[c - 1]; // Create new dynamic customer array with one less size
            // Create new plat object using the old customers details
            plat *newplat = new plat(cust[index].get_first(), cust[index].get_last(), cust[index].get_id(), cust[index].get_spent() + new_total, bonus_bucks);

            // Copy every object except the upgraded one to the new array
            int j = 0;
            for (int i = 0; i < c; i++){
                if (i != index){
                    newcust[j] = cust[i];
                    j++;
                }
            }
            // Free up memory
            delete []cust;
            cust = newcust;
            c--;

            // Create new array for pointers to preferred objects
            customer **newpre = new customer*[p+1];

            // populate the array
            for (int i = 0; i < p; i++){
                newpre[i] = pre[i];
            }
            newpre[p] = newplat;
            // Free up space
            delete []pre;
            pre = newpre;
            p++;
        }
        //upgrade to gold
        else if (new_discount != 0){
            // Create new customer array and gold object
            customer *newcust = new customer[c - 1];
            gold *newgold = new gold(cust[index].get_first(), cust[index].get_last(), cust[index].get_id(), cust[index].get_spent() + new_total, new_discount);

            // Replace the elements of the old array into the new one except the upgraded one
            int j = 0;
            for (int i = 0; i < c; i++){
                if (i != index){
                    newcust[j] = cust[i];
                    j++;
                }
            }
            // Free up space
            delete []cust;
            cust = newcust;
            c--;

            // Create new array of pointer to preferred object
            customer **newpre = new customer*[p+1];
            // Populate the new array
            for (int i = 0; i < p; i++){
                newpre[i] = pre[i];
            }
            newpre[p] = newgold;
            // Free up space
            delete []pre;
            pre = newpre;
            p++;

        }
        // Modify the amount spent with no upgrade
        else {
            cust[index].add_spent(total);
        }

    }
    // If the order is for a preferred object
    if (pre != nullptr && index == -1){
        // Find the preferred object
        for (int i = 0; i < p; i++){
            if (id == pre[i]->get_id()){
                index = i;
            }
        }

        float new_discount; // Var for a potential new discount
        float new_total = total; // Var for the total after a discount
        float bonus_bucks = -1; // Var for potential new bonus bucks

        // If the customer is gold
        // Use series of if statements to determine a potential upgrade
        if (pre[index]->get_status() == "gold"){
            new_discount = 5;
            new_total = ((100-new_discount)/100) * total;
            if (pre[index]->get_spent() + new_total >= 100){
                new_discount = 10;
                new_total = ((100-new_discount)/100) * total;
            }
            if (pre[index]->get_spent() + new_total >= 150){
                new_discount = 15;
                new_total = ((100-new_discount)/100) * total;
            }
            if (pre[index]->get_spent() + new_total >= 200){
                bonus_bucks = static_cast<float>(static_cast<int>(((pre[index]->get_spent() + new_total) - 200) / 10));
            }

            // If the gold object is upgraded to a plat object
            if (bonus_bucks != -1){
                // Free up space
                delete pre[index];
                // Create new plat object using the old data
                plat *newplat = new plat(pre[index]->get_first(), pre[index]->get_last(), pre[index]->get_id(), pre[index]->get_spent() + new_total, bonus_bucks);
                // Replace the object
                pre[index] = newplat;
            }
            // If there is just a new discount rate change it
            else if (pre[index]->get_discount() != new_discount){
                pre[index]->change_discount(new_discount);
                pre[index]->add_spent(new_total);
            }
            // If there is no change just modify the objects total
            else {
                pre[index]->add_spent(new_total);
            }
        }
        // If the object is platinum
        else {
                // Determine the new discount and bonus bucks
                new_discount = 0;
                new_discount = pre[index]->get_discount() - new_discount;
                if (new_discount < 0){
                    new_discount = 0;
                }
                new_total = new_total - pre[index]->get_discount();
                new_discount += static_cast<float>(static_cast<int>(new_total / 10));

                // Update the plat object
                pre[index]->change_discount(new_discount);
                pre[index]->add_spent(new_total);
        }


    }

}
