#include "Department.h"

Department::Department() : courses(nullptr), totalCourses(0) {
    deptName[0] = '\0';
}

Department::~Department() {
    delete[] courses;
}

void Department::setName(const char* name) {
    strncpy(deptName, name, 99);
    deptName[99] = '\0';
}

const char* Department::getName() const { return deptName; }
int Department::getTotalCourses() const { return totalCourses; }
Course* Department::getCourses() const { return courses; }

void Department::addCourse(const Course& newCourse) {
    // create new array with size + 1
    Course* temp = new Course[totalCourses + 1];
    for (int i = 0; i < totalCourses; i++) {
        temp[i] = courses[i];
    }
    temp[totalCourses] = newCourse;
    
    delete[] courses; // clean old memory
    courses = temp;
    totalCourses++;
}