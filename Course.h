#ifndef COURSE_H 
#define COURSE_H  
#include <string> 

class Course {
private:
    // private data members (encapsulation)
    std::string courseNumber;
    std::string courseName;   
    std::string schedule;   
    double price;            

public:
    // constructor: creates a "blank" course
    Course();

    // parameterized constructor: creates a course with specific details provided
    Course(std::string num, std::string name, std::string sched, double p);

    // getter methods: allows other classes (like Cart) to read the private data
    // marked as 'const' because they do not modify the object's data
    
    // returns the course number string
    std::string getCourseNumber() const { return courseNumber; }
    
    // returns the course name string
    std::string getCourseName() const { return courseName; }
    
    // returns the schedule string
    std::string getSchedule() const { return schedule; }
    
    // returns the price as a double
    double getPrice() const { return price; }
};

#endif
