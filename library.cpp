#include "library.h"

//Person class functions implementation
Person::Person() : full_name_(""), birthday_(""), gender_(other) {}

Person::Person(const std::string& full_name, const std:: string& birthday, gender gender) :
    full_name_(full_name), birthday_(birthday), gender_(gender) {}

Person::~Person() {}

void Person::display() const {
    std::cout << full_name_ << ", " << birthday_ << ", " << gender_;
}

std::string Person::name() const {
    return full_name_;
}


//Student class functions implementation

Student::Student(){

}

Student::Student(const std::string&, const std::string&, gender, double){

}

Student::Student(const Student&){

}

Student::~Student(){

}

void Student::display() const{

}

std::string Student::name() const{

}

void Student::add_course(const Course&){

}


//Course class functions implementation


//Program class functions implementation