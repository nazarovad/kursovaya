#ifndef KURsovayaOPSU_H
#define KURsovayaOPSU_H


typedef struct Exam{
    char name[50];
    char examDate[50];
    struct Exam* prev;
} Exam;

typedef struct Test {
    char name[50];
    char testDate[50];
    struct Exam* prev;
} Test;

typedef struct Student {
    Test test;
    Exam exam;
    char name[50]; // Имя
    char surname[50]; // Фамилия
    char middleName[50]; // Отчество
    int countExams; // Кол-во экзаменов 
    int countTests; // Кол-во зачетов
    char birthday[50]; // День рождения
    struct Exam* headExam;
    struct Test* headTest;
} Student;


void mainMenu(Student** studentList);
void addStudent(Student** studentList);
void printStudents(Student** studentList);
void addExam(Student* student, Student* headExam);
void addTest(Student* student);
#endif


