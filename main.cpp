#include <iostream>
#include <fstream>
#include "Department.h"
#include "Interface.h"

// global variables
Department* StoreDepartments = nullptr;
int TotalDepartments = 0;
const char* csvFile = "data.csv";

void AdminInterface::saveCSV() {
    std::ofstream file(csvFile);
    file << TotalDepartments << "\n";
    for (int i = 0; i < TotalDepartments; i++) {
        file << StoreDepartments[i].getName() << "," << StoreDepartments[i].getTotalCourses() << "\n";
        Course* c = StoreDepartments[i].getCourses();
        for (int j = 0; j < StoreDepartments[i].getTotalCourses(); j++) {
            file << c[j].getCourseName() << "," << c[j].getSchedule() << "," << c[j].getPrice() << "\n";
        }
    }
    std::cout << "Changes saved successfully." << std::endl;
}

void loadCSV() {
    std::ifstream file(csvFile);
    if (!file.is_open()) return;
    
    file >> TotalDepartments;
    StoreDepartments = new Department[TotalDepartments];
    for (int i = 0; i < TotalDepartments; i++) {
        std::string dName; int cCount;
        file.ignore();
        std::getline(file, dName, ',');
        file >> cCount;
        StoreDepartments[i].setName(dName.c_str());
        for (int j = 0; j < cCount; j++) {
            std::string cName, sched; double p;
            file.ignore();
            std::getline(file, cName, ',');
            std::getline(file, sched, ',');
            file >> p;
            StoreDepartments[i].addCourse(Course("N/A", cName, sched, p));
        }
    }
}

// main function
int main() {
    loadCSV();

    while (true) {
        std::cout << "\n1. Student\n2. Admin\n3. Exit\n";
        int role;
        std::cout << "Enter choice [1, 2, 3]: ";
        std::cin >> role;

        if (role == 3) break;

        Interface* ui = nullptr;
        if (role == 1) ui = new StudentInterface();
        else if (role == 2) ui = new AdminInterface();
        
        if (ui) {
            ui->run(); // polymorphism
            delete ui;
        }
    }

    delete[] StoreDepartments;
    return 0;
}