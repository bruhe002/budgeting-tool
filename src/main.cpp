////////////////////////////////////////////////////////////
// @main.cpp
//
// @author Eric Bruhns
//
////////////////////////////////////////////////////////////

#include "budget/Budget.h"

#include <iostream>
#include <exception>

using namespace std;
using namespace budget;

bool hasSpace(const string& str);

int main() {
    string user = "";
    string menu_choice = "";
    while(menu_choice != "4") {
        cout << "Welcome to Your Budget!\n\n";
        cout << "Select the following options:\n";
        cout << "\t1. Sign-in\n";
        cout << "\t2. Create New User\n";
        cout << "\t3. Delete a user\n";
        cout << "\t4. Exit\n";
        getline(cin, menu_choice);

        if(menu_choice.size() != 1) {
            cerr << "Invalid Option! Please try again...\n";
        }
        else {
            if(menu_choice == "1") {

            } else if(menu_choice == "2") {

            } else if(menu_choice == "3") {

            } else if(menu_choice == "4") {

            } else {
                cerr << "Invalid Option! Please try again...\n";
            }
        }
        cout << "Please Enter your user name (Type \"-1\" to exit): ";
        getline(cin, user);
        try {
            if(hasSpace(user)) {
                throw;
            }
        } catch (exception& e) {
            cerr << "User does not exist!\n" << "Creating one" 
        }

    }
    
    Budget b;
    Expense rent{"Rent", 1885.00, FIXED_C};
    Expense car{"Car", 300.07, FIXED_C};
    Expense car_in{"car_insurance", 134.21, FIXED_C};
    Expense income{"paycheck", 4710.00, FIXED_I};
    Expense food{"chick-fil-a", 25.04, ONE_TIME_C};
    Expense bday{"Birthday Money", 200.00, ONE_TIME_I};
    Expense netflix{"Netflix", 15.99, ONE_TIME_C};

    b.addExpense(rent);
    b.addExpense(car);
    b.addExpense(car_in);
    b.addExpense(income);
    b.addExpense(food);
    b.addExpense(bday);
    b.addExpense(netflix);

    b.displayBudget();

    return 0;
}

bool hasSpace(const string& str) {
    for(auto c : str) {
        if(isspace(c)) {
            return true;
        }
    }

    return false;
}