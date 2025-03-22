#ifndef CLASS_H
#define CLASS_H

class Student {
private:
    char name[50]; // Private field: fixed-size character array
    int age;
    double gpa;

    void updateGPA(double adjustment);

public:
    Student();
    Student(const char* name, int age, double gpa);

    const char (&getName() const)[50]; // Return a reference to the char[50] array
    int getAge() const;
    double getGPA() const;

    void setName(const char* newName);
    void setAge(int newAge);
    void setGPA(double newGPA);

    void displayInfo() const;
};

#endif