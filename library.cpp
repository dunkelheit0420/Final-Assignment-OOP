#include "library.h"

//Person class functions implementation
Person::Person() : full_name_(""), birthday_(""), gender_(other) {}

Person::Person(const std::string& full_name, const std:: string& birthday, gender gender) :
    full_name_(full_name), birthday_(birthday), gender_(gender) {}

Person::~Person() {
    std::cout << full_name_ << " is deleted." << std::endl;
}

void Person::display() const {
    std::cout << full_name_ << ", " << birthday_ << ", " << gender_;
}

std::string Person::name() const {
    return full_name_;
}


//Student class functions implementation

Student::Student() : Person(), gpa_(0.0) {}

Student::Student(const std::string& full_name, const std::string& birthday, gender gender, double gpa) : 
    Person(full_name, birthday, gender), gpa_(gpa) {}

Student::Student(const Student& other): Person(other), gpa_(other.gpa_){}

Student::~Student() {
    std::cout << "Student ";
}

void Student::display() const {
    Person::display();
    std::cout << " " << gpa_ << std::endl;
}

std::string Student::name() const{
    return Person::name();
}

void Student::add_course(const Course&){
    
}


//Course class functions implementation


//Program class functions implementation