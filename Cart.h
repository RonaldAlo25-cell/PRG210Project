#ifndef CART_H
#define CART_H 
#include "Course.h"
#include <string>  

class Cart {
private:
    // pointers used to manage dynamic arrays in memory
    Course* selectedCourses;   // pointer to a dynamic array of Course objects
    std::string* schedules;    // pointer to a dynamic array of strings for course schedules
    
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
