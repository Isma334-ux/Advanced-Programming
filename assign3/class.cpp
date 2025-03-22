#include "class.h"
#include <iostream>
#include <cstring> // For strcpy and strlen

Student::Student() : age(0), gpa(0.0) {
    strcpy(name, "Unknown");
}

Student::Student(const char* name, int age, double gpa)
    : age(age), gpa(gpa) {
    strncpy(this->name, name, 50);
    this->name[50] = '\0'; // Ensure null-termination
}

void Student::updateGPA(double adjustment) {
    gpa += adjustment;
    if (gpa < 0.0) gpa = 0.0;
    if (gpa > 4.0) gpa = 4.0;
}

const char (&Student::getName() const)[50] {
    return name; // Return a reference to the char[50] array
}

int Student::getAge() const {
    return age;
}

double Student::getGPA() const {
    return gpa;
}

void Student::setName(const char* newName) {
    strncpy(name, newName, 50);
    name[50] = '\0'; // Ensure null-termination
}

void Student::setAge(int newAge) {
    age = newAge;
}

void Student::setGPA(double newGPA) {
    gpa = newGPA;
    updateGPA(0.0);
}

void Student::displayInfo() const {
    std::cout << "Name: " << name << "\n"
              << "Age: " << age << "\n"
              << "GPA: " << gpa << "\n";
}