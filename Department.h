#ifndef DEPARTMENT_H
#define DEPARTMENT_H 
#include "Course.h" 
#include <cstring>   

class Department {
private:
    // fixed-size array of 100 characters to store the department name.
    char deptName[100]; 
    
    // pointer that will point to a dynamically allocated array of Course objects
    Course* courses;    
    
    // integer to track the current number of courses in the dynamic array
    int totalCourses;

public:
    // constructor: initializes the Department's state (sets count to 0, pointers to null)
    Department();

    // destructor: cleaning up the dynamic 'courses' array
    ~Department(); 

    // setter: takes a C-string as input to update the department's name
    void setName(const char* name);

    // getter: returns a constant pointer to the department's name buffer
    const char* getName() const;

    // getter: returns the current total number of courses
    int getTotalCourses() const;

    // getter: returns the memory address (pointer) where the courses are stored
    Course* getCourses() const;

    // function to add a course, resizing the dynamic array in memory
    void addCourse(const Course& newCourse); 
};

#endif
