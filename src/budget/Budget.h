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
#include <utility>

#include <ctime>

using namespace std;

std::pair<string, string> getCurrentTime();

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
    string month_;
    string year_;

    float operator+(const Expense& exp) {
        return this->value_ + exp.value_;
    }

    float operator+(float f) {
        return f + value_;
    }

    string toString() const {
        stringstream ss;
        ss << name_ << "," << value_ << "," << type_ << "," << month_ << "," << year_;
        return ss.str();
    }
};

class Budget {
public:
    Budget();
    Budget(const string& user, const string& month, const string& year);

    void addExpense(const Expense& exp);
    string getStoreName();
    void deleteExpense(const CostType& type);
    size_t getFixedIncomeSize() { return fixed_income_.size(); }
    size_t getFixedCostSize() { return fixed_cost_.size(); }
    size_t getOneTimeCostSize() { return one_time_cost_.size(); }
    size_t getOneTimeIncomeSize() { return one_time_income_.size(); }
    void exportToFile() const;
    float sumUpExpenses() const;
    void setProfit(float value);
    float getProfit() const;
    string displayBudget() const;

    ~Budget();

private:
    /**
     * Saves an Expense to a csv file once created, acting as our
     * database for saved budgets
    */
    void saveExpenseToFile(const Expense& exp);
    void deleteExpenseFromFile(const Expense& exp);

    void addExpenseToBudget(const Expense& exp) {
        switch(exp.type_) {
            case FIXED_I:
                fixed_income_.push_back(exp);
                break;
            case FIXED_C:
                fixed_cost_.push_back(exp);
                break;
            case ONE_TIME_C:
                one_time_cost_.push_back(exp);
                break;
            case ONE_TIME_I:
                one_time_income_.push_back(exp);
                break;
        }
    }

    const string username_;
    float profit_;
    const string month_;
    const string year_;

    vector<Expense> fixed_income_;
    vector<Expense> fixed_cost_;
    vector<Expense> one_time_cost_;
    vector<Expense> one_time_income_;
};
}  // namespace budget

#endif  // BUDGET_H_