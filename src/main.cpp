////////////////////////////////////////////////////////////
// @main.cpp
//
// @author Eric Bruhns
//
////////////////////////////////////////////////////////////

#include "budget/Budget.h"
#include "except/InvalidOptionException.h"

#include <iostream>
#include <exception>
#include <limits>

using namespace std;
using namespace budget;

bool hasSpace(const string& str);
void addExpenseMenu(Budget& budget);
void deleteExpenseMenu(Budget& budget);

int main() {
    // Display the budget
    Budget b;

    // Display menu
    string budget_choice = "";
    while(budget_choice != "E") {
        b.displayBudget();
        cout << "Select an option: "
                "[A]dd expense, [D]elete Expense, E[X]port Budget, [E]xit " << endl;
        getline(cin, budget_choice);
        if(budget_choice.size() != 1) {
            cerr << "Invalid Option. Please try again." << endl;
        } else {
            char letter = static_cast<char>(toupper(budget_choice[0]) );
            switch(letter) {
                case 'A':
                    // Run an add function
                    addExpenseMenu(b);
                    break;
                case 'D':
                    deleteExpenseMenu(b);
                    break;
                case 'X':
                    // Export Function
                    break;
                case 'E':
                    system("clear");
                    budget_choice = letter;
                    break;
                default:
                    cerr << "Invalid Option. Please try again." << endl;
                    break;
            }
        }
    }
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
            // If value was not numeric it will fail
            if(value <= 0) {
                cin.clear();  // Clear the error state
                cin.ignore(std::numeric_limits<streamsize>::max(),'\n'); // Clear the rest of the input
                throw except::InvalidOptionException("Not an appropriate value! Please try again...\n");
            }
            value_flag = false;
        } catch (exception& e) {
            cerr << e.what();    
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
            if (type < 1 || type > 4) {
                throw except::InvalidOptionException();
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
            cin.clear();  // Clear the error state
            cin.ignore(std::numeric_limits<streamsize>::max(),'\n'); // Clear the rest of the input
            cerr << e.what() << endl;
        }
    }
}

void deleteExpenseMenu(Budget& budget) {
    int choice = 0;
    bool quit = false;
    while(!quit) {
        cout << "Which Type of Expense to delete?\n"
                "\t1. Fixed Income\n"
                "\t2. Fixed Costs\n"
                "\t3. One-Time Costs\n"
                "\t4. One-Time Income\n"
                "\t5. Quit\n";
        try {
            cin >> choice;
            switch(choice) {
                case 1:
                    if(budget.getFixedIncomeSize() == 0) {
                        throw except::InvalidOptionException("No Expenses to Delete!");
                    }
                    budget.deleteExpense(FIXED_I);
                    break;
                case 2:
                    if(budget.getFixedCostSize() == 0) {
                        throw except::InvalidOptionException("No Expenses to Delete!");
                    }
                    budget.deleteExpense(FIXED_C);
                    break;
                case 3:
                    if(budget.getOneTimeCostSize() == 0) {
                        throw except::InvalidOptionException("No Expenses to Delete!");
                    }
                    budget.deleteExpense(ONE_TIME_C);
                    break;
                case 4:
                    if(budget.getOneTimeIncomeSize() == 0) {
                        throw except::InvalidOptionException("No Expenses to Delete!");
                    }
                    budget.deleteExpense(ONE_TIME_I);
                    break;
                case 5:
                    break;
                default:
                    throw except::InvalidOptionException();
            }
            quit = true;
        } catch(exception& e) {
            cin.clear();  // Clear the error state
            cin.ignore(std::numeric_limits<streamsize>::max(),'\n'); // Clear the rest of the input
            cerr << e.what() << endl;
        }
    }
}