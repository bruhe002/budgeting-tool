////////////////////////////////////////////////////////////
// @interface.cpp
//
// @author Eric Bruhns
//
////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <fstream>

#include <conio.h>

#include "../except/InvalidOptionException.h"

const std::string USER_DIR = "./store/users/";

const std::string USER_FILENAME = USER_DIR + "usr.txt";

int main() {
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
            std::cout << "Didnt open\n";
            if(!usr_file.is_open()) {
                usr_file.open(USER_FILENAME, std::ios::out);
                usr_file.close();
                usr_file.open(USER_FILENAME, std::ios::in);
            }

            while(getline(usr_file, line)) {
                if(line == input) {
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
            usr_file << input;
            usr_file.close();

            std::cout << input << " successfully added!\n";
            interface_on = false;

        } catch(std::exception& e) {
            std::cerr << e.what();
        }
    }
}