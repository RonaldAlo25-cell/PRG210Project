#include <iostream>
#include <fstream>
#include "Department.h"
#include "Interface.h"

// global variables to store the application state across different classes
Department* StoreDepartments = nullptr; // dynamic array of Department objects
int TotalDepartments = 0;              // current number of departments loaded
const char* csvFile = "data.csv";      // filename for persistent storage

// implementation of the saveCSV method declared in AdminInterface
void AdminInterface::saveCSV() {
    std::ofstream file(csvFile);       // open file for writing
    file << TotalDepartments << "\n";  // save the header count first
    for (int i = 0; i < TotalDepartments; i++) {
        // Save department metadata: Name and how many courses it has.
        file << StoreDepartments[i].getName() << "," << StoreDepartments[i].getTotalCourses() << "\n";
        Course* c = StoreDepartments[i].getCourses();
        for (int j = 0; j < StoreDepartments[i].getTotalCourses(); j++) {
            // save individual course details separated by commas
            file << c[j].getCourseName() << "," << c[j].getSchedule() << "," << c[j].getPrice() << "\n";
        }
    }
    std::cout << "Changes saved successfully." << std::endl;
}

// loads the data from the CSV file back into the dynamic arrays upon startup
void loadCSV() {
    std::ifstream file(csvFile);
    if (!file.is_open()) return; // if no file exists (first run), exit the function

    file >> TotalDepartments;    // read how many departments were saved
    StoreDepartments = new Department[TotalDepartments]; // allocate the main array
    for (int i = 0; i < TotalDepartments; i++) {
        std::string dName; int cCount;
        file.ignore();           // skip the newline character from the previous read
        std::getline(file, dName, ','); // read department name up to the comma
        file >> cCount;          // read how many courses are in this department
        StoreDepartments[i].setName(dName.c_str());

        for (int j = 0; j < cCount; j++) {
            std::string cName, sched; double p;
            file.ignore();
            std::getline(file, cName, ',');
            std::getline(file, sched, ',');
            file >> p;
            // reconstruct the Course object and add it to the department
            StoreDepartments[i].addCourse(Course("N/A", cName, sched, p));
        }
    }
}

// the main function
int main() {
    loadCSV(); // load existing data as soon as the program starts

    while (true) {
        std::cout << "\n1. Student\n2. Admin\n3. Exit\n";
        int role;
        std::cout << "Enter choice [1, 2, 3]: ";
        std::cin >> role;

        if (role == 3) break; // exit the loop and close the program

        Interface* ui = nullptr; // pointer to the base class for polymorphism
        if (role == 1) ui = new StudentInterface(); // create student view
        else if (role == 2) ui = new AdminInterface(); // create admin view

        if (ui) {
            ui->run();      // polymorphism: program decides which run() to call at runtime
            delete ui;      // cleans up the interface object to prevent memory leaks
        }
    }

    // final: free the global dynamic array before the program fully terminates
    delete[] StoreDepartments; 
    return 0;
}
