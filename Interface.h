#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include <limits>
#include "Department.h"

// access global variables
extern Department* StoreDepartments;
extern int TotalDepartments;

class Interface {
public:
    virtual void run() = 0; // virtual function for polymorphism
    virtual ~Interface() {}

    // validation methods
    int getValidInt(std::string prompt, int min, int max) {
        int choice;
        while (true) {
            std::cout << prompt;
            if (std::cin >> choice && choice >= min && choice <= max) return choice;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. ";
        }
    }
    
    std::string getNonEmptyString(std::string prompt) {
        std::string input;
        while (true) {
            std::cout << prompt;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, input);
            if (!input.empty()) return input;
        }
    }
};

// admin interface class
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
    void listDepts() {
        for (int i = 0; i < TotalDepartments; i++) 
            std::cout << i + 1 << ". " << StoreDepartments[i].getName() << std::endl;
    }

    void addDept() {
        std::string name = getNonEmptyString("Enter department name: ");
        Department* temp = new Department[TotalDepartments + 1];
        for (int i = 0; i < TotalDepartments; i++) temp[i] = std::move(StoreDepartments[i]);
        
        temp[TotalDepartments].setName(name.c_str());
        delete[] StoreDepartments;
        StoreDepartments = temp;
        TotalDepartments++;
        std::cout << "Department added successfully." << std::endl;
    }

    void addCourseToDept() {
        listDepts();
        int dIdx = getValidInt("Enter department number [0 to back]: ", 0, TotalDepartments) - 1;
        if (dIdx < 0) return;

        std::string num = getNonEmptyString("Enter course number: ");
        std::string name = getNonEmptyString("Enter course name: ");
        
        std::string sched;
        while(true) {
            std::cout << "Enter schedule (M/W, T/R, W/F): ";
            std::cin >> sched;
            if(sched == "M/W" || sched == "T/R" || sched == "W/F") break;
        }
        
        double price;
        std::cout << "Enter price: ";
        std::cin >> price;

        StoreDepartments[dIdx].addCourse(Course(num, name, sched, price));
        std::cout << "Course added successfully." << std::endl;
    }

    void saveCSV(); 
};

// student interface class
#include "Cart.h"
class StudentInterface : public Interface {
    Cart studentCart;
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
                browse();
            }
        }
    }

    void browse() {
        for (int i = 0; i < TotalDepartments; i++) 
            std::cout << i + 1 << ". " << StoreDepartments[i].getName() << std::endl;
        int dIdx = getValidInt("Select Dept [0 back]: ", 0, TotalDepartments) - 1;
        if (dIdx < 0) return;

        Course* cList = StoreDepartments[dIdx].getCourses();
        int count = StoreDepartments[dIdx].getTotalCourses();
        for (int i = 0; i < count; i++) 
            std::cout << i + 1 << ". " << cList[i].getCourseName() << " $" << cList[i].getPrice() << std::endl;

        int buy = getValidInt("Add course # to cart [0 back]: ", 0, count) - 1;
        if (buy >= 0) {
            studentCart.addCourse(cList[buy]);
            std::cout << "Added!" << std::endl;
        }
    }
};

#endif