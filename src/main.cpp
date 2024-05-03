////////////////////////////////////////////////////////////
// @main.cpp
//
// @author Eric Bruhns
//
////////////////////////////////////////////////////////////

#include "budget/Budget.h"

#include <iostream>

using namespace std;
using namespace budget;

int main() {

    Budget b;
    Expense rent{"Rent", 1885.00, true, false};
    Expense car{"Car", 300.07, true, false};
    Expense car_in{"car_insurance", 134.21, true, false};
    Expense income{"paycheck", 4710.00, true, true};
    Expense food{"chick-fil-a", 25.04, false, false};
    Expense bday{"Birthday Money", 200.00, false, true};
    Expense netflix{"Netflix", 15.99, true, false};

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