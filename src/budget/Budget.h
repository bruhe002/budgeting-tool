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
    void deleteExpense(string& name);
    void saveToFile() const;
    void setProfit(float value);
    float getProfit() const;
    string displayBudget() const;

    ~Budget();

private:
    string username_;
    float profit_;
};
}  // namespace budget

#endif  // BUDGET_H_