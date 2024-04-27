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
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;
namespace budget {

struct Expense {
    string name_;
    float value_;
    bool fixed_;
    bool income_;
};

// Overload the << operator
ostream& operator<<(ostream& os, const Expense& exp) {
    os << exp.name_ << "," << exp.value_ << "," << exp.fixed_ << "," << exp.income_;
    return os;
}

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
        // open file with username
        string filename = username_ + "_expense_storage.csv";
        ofstream file;
        file.open(filename, ios::app);

        // check if open
        if(!file) {
            // Handle errors later
        } else {
            file << exp;
            file.close();  // Close file
        }
    }

    const string username_;
    float profit_;

    vector<Expense> fixed_income_;
    vector<Expense> one_time_income_;
    vector<Expense> fixed_cost_;
    vector<Expense> one_time_cost_;
};
}  // namespace budget

#endif  // BUDGET_H_