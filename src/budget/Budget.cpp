////////////////////////////////////////////////////////////
// @Budget.cpp
//
// @author Eric Bruhns
//
////////////////////////////////////////////////////////////

#include "Budget.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

#include <conio.h>


namespace budget {
const int COLUMN_WIDTH = 25;

ostream& operator<<(ostream& os, const Expense& exp) {
    os << exp.name_ << "," << exp.value_ << "," << exp.fixed_ << "," << exp.income_ << "\n";
    return os;
}

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

    // Display updated list to the UI (todo)
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
    // Sum up all for vector expenses
    float fi_sum = 0.0;  // fixed-income sum
    float oti_sum = 0.0;  // one-time-income sum
    float fc_sum = 0.0;  // fixed-cost sum
    float otc_sum = 0.0;  // one-time-cost sum

    for(auto e : fixed_income_) {
        fi_sum = e + fi_sum; 
    }

    for(auto e : one_time_income_) {
        oti_sum = e + oti_sum;
    }

    for(auto e : fixed_cost_) {
        fc_sum = e + fc_sum;
    }

    for(auto e : one_time_cost_) {
        otc_sum = e + otc_sum;
    }

    return fi_sum + oti_sum - fc_sum - otc_sum;

}

/**
 * Set the profit when summed up
 * @param value The recent total of the expenses
*/
void Budget::setProfit(float value) {
    profit_ = value;
}

/**
 * Gets the profit of the budget
 * @return The Budget's profit
*/
float Budget::getProfit() const {
    return profit_;
}

/**
 * The string display of the entire budget to be displayed to
 * the user as well as be saved to the file
*/
void Budget::displayBudget() const {
    // Create an string stream
    stringstream ss;

    // Clear terminal
    system("cls");

    // Print the Budget headers
    // printf("%25s%25s%25s%25s", "Fixed Income", "Fixed Costs", "OT Income", "OT Costs");
    ss << setw(COLUMN_WIDTH) << left << "Fixed Income";
    ss << setw(COLUMN_WIDTH) << left << "Fixed Costs";
    ss << setw(COLUMN_WIDTH) << left << "OT Costs";
    ss << setw(COLUMN_WIDTH) << left << "OT Income";

    ss << endl;
    ss << string(COLUMN_WIDTH-2, '=') << "  "
       << string(COLUMN_WIDTH-2, '=') << "  "
       << string(COLUMN_WIDTH-2, '=') << "  "
       << string(COLUMN_WIDTH-2, '=') << "  "; 
    // cout << ss.str();
    ss << "\n";

    // Print the Expenses in the vector
    for(int line = 0; 
        line < fixed_income_.size() || 
        line < one_time_income_.size() ||
        line < fixed_cost_.size() ||
        line < one_time_cost_.size(); line++)
    {
        // Check if there's fixed income to print
        if(line < fixed_income_.size()) {
            ss << setw(COLUMN_WIDTH) << left << fixed_income_[line].name_ << " $" << setprecision(2) << fixed_income_[line].value_;
        }
        else {
            ss << setw(COLUMN_WIDTH) << " ";
        }

        // Check if there's fixed costs to print
        if(line < fixed_cost_.size()) {
            ss << setw(COLUMN_WIDTH) << left << fixed_cost_[line].name_ << " $" << setprecision(2) << fixed_cost_[line].value_;
        }
        else {
            ss << setw(COLUMN_WIDTH) << " ";
        }

        // Check if there's a one-time cost to print
        if(line < one_time_cost_.size()) {
            ss << setw(COLUMN_WIDTH) << left << one_time_cost_[line].name_ << " $" << setprecision(2) << one_time_cost_[line].value_;
        }
        else {
            ss << setw(COLUMN_WIDTH) << " ";
        }

        // Check if there's one time income to print
        if(line < one_time_income_.size()) {
            ss << setw(COLUMN_WIDTH) << left << one_time_income_[line].name_ << " $" << setprecision(2) << one_time_income_[line].value_;
        }
        else {
            ss << setw(COLUMN_WIDTH) << " ";
        }

        ss << "\n";
    }

    ss << string(COLUMN_WIDTH*4, '-') << " ";
    ss << setw(COLUMN_WIDTH*4) << left << "Total: $" << setprecision(2) << profit_;
    ss << "\n";

    cout << ss.str();

}

void Budget::saveExpenseToFile(const Expense& exp) {
    // open file with username
    string filename = username_ + "_expense_storage.csv";
    ofstream file;
    stringstream str;
    file.open(filename, ios::app);

    // check if open
    if(!file) {
        // Handle errors later
    } else {
        file << exp;
        file.close();  // Close file
    }
}

}  // namespace budget