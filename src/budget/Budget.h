////////////////////////////////////////////////////////////
// @Budget.h
//
// @author Eric Bruhns
//
////////////////////////////////////////////////////////////

#ifndef BUDGET_H_
#define BUDGET_H_

#include <iostream>
#include <string>

using namespace std;
namespace budget {

struct Expense {
    string name_;
    bool fixed_;
    bool income_;
    float value_;
};

class Budget {
public:
    Budget();
    Budget(const string& user);

    void addExpense(const Expense& exp);
    void deleteExpense(const string& name);
    void saveToFile() const;
    float sumUpExpenses();
    void setProfit(float value);
    float getProfit() const;
    string displayBudget() const;

    ~Budget();

private:
    /**
     * Saves an Expense to a csv file once created, acting as our
     * database for saved budgets
    */
    void saveExpenseToFile(const Expense& exp) {
        // pass
    }
    const string username_;
    float profit_;
};
}  // namespace budget

#endif  // BUDGET_H_