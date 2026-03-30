#ifndef CART_H
#define CART_H

#include "Course.h"
#include <string>

class Cart {
private:
    Course* selectedCourses;
    std::string* schedules; // schedule array
    int count;
    double totalCost;

public:
    Cart();
    ~Cart();
    void addCourse(const Course& c);
    void listCart() const;
    void checkout();
    int getCount() const { return count; }
};

#endif