#include "program.h"

#include <iostream>
#include <fstream>
#include <algorithm>

Program::Program(const std::string& name) : program_name(name) {}

void Program::add_student(Student& student) {
    students.push_back(&student);
}

void Program::add_course(Course& course) {
    courses.push_back(&course);
}

void Program::honours_list() const {
    std::vector<Student*> honoured;

    std::copy_if(students.begin(), students.end(), std::back_inserter(honoured),
        [](const Student* s) {
            return s->gpa > 3.5;
        });

    std::sort(honoured.begin(), honoured.end(),
        [](const Student* a, const Student* b) {
            return a->gpa > b->gpa;
        });

    std::cout << "=== Honours List for " << program_name << " ===" << std::endl;

    std::for_each(honoured.begin(), honoured.end(), [](const Student* s) {
        std::cout << "  " << s->name() << " - GPA: " << s->gpa << std::endl;
        });
}

void Program::save_to_file(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    file << "Program: " << program_name << std::endl;

    file << "Courses: " << courses.size() << std::endl;
    for (const Course* c : courses) {
        file << c->name() << "," << c->code() << std::endl;
    }

    file << "Students: " << students.size() << std::endl;
    for (const Student* s : students) {
        file << s->full_name << "," << s->dob << "," << s->sex << "," << s->gpa << std::endl;
    }

    file.close();
}

void Program::load_from_file(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error: Could not open file " << filename << " for reading." << std::endl;
        return;
    }

    std::string line;

    std::getline(file, line);
    program_name = line.substr(line.find(": ") + 2);

    std::getline(file, line);
    int num_courses = std::stoi(line.substr(line.find(": ") + 2));

    for (int i = 0; i < num_courses; i++) {
        std::getline(file, line);
        std::string c_name = line.substr(0, line.find(','));
        std::string c_code = line.substr(line.find(',') + 1);

        Course* c = new Course(c_name, c_code);
        courses.push_back(c);
    }

    std::getline(file, line);
    int num_students = std::stoi(line.substr(line.find(": ") + 2));

    for (int i = 0; i < num_students; i++) {
        std::getline(file, line);

        size_t p1 = line.find(',');
        size_t p2 = line.find(',', p1 + 1);
        size_t p3 = line.find(',', p2 + 1);

        std::string s_name = line.substr(0, p1);
        std::string s_dob = line.substr(p1 + 1, p2 - p1 - 1);
        gender s_gender = static_cast<gender>(std::stoi(line.substr(p2 + 1, p3 - p2 - 1)));
        double s_gpa = std::stod(line.substr(p3 + 1));

        Student* s = new Student(s_name, s_dob, s_gender, s_gpa);
        students.push_back(s);
    }

    file.close();
}

Program::~Program() {
    std::cout << "Program object has been destroyed." << std::endl;
}