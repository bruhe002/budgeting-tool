////////////////////////////////////////////////////////////
// @Budget.h
//
// @author Eric Bruhns
//
////////////////////////////////////////////////////////////

#ifndef BUDGET_H_
#define BUDGET_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <ctime>

using namespace std;
namespace budget {

struct Expense {
    string name_;
    float value_;
    bool fixed_;
    bool income_;

    float operator+(const Expense& exp) {
        return this->value_ + exp.value_;
    }

    float operator+(float f) {
        return f + value_;
    }
};



class Budget {
public:
    Budget();
    Budget(const string& user);

    void addExpense(const Expense& exp);
    string getStoreName();
    void deleteExpense(const string& name);
    void saveToFile() const;
    float sumUpExpenses() const;
    void setProfit(float value);
    float getProfit() const;
    void displayBudget() const;

    ~Budget();

private:
    /**
     * Saves an Expense to a csv file once created, acting as our
     * database for saved budgets
    */
    void saveExpenseToFile(const Expense& exp);

    const string username_;
    float profit_;

    vector<Expense> fixed_income_;
    vector<Expense> one_time_income_;
    vector<Expense> fixed_cost_;
    vector<Expense> one_time_cost_;
};
}  // namespace budget

#endif  // BUDGET_H_