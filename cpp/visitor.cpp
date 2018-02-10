#include <iostream>
#include <list>
#include <string>

using namespace std;

/* Visitor Pattern 
 * The code is referenced from 
 * https://en.wikipedia.org/wiki/Visitor_pattern */

class SchoolMember;
class Teacher;
class Student;

class Visitor {
    public:
        /* Input parameter should be concrete element,
         * otherwise we can only access element's attributes */
        virtual void VisitStudent(Student *m) = 0;
        virtual void VisitTeacher(Teacher *m) = 0;
};

class SchoolMember {
    public:
       virtual void Accept(Visitor *v) = 0; 
};

class Student: public SchoolMember {
    public:
        void Accept(Visitor *v) override {
            /* Each element type has its visitor method,
             * namely, visitor should implement methods for
             * every visitor */
            v->VisitStudent(this);
        }
        Student(string &s, int ag): name{s}, age{ag} {} 
        string name;
        int age;
};

class Teacher: public SchoolMember {
    public:
        void Accept(Visitor *v) override {
            v->VisitTeacher(this);
        }

        Teacher(string &s, int ag): name{s}, age{ag} {} 
        string name;
        int age;
};

class NameVisitor: public Visitor {
    public:
        /* In this way, we seperate data (elements) from 
         * its algorithm (visitors) */
        void VisitStudent(Student *m) override {
            cout << "Student: " << m->name << endl;
        }
        void VisitTeacher(Teacher *m) override {
            cout << "Teacher: " << m->name << endl;
        }
};

class AgeVisitor: public Visitor {
    public:
        void VisitStudent(Student *m) override {
            cout << "Student: " << m->age << endl;
        }
        void VisitTeacher(Teacher *m) override {
            cout << "Teacher: " << m->age << endl;
        }
};

void VisitorPatternTestCode() {
    string s[5]{"John", "Mary", "Tom", "Ben", "Frank"};
    Student st1{s[0], 15};
    Student st2{s[1], 17};
    Student st3{s[2], 16};
    Teacher t1{s[3], 45};
    Teacher t2{s[4], 37};

    list<SchoolMember*> l{&st1, &st2, &st3, &t1, &t2};
    
    NameVisitor nv;
    for (auto &i : l)
        i->Accept(&nv);
    
    AgeVisitor av;
    for (auto &i : l)
        i->Accept(&av);
}

int main() {
    VisitorPatternTestCode();
}
