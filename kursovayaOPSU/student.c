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
            "(1) Добавить информацию о студенте.\n"
            "(2) Удалить информацию о студенте.\n"
            "(3) Корректировать информацию о студенте.\n"
            "(4) Поиск по базе данных информации студента по ФИО.\n"
            "(5) Сортировка базы данных по фамилиям студента (в алфавитном порядке).\n"
            "(6) Вывод в консоль всей информации базы данных.\n"
            "(7) Вывод в консоль найденную информацию из базы данных.\n"
            "(8) Запись всей информации в файл из базы данных.\n"
            "(9) Запись найденной инфомации в файл из базы данных.\n"
            "(10) Добавить название для новой базы данных.\n"
            "(0) Завершить процесс.\n"
            "Ваш выбор: "
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

//Функция добавления нового студента
void addStudent(Student** studentList) {
    system("cls");
    if (COUNT_STUDENTS >= 20) {
        printf("Количество студентов больше 20.\n");
        return;
    }

    char name[50]; // Имя
    char surname[50]; // Фамилия
    char middleName[50]; // Отчество
    char birthday[50]; // День рождения
    char choice;



   // чтобы не было Error C6308
    if (studentList == NULL) {
        exit(0);
    }
    *studentList = (Student**)realloc(*studentList, (COUNT_STUDENTS + 1) * sizeof(Student));
    

    Student* newStudent = (Student*)malloc(sizeof(Student));

    newStudent->countExams = 0;
    newStudent->countTests = 0;
    newStudent->headExam = NULL;
    newStudent->headTest = NULL;

    printf("Введите имя студента: ");
    scanf("%s", &name);
    strcpy(newStudent->name, name);

    printf("Введите фамилию студента: ");
    scanf("%s", &surname);
    strcpy(newStudent->surname, surname);

    printf("Введите отчество студента: ");
    scanf("%s", &middleName);
    strcpy(newStudent->middleName, middleName);

    printf("Введите дату рождения студента: ");
    scanf("%s", &birthday);
    strcpy(newStudent->birthday, birthday);

    *studentList[COUNT_STUDENTS] = *newStudent;
    COUNT_STUDENTS++;

    fseek(stdin, 0, SEEK_END);
    printf(
        "(1) Добавить экзаен\n"
        "(2) Добавить зачет\n"
        "(3) Назад\n"
        "Ваш выбор: "
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
        printf("Кол-во экзаменов больше 5.\n");
        return;
    }

    Exam* newExam = (Exam*)malloc(sizeof(Exam));
    Student* pathStudent = student;

    char name[50];
    char examDate[50];
    pathStudent->countExams++;

    printf("Название экзамена: ");
    scanf("%s", &name); printf("\n");
    strcpy(newExam->name, name);

    printf("Дата экзамена: ");
    scanf("%s", &examDate); printf("\n");
    strcpy(newExam->examDate, examDate);


    newExam->prev = headExam;
    headExam = newExam;


    if (student->countExams < 5) {
        char choice;
        fseek(stdin, 0, SEEK_END);
        printf(
            "(1) Добавить экзамен\n"
            "(2) Добавить зачет\n"
            "(3) Назад\n"
            "Ваш выбор: "

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
        printf("Зачетов больше 10.\n");
        return;
    }

    Test* newTest = (Test*)malloc(sizeof(Test));
    Student* pathStudent = student;

    char name[50];
    char testDate[50];
    pathStudent->countTests++;

    printf("Введите название зачета: ");
    scanf("%s", &name); printf("\n");
    strcpy(newTest->name, name);

    printf("Введите дату зачета: ");
    scanf("%s", &testDate); printf("\n");
    strcpy(newTest->testDate, testDate);


    newTest->prev = pathStudent->headTest;
    pathStudent->headTest = newTest;

    if (student->countTests < 10) {
        char choice;
        fseek(stdin, 0, SEEK_END);
        printf(
            "(1) Добавить экзамен\n"
            "(2) Добавить зачет\n"
            "(3) Назад\n"
            "Ваш выбор: "
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

        printf("Имя: %s\n", student->name);
        printf("Фамилия: %s\n", student->surname);
        printf("Отчество: %s\n", student->middleName);
        printf("Дата рождения %s\n", student->birthday);
        printf("\n");

        exam = student->headExam;
        test = student->headTest;

        printf("Сведения об экзаменах: \n");
        while (exam != NULL) {
            printf("Название предмета: ");
            printf("Дата экзамена: ");
            exam = exam->prev;
        }

        printf("Сведения о зачетах: \n");
        while (test != NULL) {
            printf("Название предмета: ");
            printf("Дата зачета: ");
            test = test->prev;
        }

    }
    system("pause");
}
