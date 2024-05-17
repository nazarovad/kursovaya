#ifndef KURsovayaOPSU_H
#define KURsovayaOPSU_H

typedef struct {
    char* name;
    char* examDate;
    struct Exam* prev;
} Exam;

typedef struct Student {
    Exam exam;
    char* name; // ���
    char* surname; // �������
    char* middleName; // ��������
    int countExams; // ���-�� ��������� 
    char* birthday; // ���� ��������
    struct Exam* headExam;
    struct Student* prev;
    struct Student* next;
} Student;

void addStudent(Student** head, char* name);
void addExam(Student* head, Student** headExam, char* name, char* examDate);

// ����� �� ���
Student* findStudent(Student* head, char* find);
Student* removeStudent(Student* head, char* find);
void saveToFile(Student* head, const char* filename);
Student* sortStudent(Student* head);
void printStudentInfo(Student* head, char* option, ...);
void toChangeDataStudent(Student* head);

#endif
