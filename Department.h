#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "Course.h"
#include <cstring>

class Department {
private:
    char deptName[100]; // character array for name
    Course* courses;    // dynamically allocated array
    int totalCourses;  

public:
    Department();
    ~Department(); // destructor to clear courses 
    
    void setName(const char* name);
    const char* getName() const;
    int getTotalCourses() const;
    Course* getCourses() const;
    
    void addCourse(const Course& newCourse); // manually resizes array
};

#endif