////////////////////////////////////////////////////////////
// @interface.cpp
//
// @author Eric Bruhns
//
////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <ctime>

#include <sys/stat.h>
#include <conio.h>

#include "../except/InvalidOptionException.h"

const std::string USER_DIR = "./store/users/";

const std::string USER_FILENAME = USER_DIR + "usr.txt";

const char DELIM = ',';

std::pair<std::string, std::string> getCurrentTime(){
    // Create the time
    std::stringstream time_ss;
    time_t curr_time;
    time(&curr_time);
    time_ss << asctime(localtime(&curr_time));
    std::string day;
    std::string month;
    std::string num_day;
    std::string time;
    std::string year;
    time_ss >> day >> month >> num_day >> time >> year;

    return std::make_pair(month, year);
}

int main() {
    system("cls");
    system("clear");
    std::cout << std::string(10, '-')  << "SIGN-UP FOR BUDGET" << std::string(10, '-') << std::endl;
    bool interface_on = true;

    // start the while loop
    while(interface_on) {
        // Ask user to enter a username
        std::cout << "\nEnter a username for your budget: ";
        std::string input;
        getline(std::cin, input);

        if(input == "quit") {
            exit(0);
        }

        // Need to check if the name exists in the file 
        // Check if storage directory exists
        std::fstream usr_file;
        usr_file.open(USER_FILENAME, std::ios::in);

        std::string line = "";
        // Check if username is in the file
        try {
            if(!usr_file.is_open()) {
                usr_file.open(USER_FILENAME, std::ios::out);
                usr_file.close();
                usr_file.open(USER_FILENAME, std::ios::in);
            }

            while(getline(usr_file, line)) {
                std::stringstream ss(line);
                std::string name;
                std::string month;
                std::getline(ss, name, DELIM);
                std::getline(ss, month, DELIM);
                if(name == input) {
                    usr_file.close();
                    throw except::InvalidOptionException("ERROR: Username already exists! Please try again!\n");
                } else if(line == "quit") {
                    interface_on = false;
                    throw except::InvalidOptionException("");
                }
                // If the input doesn't match the line, do nothing
            }

            // If we pass the loop, add the username
            usr_file.close();
            usr_file.open(USER_FILENAME, std::ios::app);
            if(!usr_file.is_open()) {
                throw except::InvalidOptionException("ERROR: File failed to open!\n");
            }

            // Get the current month
            std::pair<std::string, std::string> current_date = getCurrentTime();

            usr_file << input + DELIM + current_date.first + "\n";
            usr_file.close();

            std::cout << input << " successfully added!\n";
            interface_on = false;

        } catch(std::exception& e) {
            std::cerr << e.what();
        }
    }
}