#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "student.h";


int COUNT_STUDENTS = 0;


void mainMenu(Student** studentList) {
    char choice = NULL;
    char name[50];
    Student* findedStudent = false;
    while (choice != '0')
    {
        printf(
            "(1) �������� ���������� � ��������.\n"
            "(2) ������� ���������� � ��������.\n"
            "(3) �������������� ���������� � ��������.\n"
            "(4) ����� �� ���� ������ ���������� �������� �� ���.\n"
            "(5) ���������� ���� ������ �� �������� �������� (� ���������� �������).\n"
            "(6) ����� � ������� ���� ���������� ���� ������.\n"
            "(7) ����� � ������� ��������� ���������� �� ���� ������.\n"
            "(8) ������ ���� ���������� � ���� �� ���� ������.\n"
            "(9) ������ ��������� ��������� � ���� �� ���� ������.\n"
            "(10) �������� �������� ��� ����� ���� ������.\n"
            "(0) ��������� �������.\n"
            "��� �����: "
        );

        fseek(stdin, 0, SEEK_END);
        scanf("%c", &choice);
        switch (choice)
        {
        case '1':
            addStudent(*&studentList);
            break;
        case '6':
            printStudents(*&studentList);
            break;
        default:
            break;
        }
    }
 }

//������� ���������� ������ ��������
void addStudent(Student** studentList) {
    system("cls");
    if (COUNT_STUDENTS >= 20) {
        printf("���������� ��������� ������ 20.\n");
        return;
    }

    char name[50]; // ���
    char surname[50]; // �������
    char middleName[50]; // ��������
    char birthday[50]; // ���� ��������
    char choice;



   // ����� �� ���� Error C6308
    if (studentList == NULL) {
        exit(0);
    }
    *studentList = (Student**)realloc(*studentList, (COUNT_STUDENTS + 1) * sizeof(Student));
    

    Student* newStudent = (Student*)malloc(sizeof(Student));

    newStudent->countExams = 0;
    newStudent->countTests = 0;
    newStudent->headExam = NULL;
    newStudent->headTest = NULL;

    printf("������� ��� ��������: ");
    scanf("%s", &name);
    strcpy(newStudent->name, name);

    printf("������� ������� ��������: ");
    scanf("%s", &surname);
    strcpy(newStudent->surname, surname);

    printf("������� �������� ��������: ");
    scanf("%s", &middleName);
    strcpy(newStudent->middleName, middleName);

    printf("������� ���� �������� ��������: ");
    scanf("%s", &birthday);
    strcpy(newStudent->birthday, birthday);

    *studentList[COUNT_STUDENTS] = *newStudent;
    COUNT_STUDENTS++;

    fseek(stdin, 0, SEEK_END);
    printf(
        "(1) �������� ������\n"
        "(2) �������� �����\n"
        "(3) �����\n"
        "��� �����: "
    );


    scanf("%c", &choice);
    
    switch (choice)
    {
    case '1':
        *studentList = (Student**)realloc(*studentList, studentList + sizeof(Exam));
        addExam(newStudent, newStudent->headExam);
        break;
    case '2':
        *studentList = (Student**)realloc(*studentList, studentList + sizeof(Test));
        addTest(newStudent);
        break;
    default:
        system("cls");
        break;
    }
}

void addExam(Student* student, Student* headExam) {
    system("cls");
    if (student->countExams == 5) {
        printf("���-�� ��������� ������ 5.\n");
        return;
    }

    Exam* newExam = (Exam*)malloc(sizeof(Exam));
    Student* pathStudent = student;

    char name[50];
    char examDate[50];
    pathStudent->countExams++;

    printf("�������� ��������: ");
    scanf("%s", &name); printf("\n");
    strcpy(newExam->name, name);

    printf("���� ��������: ");
    scanf("%s", &examDate); printf("\n");
    strcpy(newExam->examDate, examDate);


    newExam->prev = headExam;
    headExam = newExam;


    if (student->countExams < 5) {
        char choice;
        fseek(stdin, 0, SEEK_END);
        printf(
            "(1) �������� �������\n"
            "(2) �������� �����\n"
            "(3) �����\n"
            "��� �����: "

        );
        scanf("%c", &choice);
        switch (choice)
        {
        case '1':
            addExam(student, student->headExam);
            break;
        case '2':
            addTest(student);
            break;
        default:
            system("cls");
            break;
        }
    }
}   

void addTest(Student* student) {
    system("cls");
    if (student->countTests == 10) {
        printf("������� ������ 10.\n");
        return;
    }

    Test* newTest = (Test*)malloc(sizeof(Test));
    Student* pathStudent = student;

    char name[50];
    char testDate[50];
    pathStudent->countTests++;

    printf("������� �������� ������: ");
    scanf("%s", &name); printf("\n");
    strcpy(newTest->name, name);

    printf("������� ���� ������: ");
    scanf("%s", &testDate); printf("\n");
    strcpy(newTest->testDate, testDate);


    newTest->prev = pathStudent->headTest;
    pathStudent->headTest = newTest;

    if (student->countTests < 10) {
        char choice;
        fseek(stdin, 0, SEEK_END);
        printf(
            "(1) �������� �������\n"
            "(2) �������� �����\n"
            "(3) �����\n"
            "��� �����: "
        );
        scanf("%c", &choice);
        switch (choice)
        {
        case '1':
            addTest(student);
            break;
        case '2':
            addExam(student, student->headExam);
            break;
        default:
            system("cls");
            break;
        }
    }

}


void printStudents(Student** studentList) {
    Student* student;
    Test* test;
    Exam* exam;
    for (int i = 0; i < COUNT_STUDENTS; i++)
    {
        student = studentList[i];

        printf("���: %s\n", student->name);
        printf("�������: %s\n", student->surname);
        printf("��������: %s\n", student->middleName);
        printf("���� �������� %s\n", student->birthday);
        printf("\n");

        exam = student->headExam;
        test = student->headTest;

        printf("�������� �� ���������: \n");
        while (exam != NULL) {
            printf("�������� ��������: ");
            printf("���� ��������: ");
            exam = exam->prev;
        }

        printf("�������� � �������: \n");
        while (test != NULL) {
            printf("�������� ��������: ");
            printf("���� ������: ");
            test = test->prev;
        }

    }
    system("pause");
}
