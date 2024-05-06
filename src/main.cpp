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