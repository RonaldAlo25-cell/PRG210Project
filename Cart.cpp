#include "Cart.h"
#include <iostream>

Cart::Cart() : selectedCourses(nullptr), schedules(nullptr), count(0), totalCost(0.0) {}

Cart::~Cart() {
    delete[] selectedCourses;
    delete[] schedules;
}

void Cart::addCourse(const Course& c) {
    Course* tempC = new Course[count + 1];
    std::string* tempS = new std::string[count + 1];
    
    for(int i = 0; i < count; i++) {
        tempC[i] = selectedCourses[i];
        tempS[i] = schedules[i];
    }
    
    tempC[count] = c;
    tempS[count] = c.getSchedule();
    
    delete[] selectedCourses;
    delete[] schedules;
    
    selectedCourses = tempC;
    schedules = tempS;
    totalCost += c.getPrice();
    count++;
}

void Cart::listCart() const {
    for(int i = 0; i < count; i++) {
        std::cout << selectedCourses[i].getCourseNumber() << " - " 
                  << selectedCourses[i].getCourseName() << " (" 
                  << schedules[i] << ") $" << selectedCourses[i].getPrice() << std::endl;
    }
}

void Cart::checkout() {
    if (count > 0) {
        // calculate price with 13% tax
        double finalTotal = totalCost * 1.13; 
        std::cout << "Total (inc. 13% tax): $" << finalTotal << "\nThank you for your purchase!" << std::endl;
        
        delete[] selectedCourses;
        delete[] schedules;
        selectedCourses = nullptr;
        schedules = nullptr;
        count = 0;
        totalCost = 0.0;
    } else {
        std::cout << "No courses in the cart" << std::endl;
    }
}