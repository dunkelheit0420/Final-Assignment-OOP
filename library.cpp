#include "library.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

//Person class functions implementation
Person::Person() : full_name_(""), birthday_(""), gender_(other) {}

Person::Person(const std::string& full_name, const std:: string& birthday, gender gender) :
    full_name_(full_name), birthday_(birthday), gender_(gender) {}

Person::~Person() {
    std::cout << full_name_ << " is deleted." << std::endl;
}

void Person::display() const {
    std::cout << full_name_ << ", " << birthday_ << ", " << genderToStr(gender_);
}

std::string Person::name() const {
    return full_name_;
}

//Helper function to output the gender string
std::string genderToStr(gender g){
    if(g == male) return "male";
    if(g == female) return "female";
    return "other";
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

void Student::add_course(Course& course){
    //check if the student is already enrolled in the course:
    for (size_t i = 0; i < courses_.size(); i++) {
        if(&course == courses_[i]) {
            throw std::string("Student already enrolled in the course");
        }
    }

    try {
        course.add_student(*this);
        courses_.push_back(&course);
    }

    catch (const std::string& error) {
        std::cerr << error << std::endl;
    }
}


//Course class functions implementation
Course::Course() : course_name_(""), course_code_("") {}

Course::Course(const std::string& name, const std::string& code)
    : course_name_(name), course_code_(code) {
}

Course::~Course() {
    std::cout << "Course object has been destroyed." << std::endl;
}

void Course::display() const {
    std::cout << course_name_ << ", " << course_code_ << ", " << students_.size() << " students" << std::endl;
}

std::string Course::code() const {
    return course_code_;
}

void Course::add_student(Student& student) {
    //check if the course is enrolling duplicate students:
    for (size_t i = 0; i < students_.size(); i++) {
        if(&student == students_[i]) {
            throw std::string("Student already enrolled in the course");
        }
    }

    if (students_.size() >= COURSE_SIZE) {
        throw std::string("Error: Course " + course_code_ + " is full. Cannot enroll " + student.name() + ".");
    }

    students_.push_back(&student);
}

void Course::display_students() const {
    std::cout << "Students enrolled in " << course_code_ << " - " << course_name_ << ":" << std::endl;
    std::for_each(students_.begin(), students_.end(), [](const Student* s) {
        std::cout << s->name() << std::endl;
    });
}


//Program class functions implementation
Program::Program(const std::string& name) : program_name_(name), owns_memory_(false) {}

void Program::add_student(Student& student) {
    students_.push_back(&student);
}

void Program::add_course(Course& course) {
    courses_.push_back(&course);
}

void Program::honours_list() const {
    std::vector<Student*> honoured;

    std::copy_if(students_.begin(), students_.end(), std::back_inserter(honoured),
        [](const Student* s) {
            return s->gpa_ > 3.5;
        });

    std::sort(honoured.begin(), honoured.end(),
        [](const Student* a, const Student* b) {
            return a->gpa_ > b->gpa_;
        });

    std::cout << "=== Honours List for " << program_name_ << " ===" << std::endl;

    std::for_each(honoured.begin(), honoured.end(), [](const Student* s) {
        s->display(); });
}

void Program::save_to_file(const std::string& filename) const {
    try {
        std::ofstream outfile(filename);

        if (!outfile) {
            throw std::string("Error: Could not open file " + filename + " for writing.");
        }

        outfile << program_name_ << std::endl;
        outfile << courses_.size() << std::endl;

        for (const Course* c : courses_) {
            outfile << c->code() << "," << c->course_name_ << std::endl;
        }

        outfile << students_.size() << std::endl;
        for (const Student* s : students_) {
            outfile << s->full_name_ << "," << s->birthday_ << "," << s->gender_ << "," << s->gpa_ << "," << s->courses_.size();
            for(int i = 0; i < s->courses_.size(); i++) {
                outfile << "," << s->courses_[i]->code();
            }
            outfile << "\n";
        }
        outfile.close();
    }
    catch (const std::string& error) {
        std::cerr << error << std::endl;
    }
}

void Program::load_from_file(const std::string& filename) {
    try {
        std::ifstream infile(filename);

        if (!infile) {
            throw std::string("Error: Could not open file " + filename + " for reading.");
        }

        std::string line;
        std::getline(infile, line);
        program_name_ = line;

        std::getline(infile, line);
        int num_courses = std::stoi(line);

        for (int i = 0; i < num_courses; i++) {
            std::getline(infile, line);
            std::stringstream ss(line);
            std::string c_code, c_name;
            std::getline(ss, c_code, ',');
            std::getline(ss, c_name);

            Course* c = new Course(c_name, c_code);
            add_course(*c);
        }

        std::getline(infile, line);
        int num_students = std::stoi(line);

        for (int i = 0; i < num_students; i++) {
            std::getline(infile, line);
            std::stringstream ss(line);
            std::string fullName, birthday, genderStr, gpaStr, numCoursesStr;

            std::getline(ss, fullName, ',');
            std::getline(ss, birthday, ',');
            std::getline(ss, genderStr, ',');
            std::getline(ss, gpaStr, ',');
            gender genderEnum = static_cast<gender>(std::stoi(genderStr));
            double gpa = std::stod(gpaStr);

            Student* s = new Student(fullName, birthday, genderEnum, gpa);
            add_student(*s);

            std::getline(ss, numCoursesStr, ',');
            std::string courseCode;
            int numCourses = std::stoi(numCoursesStr);
            for(int j = 0; j < numCourses; j++) {
                if (j < numCourses - 1) {
                    std::getline(ss, courseCode, ',');
                } else {
                    std::getline(ss, courseCode, ',');
                }

                for(Course* c : courses_) {
                    if(c->code() == courseCode) {
                        s->add_course(*c);
                    }
                }
            }

        }
        infile.close();
    }
    catch (const std::string& error) {
        std::cerr << error << std::endl;
    }
}

Program::~Program() {
    //Only delete memory if loaded from file
    if(owns_memory_) {
        for (Student* s : students_) delete s;
        for (Course* c : courses_) delete c;
    }
    std::cout << "Program object has been destroyed." << std::endl;
}