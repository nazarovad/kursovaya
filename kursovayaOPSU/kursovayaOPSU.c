#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char* name;
    int grades;
    struct Exam* prev;
} Exam;

typedef struct Student {
    Exam exam;
    char* name;
    int age;
    int countExams;
    struct Exam* headExam;
    struct Student* prev;
    struct Student* next;
} Student;


void addStudent(Student **head, char* name) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    newStudent->countExams = 0;
    newStudent->name = name;

    newStudent->prev = *head;
    newStudent->next = NULL;
    if (*head != NULL) {
        (*head)->next = newStudent;
    }


    *head = newStudent;
    newStudent->headExam = NULL;
}

void addExam(Student** head, Student** headExam, char* name, int grades) {
    Exam* newExam = (Exam*)malloc(sizeof(Exam));
    Student* pathStudent = *head;
    
    pathStudent->countExams++;
    newExam->name = name;
    newExam->grades = grades;
    
    newExam->prev = *headExam;
    *headExam = newExam;
}

// Поиск по ФИО
Student* findStudent(Student* head, char* find) {
    Student* pthHead = head;
    if (pthHead == NULL)
    {
        printf("Студентов нет");
    }
    else
    {
        while (pthHead != NULL)
        {
            if (pthHead->name == find)  
            {
                printf("Студент найден!\n");
                return pthHead;
            }
            pthHead = pthHead->prev;
        }
    }
    printf("Студент не найден\n");
    return false;
}

void removeStudent(Student **head, char* find) {

    Student* tempHead = *head;
    Student* StundentDelete = findStudent(tempHead, find);
    
    if (*head == StundentDelete)
    {
       (*head)->prev;
    }
    else
    {
        while ((*head)->prev != NULL)
        {
            if (StundentDelete == *head)
            {
                Student* temp = *head;
                //(*head)->prev->next = (*head)->next;
                //(*head)->next->prev = (*head)->prev;
            }
        }
        while ((*head)->next != NULL)
        {
            (*head) = (*head)->next;
        }
    }
   
}

void printStudent(Student* head) {
    Student* pthHead = head;
    Student* pthExamHead = head->headExam;

    if (pthHead == NULL)
    {
        printf("Студентов нет\n");
    }
    else
    {
        while (pthHead != NULL)
        {
            printf("%s %d | ",pthHead->name, pthHead->countExams);
            while (pthExamHead != NULL)
            {
                printf("%s %d", pthExamHead->exam.name, pthExamHead->exam.grades);
                printf("\n");
                pthExamHead = pthExamHead->exam.prev;
            }
            pthHead = pthHead->prev;
            if (pthHead != NULL)
            {
                pthExamHead = pthHead->headExam;
            }
            printf("\n");
        }
    }
}

int main() {
    system("chcp 1251 >> null");
    int countStudents = 0;
    Student* head = NULL;
    

    addStudent(&head, "Andrey");
    addExam(&head, &head->headExam, "информатика", 5);
    addExam(&head, &head->headExam, "устный р", 5);
    addStudent(&head, "Саша");
    addExam(&head, &head->headExam, "литература", 5);
    addExam(&head, &head->headExam, "матика", 5);

    printStudent(head);

    findStudent(head, "Саша");
    findStudent(head, "May");

    printStudent(head);
    printStudent(head);
    removeStudent(head, "Andrey");
    printStudent(head);
    system("chcp 1251 >> null");

	return 0;
}