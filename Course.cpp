#include "Course.h"

// constructor: runs when you create a Course object without providing any data
// uses an "Initializer List" to set strings to empty and the price to zero
Course::Course() : courseNumber(""), courseName(""), schedule(""), price(0.0) {}

// parameterized constructor: runs when you create a Course and provide specific details
// takes four inputs (num, name, sched, p) and assigns them to the class's private member variables
Course::Course(std::string num, std::string name, std::string sched, double p) 
    : courseNumber(num), courseName(name), schedule(sched), price(p) {}
