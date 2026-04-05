#ifndef INTERFACE_H
#define INTERFACE_H
#include <iostream>
#include <string>
#include <limits>
#include "Department.h"

// access global variables
// StoreDepartments is a dynamic array of Department objects
extern Department* StoreDepartments;
extern int TotalDepartments;

// base class: provides shared logic for input validation
class Interface {
public:
    // pure virtual function: makes this an abstract class 
    // derived classes MUST implement their own 'run' logic
    virtual void run() = 0; 
    virtual ~Interface() {}

    // validation: forces the user to enter an integer within a specific [min, max] range.
    int getValidInt(std::string prompt, int min, int max) {
        int choice;
        while(true) {
            std::cout << prompt;
            // checks if input is a number AND within range
            if (std::cin >> choice && choice >= min && choice <= max) return choice;
            std::cin.clear(); // clear error flags if user typed text instead of a number
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
            std::cout << "Invalid input. ";
        }
    }

    // validation: snsures the user doesn't leave a required text field empty
    std::string getNonEmptyString(std::string prompt) {
        std::string input;
        while (true) {
            std::cout << prompt;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer
            std::getline(std::cin, input); // capture the full line of text
            if (!input.empty()) return input;
        }
    }
};

// Admin Interface: controls for adding departments and courses
class AdminInterface : public Interface {
public:
    void run() override {
        while (true) {
            std::cout << "\n--- Admin Menu ---\n1. List Departments\n2. Add Department\n3. Add Course\n4. Save to CSV\n5. Exit\n";
            int choice = getValidInt("Enter your choice [1-5]: ", 1, 5);
            if (choice == 5) break;

            switch (choice) {
                case 1: listDepts(); break;
                case 2: addDept(); break;
                case 3: addCourseToDept(); break;
                case 4: saveCSV(); break;
            }
        }
    }

private:
    // loops through the global StoreDepartments array and prints names
    void listDepts() {
        for (int i = 0; i < TotalDepartments; i++) {
            std::cout << i + 1 << ". " << StoreDepartments[i].getName() << std::endl;
        }
    }

    // resizes the global StoreDepartments array to add a new department
    void addDept() {
        std::string name = getNonEmptyString("Enter department name: ");
        Department* temp = new Department[TotalDepartments + 1];
        for (int i = 0; i < TotalDepartments; i++) temp[i] = std::move(StoreDepartments[i]);
        
        temp[TotalDepartments].setName(name.c_str());
        delete[] StoreDepartments; // free old memory
        StoreDepartments = temp;
        TotalDepartments++;
        std::cout << "Department added successfully." << std::endl;
    }

    // adds a new Course object to a specific department selected by the user
    void addCourseToDept() {
        listDepts();
        int didx = getValidInt("Enter department number [0 to back]: ", 0, TotalDepartments) - 1;
        if (didx < 0) return;

        std::string num = getNonEmptyString("Enter course number: ");
        std::string name = getNonEmptyString("Enter course name: ");

        // loop to ensure the schedule format is one of the three allowed codes
        std::string sched;
        while(true) {
            std::cout << "Enter schedule (M/W, T/R, W/F): ";
            std::cin >> sched;
            if(sched == "M/W" || sched == "T/R" || sched == "W/F") break;
        }

        double price;
        std::cout << "Enter price: ";
        std::cin >> price;

        // calls the addCourse method within the specific Department object
        StoreDepartments[didx].addCourse(Course(num, name, sched, price));
        std::cout << "Course added successfully." << std::endl;
    }

    void saveCSV(); // Placeholder for saving logic.
};

// Student Interface: controls for browsing courses and using the shopping cart
#include "Cart.h"
class StudentInterface : public Interface {
    Cart studentCart; // student's private shopping cart instance
public:
    void run() override {
        while (true) {
            std::cout << "\n--- Student Menu ---\n1. Show Cart\n2. Browse Departments\n3. Exit\n";
            int choice = getValidInt("Enter choice [1-3]: ", 1, 3);
            if (choice == 3) break;

            if (choice == 1) {
                std::cout << "1. List Courses\n2. Checkout\n3. Back\n";
                int c = getValidInt("Choice: ", 1, 3);
                if (c == 1) studentCart.listCart();
                else if (c == 2) studentCart.checkout();
            } else {
                browse(); // go to the department/course selection logic
            }
        }
    }

    // Browsing Logic: shows departments, then courses, then lets student add one to cart
    void browse() {
        for (int i = 0; i < TotalDepartments; i++)
            std::cout << i + 1 << ". " << StoreDepartments[i].getName() << std::endl;
        
        int didx = getValidInt("Select Dept [0 back]: ", 0, TotalDepartments) - 1;
        if (didx < 0) return;

        Course* cList = StoreDepartments[didx].getCourses();
        int count = StoreDepartments[didx].getTotalCourses();
        for (int i = 0; i < count; i++)
            std::cout << i + 1 << ". " << cList[i].getCourseName() << " - $" << cList[i].getPrice() << std::endl;

        int buy = getValidInt("Add course # to cart [0 back]: ", 0, count) - 1;
        if (buy >= 0) {
            studentCart.addCourse(cList[buy]); // adds the chosen course to the student's cart.
            std::cout << "Added!" << std::endl;
        }
    }
};

#endif
