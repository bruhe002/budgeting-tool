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
#include <algorithm>

#include <conio.h>


namespace budget {
const int COLUMN_WIDTH = 30;
const string COLUMN_SPACE = "  ";
const int DISPLAY_WIDTH = (COLUMN_WIDTH + COLUMN_SPACE.size()) * 4;
const string EXPENSE_STORAGE = "expense_store/";

ostream& operator<<(ostream& os, const Expense& exp) {
    os << exp.name_ << "," << exp.value_ << "," << exp.type_ << "\n";
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
{
    // Create a file with the name
    string filename = getStoreName();
    FILE* file = fopen(filename.c_str(), "r");

    if(!file) {
        // File Doesn't exist
        file = fopen(filename.c_str(), "w");
        fprintf(file, "Name,value,costtype\n");

    } else {
        char* name;
        CostType type;
        float value; 
        while(fscanf(file, "%[^,]%f%i", name, value, type)) {
            addExpenseToBudget(Expense{name, value, type});
        }
    }

    fclose(file);

}

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
    addExpenseToBudget(exp);

    // After the expense is added to the appropriate vector
    // save it to storage file
    // Need to check if the expense exists
    // saveExpenseToFile(exp);
}

string Budget::getStoreName() {
    return username_ + "_expense_store.csv";
}

/**
 * Deletes an expense from the budget class
 * @name Name of struct to be deleted
*/
void Budget::deleteExpense(const CostType& type) {
    vector<Expense> list;
    switch(type) {
        case FIXED_I:
            copy(fixed_income_.begin(), fixed_income_.end(), back_inserter(list));
            break;
        case FIXED_C:
            copy(fixed_cost_.begin(), fixed_cost_.end(), back_inserter(list));
            break;
        case ONE_TIME_C:
            copy(one_time_cost_.begin(), one_time_cost_.end(), back_inserter(list));
            break;
        case ONE_TIME_I:
            copy(one_time_income_.begin(), one_time_income_.end(), back_inserter(list));
            break;
    }

    cout << "Choose an expense to delete: \n";

    for(int i = 0; i < list.size();) {
        cout << "\t" << ++i << ". " << list[i];
    }

    uint32_t choice = 0;
    while(choice > list.size()) {
        try {
            cin >> choice;
            if (choice > list.size()) {
                throw;
            } else {
                list.erase(list.begin() + choice);
            }
        } catch (exception& e) {
            cerr << "Invalid choice. Please try again!\n";
        }
    }

    switch(type) {
        case FIXED_I:
            fixed_income_.clear();
            copy(list.begin(), list.end(), back_inserter(fixed_income_));
            break;
        case FIXED_C:
            fixed_cost_.clear();
            copy(list.begin(), list.end(), back_inserter(fixed_cost_));
            break;
        case ONE_TIME_C:
            one_time_cost_.clear();
            copy(list.begin(), list.end(), back_inserter(one_time_cost_));
            break;
        case ONE_TIME_I:
            one_time_income_.clear();
            copy(list.begin(), list.end(), back_inserter(one_time_income_));
            break;
    }
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
float Budget::sumUpExpenses() const {
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
    ss << "  ";
    ss << setw(COLUMN_WIDTH) << left << "Fixed Costs";
    ss << "  ";
    ss << setw(COLUMN_WIDTH) << left << "OT Costs";
    ss << "  ";
    ss << setw(COLUMN_WIDTH) << left << "OT Income";

    ss << endl;
    ss << string(COLUMN_WIDTH, '=') << COLUMN_SPACE
       << string(COLUMN_WIDTH, '=') << COLUMN_SPACE
       << string(COLUMN_WIDTH, '=') << COLUMN_SPACE
       << string(COLUMN_WIDTH, '=') << COLUMN_SPACE; 

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
            ss << setw(COLUMN_WIDTH/2) << left << fixed_income_[line].name_ 
                << setw((COLUMN_WIDTH/2)) << right << fixed << setprecision(2) 
                << fixed_income_[line].value_ << COLUMN_SPACE;
        }
        else {
            ss << setw(COLUMN_WIDTH+2) << COLUMN_SPACE;
        }

        // Check if there's fixed costs to print
        if(line < fixed_cost_.size()) {
            ss << setw(COLUMN_WIDTH/2) << left << fixed_cost_[line].name_ 
                << setw((COLUMN_WIDTH/2)) << right << fixed << setprecision(2) 
                << fixed_cost_[line].value_ << COLUMN_SPACE;
        }
        else {
            ss << setw(COLUMN_WIDTH+2) << COLUMN_SPACE;
        }

        // Check if there's a one-time cost to print
        if(line < one_time_cost_.size()) {
            ss << setw(COLUMN_WIDTH/2) << left << one_time_cost_[line].name_ 
                << setw((COLUMN_WIDTH/2)) << right << fixed << setprecision(2) 
                << one_time_cost_[line].value_ << COLUMN_SPACE;
        }
        else {
            ss << setw(COLUMN_WIDTH+2) << COLUMN_SPACE;
        }

        // Check if there's one time income to print
        if(line < one_time_income_.size()) {
            ss << setw(COLUMN_WIDTH/2) << left << one_time_income_[line].name_ 
                << setw((COLUMN_WIDTH/2)) << right << fixed << setprecision(2) 
                << one_time_income_[line].value_ << COLUMN_SPACE;
        }
        else {
            ss << setw(COLUMN_WIDTH+2) << COLUMN_SPACE;
        }

        ss << "\n";
    }

    ss << string(DISPLAY_WIDTH, '-');
    ss << "\n";

    stringstream total;
    total << "Total: $" << fixed << setprecision(2) << sumUpExpenses();
    ss << setw(DISPLAY_WIDTH) << right << total.str();
    ss << "\n";

    // Displays Budget to UI
    cout << ss.str();

}

void Budget::saveExpenseToFile(const Expense& exp) {
    // open file with username
    ofstream file;
    stringstream str;
    file.open(getStoreName(), ios::app);

    // check if open
    if(!file) {
        // Handle errors later
    } else {
        file << exp;
        file.close();  // Close file
    }
}

}  // namespace budget