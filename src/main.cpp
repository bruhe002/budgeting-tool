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
void addExpenseMenu(Budget& budget);

int main() {
    // string user = "";
    // string menu_choice = "";
    // while(menu_choice != "4") {
    //     cout << "Welcome to Your Budget!\n\n";
    //     cout << "Select the following options:\n";
    //     cout << "\t1. Sign-in\n";
    //     cout << "\t2. Create New User\n";
    //     cout << "\t3. Delete a user\n";
    //     cout << "\t4. Exit\n";
    //     getline(cin, menu_choice);

    //     if(menu_choice.size() != 1) {
    //         cerr << "Invalid Option! Please try again...\n";
    //     }
    //     else {
    //         if(menu_choice == "1") {

    //         } else if(menu_choice == "2") {

    //         } else if(menu_choice == "3") {

    //         } else if(menu_choice == "4") {

    //         } else {
    //             cerr << "Invalid Option! Please try again...\n";
    //         }
    //     }
    //     cout << "Please Enter your user name (Type \"-1\" to exit): ";
    //     getline(cin, user);
    //     try {
    //         if(hasSpace(user)) {
    //             throw;
    //         }
    //     } catch (exception& e) {
    //         cerr << "User does not exist!\n" << "Creating one";
    //     }

    // }

    // Display the budget
    Budget b;

    // Display menu
    string budget_choice = "";
    while(budget_choice != "E") {
        b.displayBudget();
        cout << "Select an option: "
                "[A]dd expense, [D]elete Expense, [E]xit " << endl;
        
        getline(cin, budget_choice);
        if(budget_choice.size() != 1) {
            cerr << "Invalid Option. Please try again." << endl;
        } else {
            char letter = toupper(budget_choice[0]);
            switch(letter) {
                case 'A':
                    // Run an add function
                    addExpenseMenu(b);
                    break;
                case 'D':
                    break;
                case 'E':
                    budget_choice = letter;
                    break;
                default:
                    cerr << "Invalid Option. Please try again." << endl;
                    break;
            }
        }
    }

    // Expense rent{"Rent", 1885.00, FIXED_C};
    // Expense car{"Car", 300.07, FIXED_C};
    // Expense car_in{"car_insurance", 134.21, FIXED_C};
    // Expense income{"paycheck", 4710.00, FIXED_I};
    // Expense food{"chick-fil-a", 25.04, ONE_TIME_C};
    // Expense bday{"Birthday Money", 200.00, ONE_TIME_I};
    // Expense netflix{"Netflix", 15.99, ONE_TIME_C};

    // b.addExpense(rent);
    // b.addExpense(car);
    // b.addExpense(car_in);
    // b.addExpense(income);
    // b.addExpense(food);
    // b.addExpense(bday);
    // b.addExpense(netflix);


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

void addExpenseMenu(Budget& budget) {
    // Ask for name
    string exp_name = "";
    float value = 0.00;
    int type = 0;

    bool name_flag = true;
    while(name_flag) {
        cout << "Expense's name: ";
        getline(cin, exp_name);

        if(exp_name.size() > 15) {
            cerr << "Name too long. Please try again!\n";
        } else {
            name_flag = false;
        }
    }

    bool value_flag = true;
    while(value_flag) {
        cout << "Value: ";
        try {
            cin >> value;
            value_flag = false;
        } catch (exception& e) {
            cerr << e.what() << " Please try again. \n";
        }
    }

    bool type_flag = true;
    while(type_flag) {
        cout << "What type is it:\n";
        cout << "\t1. Fixed Income\n";
        cout << "\t2. Fixed Cost\n";
        cout << "\t3. One-time Cost\n";
        cout << "\t4. One-time Income\n";
        try {
            cin >> type;
            if (type < 1 || type > 5) {
                throw;
            }

            switch(type) {
                case 1:
                    budget.addExpense({exp_name, value, FIXED_I});
                    break;
                case 2:
                    budget.addExpense({exp_name, value, FIXED_C});
                    break;
                case 3:
                    budget.addExpense({exp_name, value, ONE_TIME_C});
                    break;
                case 4:
                    budget.addExpense({exp_name, value, ONE_TIME_I});
                    break;
            }

            type_flag = false;
        } catch(exception& e) {
            cerr << "Invalid Option. Please try again!\n";
        }
    }
}