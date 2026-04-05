#include "Cart.h"
#include <iostream>

// constructor: initializes the cart with no courses, null pointers, and zero cost
Cart::Cart() : selectedCourses(nullptr), schedules(nullptr), count(0), totalCost(0.0) {}

// destructor: ensures that dynamically allocated memory is freed when the Cart object is destroyed
Cart::~Cart() {
    delete[] selectedCourses; // Deallocates the array of Course objects
    delete[] schedules;       // Deallocates the array of schedule strings
}

// adds a new course to the cart by resizing the internal arrays.
void Cart::addCourse(const Course& c) {
    // creates new temporary arrays that are one slot larger than the current count
    Course* tempC = new Course[count + 1];
    std::string* tempS = new std::string[count + 1];

    // copies existing data from the old arrays into the new, larger arrays
    for(int i = 0; i < count; i++) {
        tempC[i] = selectedCourses[i];
        tempS[i] = schedules[i];
    }

    // adds the new course and its schedule to the last index of the new arrays
    tempC[count] = c;
    tempS[count] = c.getSchedule();

    // free the memory used by the old, smaller arrays
    delete[] selectedCourses;
    delete[] schedules;

    // pointing the class members to the new, larger arrays
    selectedCourses = tempC;
    schedules = tempS;
    
    // updating the total cost and increment the course count
    totalCost += c.getPrice();
    count++;
}

// displaying all courses currently in the cart to the console
void Cart::listCart() const {
    for(int i = 0; i < count; i++) {
        std::cout << selectedCourses[i].getCourseNumber() << " - "
                  << selectedCourses[i].getCourseName() << " ("
                  << schedules[i] << ") $" << selectedCourses[i].getPrice() << std::endl;
    }
}

// finalizing the purchase, calculates tax, and clears the cart memory
void Cart::checkout() {
    if (count > 0) {
        // calculate price with 13% tax
        double finalTotal = totalCost * 1.13;
        std::cout << "Total (inc. 13% tax): $" << finalTotal << "\nThank you for your purchase!" << std::endl;

        // freeing the dynamic memory after checkout
        delete[] selectedCourses;
        delete[] schedules;
        
        // resetting all member variables to their initial state
        selectedCourses = nullptr;
        schedules = nullptr;
        count = 0;
        totalCost = 0.0;
    } else {
        // if the cart was empty, inform the user
        std::cout << "No courses in the cart" << std::endl;
    }
}
