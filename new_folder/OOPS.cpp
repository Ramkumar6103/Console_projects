#include <iostream>
#include <string>
using namespace std;

// 🔒 1. Encapsulation + Abstraction
class Person {
private: // encapsulated data
    string name;
    int age;

public:
    // Constructor
    Person(string n, int a) : name(n), age(a) {}

    // Getter
    string getName() const { return name; }
    int getAge() const { return age; }

    // Virtual function for polymorphism
    virtual void displayInfo() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

// 🧬 2. Inheritance
class Student : public Person {
private:
    string studentID;

public:
    Student(string n, int a, string id) : Person(n, a), studentID(id) {}

    void displayInfo() const override { // 🔁 Run-time polymorphism
        cout << "[Student] Name: " << getName()
             << ", Age: " << getAge()
             << ", ID: " << studentID << endl;
    }
};

// 👨‍🏫 Another derived class
class Teacher : public Person {
private:
    string subject;

public:
    Teacher(string n, int a, string s) : Person(n, a), subject(s) {}

    void displayInfo() const override {
        cout << "[Teacher] Name: " << getName()
             << ", Age: " << getAge()
             << ", Subject: " << subject << endl;
    }
};

// 🧠 3. Compile-time Polymorphism (Function Overloading)
class Calculator {
public:
    int add(int a, int b) { return a + b; }
    double add(double a, double b) { return a + b; }
};

int main() {
    // 🎯 1. Object & Class
    Student s1("Alice", 20, "S123");
    Teacher t1("Mr. Smith", 40, "Physics");

    // 🌈 2. Runtime Polymorphism via base class pointer
    Person* people[] = { &s1, &t1 };

    for (Person* p : people) {
        p->displayInfo();  // calls the overridden version
    }

    // 🧮 3. Compile-time Polymorphism
    Calculator calc;
    cout << "Int Add: " << calc.add(5, 3) << endl;
    cout << "Double Add: " << calc.add(2.5, 4.1) << endl;

    return 0;
}
