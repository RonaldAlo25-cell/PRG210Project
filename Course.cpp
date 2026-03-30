#include "Course.h"

Course::Course() : courseNumber(""), courseName(""), schedule(""), price(0.0) {}

Course::Course(std::string num, std::string name, std::string sched, double p) 
    : courseNumber(num), courseName(name), schedule(sched), price(p) {}