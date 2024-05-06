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
#include <stdint.h>

#include <ctime>

using namespace std;
namespace budget {

enum CostType : uint32_t {
    FIXED_I = 0,
    FIXED_C,
    ONE_TIME_C,
    ONE_TIME_I
};

struct Expense {
    string name_;
    float value_;
    CostType type_;

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

    void addExpenseToBudget(const Expense& exp);

    const string username_;
    float profit_;

    vector<Expense> fixed_income_;
    vector<Expense> one_time_income_;
    vector<Expense> fixed_cost_;
    vector<Expense> one_time_cost_;
};
}  // namespace budget

#endif  // BUDGET_H_