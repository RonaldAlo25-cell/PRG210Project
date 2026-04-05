#include "Department.h"

// constructor: initializes the course list to null and the count to 0
// sets the department name to an empty string by null-terminating the first character
Department::Department() : courses(nullptr), totalCourses(0) {
    deptName[0] = '\0'; 
}

// destructor: frees the dynamically allocated memory for the courses array
// prevents memory leaks when the Department object is destroyed
Department::~Department() {
    delete[] courses;
}

// sets the department name using C-style string copying
void Department::setName(const char* name) {
    // strncpy copies up to 99 characters to avoid overflowing the deptName buffer
    strncpy(deptName, name, 99);
    // explicitly null-terminates the last index to ensure the string is valid even if truncated
    deptName[99] = '\0';
}

// getter: returns a pointer to the department's name string
const char* Department::getName() const { return deptName; }

// getter: returns the current number of courses in the department
int Department::getTotalCourses() const { return totalCourses; }

// getter: returns the pointer to the dynamic array of Course objects
Course* Department::getCourses() const { return courses; }

// logic to add a new course by resizing the dynamic array
void Department::addCourse(const Course& newCourse) {
    // creates a new temporary array that is one slot larger than the current count
    Course* temp = new Course[totalCourses + 1];

    // copies all existing Course objects into the new temporary array
    for (int i = 0; i < totalCourses; i++) {
        temp[i] = courses[i];
    }

    // places the new course into the final available slot
    temp[totalCourses] = newCourse;

    // deallocates the memory used by the old, smaller array
    delete[] courses; // clean old memory

    // points the member variable to the new, larger array and update the count
    courses = temp;
    totalCourses++;
}
