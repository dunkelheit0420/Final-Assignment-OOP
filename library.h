#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <iostream>
#include <vector>

enum gender {
    male, 
    female, 
    other
};

class Person {
protected:
    std::string full_name_;
    std::string birthday_;
    gender gender_;
public:
    Person();
    Person(const std::string&, const std:: string&, gender);
    virtual ~Person();
    virtual void display() const;
    virtual std::string name() const;
};

class Course;

class Student : public Person {
private:
    std::vector<Course*> courses_;
    double gpa_;
public:
    Student();
    Student(const std::string&, const std::string&, gender, double);
    Student(const Student&);
    ~Student();
    void display() const override;
    std::string name() const override;
    void add_course(const Course&);
};

class Course {
private:
    std::string course_name_;
    std::string course_code_;
    std::vector<Student*> students_;
public:
    Course();
    Course(const std::string&, const std::string&);
    ~Course();
    void display();
    std::string code();
    void add_student(const Student&);
    
};

#endif