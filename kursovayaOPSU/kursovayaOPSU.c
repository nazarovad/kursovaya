#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include "student.h";

int main() {
    system("chcp 1251 >> null");

    int countStudents = 0;
    Student* head = NULL;
    Student* tail = head;
    

    addStudent(&head, "Андрей");
    addExam(&head, &head->headExam, "информатика", "01.01.23");

    addStudent(&head, "Саша");

    addStudent(&head, "Вика");
    addExam(&head, &head->headExam, "литература", "01.01.23");
    addExam(&head, &head->headExam, "матика", "01.01.23");

    addStudent(&head, "Лиза");

    addExam(&head, &head->headExam, "матика", "01.01.23");
    addExam(&head, &head->headExam, "матика", "01.01.23");
    addExam(&head, &head->headExam, "устный р", "01.01.23");
    addExam(&head, &head->headExam, "матика", "01.01.23");
   

    printStudentInfo(head, "fullInfo");

    //head = removeStudent(head, "Лиза");
    printf("\n------------\n");
    //head = sortStudent(head);





    //printStudentInfo(head, "fullInfo");
    printStudentInfo(head, "findInfo", "Андрей");
    printStudentInfo(head, "findInfo", "Андрей");
    printf("\n------------\n");
    toChangeDataStudent(head);


	return 0;
}