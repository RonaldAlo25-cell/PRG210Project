#ifndef CART_H
#define CART_H 
#include "Course.h"
#include <string>  
/*
The Cart class simulates a shopping cart system where students can:
-Add courses
-View selected courses
-Checkout (includes taxes)
*/

class Cart {
private:
    // These pointers track course objects and schedule strings respectively.
    Course* selectedCourses;   // pointer to a dynamic array of Course objects
    std::string* schedules;    // pointer to a dynamic array of strings for course schedules
    // These variables track the amount courses and their total price.
    int count;                 // tracks the number of courses currently in the cart
    double totalCost;          // tracks the cumulative price of all courses in the cart

public:
    // Constructor: initializes a new, empty Cart object
    Cart();

    // destructor: cleans up dynamic memory when the Cart object is destroyed
    ~Cart();

    // adds a Course object to the cart
    void addCourse(const Course& c);

    // prints a list of all courses in the cart to the console
    void listCart() const;

    // calculates the final total (with tax) and empties the cart
    void checkout();

    // getter: returns the current number of courses in the cart.
    int getCount() const { return count; }
};

#endif
