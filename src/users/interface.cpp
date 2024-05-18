////////////////////////////////////////////////////////////
// @interface.cpp
//
// @author Eric Bruhns
//
////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sys/stat.h>

int main() {
    std::cout << std::string(10, '-')  << "SIGN-UP FOR BUDGET" << std::string(10, '-') << std::endl;
    bool interface_on = true;

    // start the while loop
    while(interface_on) {
        // Ask user to enter a username
        std::cout << "\nEnter a username for your budget: ";

        // Need to check if the name exists in the file 
        // Check if storage directory exists
        const char* path = "store/users";
        struct stat sb;

        if(stat(path, &sb) != 0) {
            mkdir(path);
        }
    }
}