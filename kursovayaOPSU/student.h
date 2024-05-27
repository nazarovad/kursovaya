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
    char name[50]; // ���
    char surname[50]; // �������
    char middleName[50]; // ��������
    int countExams; // ���-�� ��������� 
    int countTests; // ���-�� �������
    char birthday[50]; // ���� ��������
    struct Exam* headExam;
    struct Test* headTest;
} Student;


void mainMenu(Student** studentList);
void addStudent(Student** studentList);
void printStudents(Student** studentList);
void addExam(Student* student, Student* headExam);
void addTest(Student* student);
#endif


