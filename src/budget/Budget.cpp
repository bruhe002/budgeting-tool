////////////////////////////////////////////////////////////
// @Budget.cpp
//
// @author Eric Bruhns
//
////////////////////////////////////////////////////////////

#include "Budget.h"
#include "../except/InvalidOptionException.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <ctime>

#include <sys/stat.h>
#include <conio.h>

std::pair<string, string> getCurrentTime(){
    // Create the time
    stringstream time_ss;
    time_t curr_time;
    time(&curr_time);
    time_ss << asctime(localtime(&curr_time));
    string day;
    string month;
    string num_day;
    string time;
    string year;
    time_ss >> day >> month >> num_day >> time >> year;

    return std::make_pair(month, year);
}


namespace budget {
const int COLUMN_WIDTH = 30;
const string COLUMN_SPACE = "  ";
const int DISPLAY_WIDTH = (COLUMN_WIDTH + COLUMN_SPACE.size()) * 4;
const string EXPENSE_DIR = "store/expenses/";

ostream& operator<<(ostream& os, const Expense& exp) {
    os << exp.toString();
    return os;
}

/**
 * Default Constructor
*/
Budget::Budget() 
    : username_("test_user"),
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
    // Read budgets from storage
    ifstream exp_file;

    exp_file.open(EXPENSE_DIR + username_ + "_expense_store.csv", ios::in);

    if(!exp_file.is_open()) {
        cerr << "WARNING: No Expenses saved for user. Creating a new storage now.\n";
        exp_file.open(EXPENSE_DIR + username_ + "_expense_store.csv", ios::out);
        exp_file.close();
    } else {
        // Get current time
        pair<string, string> current_time = getCurrentTime();
        
        // Set variables to read from file
        string exp_name;
        string exp_value;
        string exp_type;
        string exp_month;
        string exp_year;

        // set up variable for each line
        string line;
        // Get the row
        while(getline(exp_file, line)) {
            // create the stream
            stringstream ss(line);
            char delim = ',';

            // Extract each attribute in order
            getline(ss, exp_name, delim);
            getline(ss, exp_value, delim);
            getline(ss, exp_type, delim);
            getline(ss, exp_month, delim);
            getline(ss, exp_year, delim);

            if(exp_month == current_time.first && exp_year == current_time.second) {
                // convert the values
                unsigned int exp_type_int = std::stoi(exp_type);
                float exp_value_float = std::stof(exp_value);
                
                // figure out which vector to push the expense value in
                switch(exp_type_int) {
                    case 0:
                        fixed_income_.push_back({exp_name, exp_value_float, CostType::FIXED_I, exp_month, exp_year});
                        break;
                    case 1:
                        fixed_cost_.push_back({exp_name, exp_value_float, CostType::FIXED_C, exp_month, exp_year});
                        break;
                    case 2:
                        one_time_cost_.push_back({exp_name, exp_value_float, CostType::ONE_TIME_C, exp_month, exp_year});
                        break;
                    case 3:
                        one_time_income_.push_back({exp_name, exp_value_float, CostType::ONE_TIME_I, exp_month, exp_year});
                        break;
                }
            }
        }

        exp_file.close();
    }
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
    saveExpenseToFile(exp);

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

    uint32_t choice = 0;
    bool choice_flag = true;
    while(choice_flag) {
        cout << "Choose an expense to delete: \n";

        for(int i = 0; i < list.size(); i++) {
            cout << "\t" << i+1 << ". " << list[i] << endl;
        }
        try {
            cin >> choice;
            --choice;
            if (choice >= list.size()) {
                throw except::InvalidOptionException();
            } else {
                Expense exp_to_delete = *(list.begin() + choice);
                deleteExpenseFromFile(exp_to_delete);
                list.erase(list.begin() + choice);
                choice_flag = false;
            }
        } catch (exception& e) {
            cin.clear();  // Clear the error state
            cin.ignore(std::numeric_limits<streamsize>::max(),'\n'); // Clear the rest of the input
            cerr << e.what() << endl;
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
void Budget::exportToFile() const {
    std::pair<string, string> current_time = getCurrentTime();

    string filename = "./store/budgets/" + username_ + "_budget_" + current_time.first + "_" + current_time.second + ".txt";

    // Check if storage directory exists
    const char* path = "store/budgets";
    struct stat sb;

    if(stat(path, &sb) != 0) {
        mkdir(path);
    }

    ofstream file;
    file.open(filename, ios::out);

    if(file.is_open()) {
        file << displayBudget();
    }
    else {
        cerr << "File could not be opened...\n";
    }

    file.close();
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
string Budget::displayBudget() const {
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
    return ss.str();

}

void Budget::saveExpenseToFile(const Expense& exp) {
    // open file with username
    ofstream file;
    stringstream str;
    file.open(EXPENSE_DIR + username_ + "_expense_store.csv", ios::app);

    // check if open
    if(!file) {
        // Handle errors later
        file.open(EXPENSE_DIR + username_ + "_expense_store.csv", ios::out);
        file.close();
        file.open(EXPENSE_DIR + username_ + "_expense_store.csv", ios::app);
    }

    file << exp << endl;
    file.close();  // Close file
}

void Budget::deleteExpenseFromFile(const Expense& exp) {
    // Open the file
    fstream exp_file;
    exp_file.open(EXPENSE_DIR + username_ + "_expense_store.csv", ios::in);

    if(!exp_file.is_open()) {
        cerr << "WARNING: Could not open file!\n";
    } else {
        string line;
        stringstream ss;
        
        // Add lines to a string stream
        while(getline(exp_file, line)) {
            if(line != exp.toString()) {
                ss << line << "\n";
            }
        }
        exp_file.close();
        exp_file.open(EXPENSE_DIR + username_ + "_expense_store.csv", ios::out);
        // add string stream to file
        exp_file << ss.str();

        exp_file.close();
    }
}

}  // namespace budget