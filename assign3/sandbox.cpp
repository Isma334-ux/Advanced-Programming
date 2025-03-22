#include "class.h"

void sandbox() {
    Student student1("Alice", 20, 3.5);
    student1.displayInfo();

    student1.setName("Bob");
    student1.setAge(21);
    student1.setGPA(3.8);

    student1.displayInfo();
}