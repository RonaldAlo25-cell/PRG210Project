#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
private:
    std::string courseNumber;
    std::string courseName;
    std::string schedule;
    double price;

public:
    Course();
    Course(std::string num, std::string name, std::string sched, double p);
    
    // getter methods
    std::string getCourseNumber() const { return courseNumber; }
    std::string getCourseName() const { return courseName; }
    std::string getSchedule() const { return schedule; }
    double getPrice() const { return price; }
};

#endif