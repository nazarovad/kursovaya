#ifndef KURsovayaOPSU_H
#define KURsovayaOPSU_H


typedef struct Exam{
    char name[50];
    char examDate[50];
    struct Exam* prev;
} Exam;

typedef struct Student {
    Exam exam;
    char name[50]; // ���
    char surname[50]; // �������
    char middleName[50]; // ��������
    int countExams; // ���-�� ��������� 
    char birthday[50]; // ���� ��������
    struct Exam* headExam;
    struct Student* prev;
    struct Student* next;
} Student;

void addStudent(Student** head, char* name);
void addExam(Student* head, Student* headExam, char* name, char* examDate);
void deleteExam(Student* head, char* nameExam);

// ����� �� ���
Student* findStudent(Student* head, char* find);
Student* removeStudent(Student* head, char* find);
void saveToFile(Student* head, const char* filename);
Student* sortStudent(Student* head);
void printStudentInfo(Student* head, char* option, ...);



#endif
