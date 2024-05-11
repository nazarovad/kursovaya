#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* name;
    int grades;

    struct Exam* prev;
} Exam;

typedef struct {
    Exam exam;
    char* name;
    int age;
    int countExams;
    struct Exam* headExam;
    struct Student* prev;

} Student;


void addStudent(Student **head, char* name) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    newStudent->countExams = 0;
    newStudent->name = name;
    newStudent->prev = *head;
    *head = newStudent;
    newStudent->headExam = NULL;

}

void  addExam(Student** head, Student** headExam, char* name, int grades) {
    Exam* newExam = (Exam*)malloc(sizeof(Exam));
    Student* pathStudent = *head;
    
    pathStudent->countExams++;
    newExam->name = name;
    newExam->grades = grades;
    
    newExam->prev = *headExam;
    *headExam = newExam;

}

void printStudent(Student* head) {
    Student* pthHead = head;
    if (pthHead == NULL)
    {
        printf("Студентов нет");
    }
    else
    {
        while (pthHead != NULL)
        {
            printf("%s %d",pthHead->name, pthHead->countExams);
            pthHead = pthHead->prev;
            printf("\n");
        }
    }
}

int main() {
    system("chcp 1251 >> null");
    Student* head = NULL;

    addStudent(&head, "Andrey");
    addExam(&head, &head->headExam, "информатика", 5);
    addExam(&head, &head->headExam, "устный р", 5);
    addStudent(&head, "Саша");
    addExam(&head, &head->headExam, "литература", 5);
    addExam(&head, &head->headExam, "матика", 5);

    printStudent(head);

    system("chcp 1251 >> null");

	return 0;
}