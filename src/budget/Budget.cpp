////////////////////////////////////////////////////////////
// @Budget.cpp
//
// @author Eric Bruhns
//
////////////////////////////////////////////////////////////

#include "Budget.h"

namespace budget {

/**
 * Default Constructor
*/
Budget::Budget() 
    : username_(""),
      profit_(0.0),
      fixed_income_(),
      one_time_income_(),
      fixed_cost_(),
      one_time_cost_()
{}

/**
 * Overload Constructor
 * @param user The username to identify the budget
*/
Budget::Budget(const string& user) 
    : username_(user),
      profit_(0.0),
      fixed_income_(),
      one_time_income_(),
      fixed_cost_(),
      one_time_cost_()
{}

/**
 * Default Destructor
*/
Budget::~Budget() {}

/**
 * Adds an expense to the budget class
 * @param exp The expense to be added
*/
void Budget::addExpense(const Expense& exp) {
    // We need to see what type of Expense it is
    // fixed, income etc
    if(exp.fixed_ && exp.income_) {
        fixed_income_.push_back(exp);
    } else if(!exp.fixed_ && exp.income_) {
        one_time_income_.push_back(exp);
    } else if(exp.fixed_ && !exp.income_) {
        fixed_cost_.push_back(exp);
    } else {  // !exp.fixed_ && !exp.income_
        one_time_cost_.push_back(exp);
    }

    // After the expense is added to the appropriate vector
    // save it to storage file
    saveExpenseToFile(exp);
}

/**
 * Deletes an expense from the budget class
 * @name Name of struct to be deleted
*/
void Budget::deleteExpense(const string& name) {
    //pass
}

/**
 * Saves Budget to a file
*/
void Budget::saveToFile() const {
    // pass
}

/**
 * Sums up all expenses in the budget
 * @return The total sum of the expenses
*/
float Budget::sumUpExpenses() {
    // pass
}

/**
 * Set the profit when summed up
 * @param value The recent total of the expenses
*/
void Budget::setProfit(float value) {
    // pass
}

/**
 * Gets the profit of the budget
 * @return The Budget's profit
*/
float Budget::getProfit() const {
    // pass
}

/**
 * The string display of the entire budget to be displayed to
 * the user as well as be saved to the file
*/
string Budget::displayBudget() const {
    // pass
}





}  // namespace budget