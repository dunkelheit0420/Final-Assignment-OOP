#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <iostream>
#include <vector>

const int COURSE_SIZE = 6;

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
    virtual ~Person() = 0;
    virtual void display() const;
    virtual std::string name() const = 0;
};

class Course; //declared below

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
    void display() const;
    std::string code() const;
    void add_student(const Student&);
    void display_students() const;
};

class Program {
private:
    std::string program_name;
    std::vector<Student*> students;
    std::vector<Course*> courses;
public:
    Program(const std::string& name);
    void add_student(Student& student);
    void add_course(Course& course);
    void honours_list() const; // names of all students
    void save_to_file(const std::string& filename) const; // courses + students
    void load_from_file(const std::string& filename);
    ~Program();
};

#endif