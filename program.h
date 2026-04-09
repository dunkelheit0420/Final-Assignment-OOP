#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>

#include "course.h"
#include "student.h"

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