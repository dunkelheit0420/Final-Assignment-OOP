#include "library.h"
#include <algorithm>
#include <fstream>
#include <string>

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
Course::Course() : course_name_("Unknown"), course_code_("000") {}

Course::Course(const std::string& name, const std::string& code)
    : course_name_(name), course_code_(code) {
}

void Course::display() const {
    std::cout << "Course Name: " << course_name_ << std::endl;
    std::cout << "Course Code: " << course_code_ << std::endl;
    std::cout << "Enrolled Students: " << students.size() << std::endl;
}

std::string Course::code() const {
    return course_code_;
}

void Course::add_student(const Student& student) {
    if (student.courses_.size() >= COURSE_SIZE) {
        throw std::string("Error: Course " + course_code_ + " is full. Cannot enroll " + student.name() + ".");
    }
    student.push_back(&student);
}

void Course::display_students() const {
    std::cout << "Students enrolled in " << course_code_ << " - " << course_name_ << ":" << std::endl;
    std::for_each(student.begin(), student.end(), [](const Student* s) {
        std::cout << "  - " << s->name() << std::endl;
        });
}

Course::~Course() {
    std::cout << "Course object has been destroyed." << std::endl;
}

//Program class functions implementation
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
        file << s->full_name_ << "," << s->dob << "," << s->sex << "," << s->gpa << std::endl;
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