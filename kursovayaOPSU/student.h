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
    struct Student* prev;
    struct Student* next;
} Student;

void addStudent(Student** head);
void addExam(Student* head);
void addTest(Student* head);
void deleteExam(Student* head);

// Поиск по ФИО
Student* findStudent(Student* head, char* find);
void removeStudent(Student** head, char* find);
void saveToFile(Student* head, const char* filename);
Student* sortStudent(Student* head);
void printStudentInfo(Student* head, char* option, ...);
void mainMenu();
void toChangeDataStudent(Student* head);


void saveStudentsToFile(Student* head);
void loadStudentsFromFile(Student** head);
int COUNT_STUDENTS;




#endif


