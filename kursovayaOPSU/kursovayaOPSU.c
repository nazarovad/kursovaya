#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include "student.h";
#include <string.h>


void toChangeDataStudent(Student* head) {

    char name[50] = "Андрей";
    printf("Для корректировки введите имя студента");
    //scanf("%s", &name);
    Student* student = findStudent(head, name);
    if (student == false) {
        return;
    }
    system("cls");
    printf("Данные студента: \n");
    printStudentInfo(head, "findInfo", name);

    int choice = 5;
    char endterString[50];
    int enterInteher;
    printf("Выбери действие: \n");
    printf("(0) Выход для програмы\n");
    printf("(1) Изменить имя студента \n");
    printf("(2) Изменить фамилию студента \n");
    printf("(3) Изменить отчество студента \n");
    printf("(4) Изменить дату рождения студента \n");
    printf("(5) Изменить экзаменационные сведения\n");
    printf("Ваш выбор: ");
    //scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        system("cls");
        printf("Имя студента %s\n", student->name);
        printf("Для изменения введите имя: ");
        scanf("%s", &endterString);
        strcpy(student->name, endterString);
        break;
    case 2:
        system("cls");
        printf("Фамилия студента %s\n", student->surname);
        printf("Для изменения введите фамилию: ");
        scanf("%s", &endterString);
        strcpy(student->surname, endterString);
        break;
    case 3:
        system("cls");
        printf("Отчество студента %s\n", student->middleName);
        printf("Для изменения введите отчество: ");
        scanf("%s", &endterString);
        strcpy(student->middleName, endterString);
        break;
    case 4:
        system("cls");
        printf("Дата рождения студента %s\n", student->birthday);
        printf("Для изменения введите дату рождения: ");
        scanf("%s", &endterString);
        strcpy(student->birthday, endterString);
        break;
    case 5:
        //system("pause");
        system("cls");
        printf("Экзаменационные сведения: \n");

        printStudentInfo(head, "findExamInfo", name);

        printf("Выбери действие:\n");
        printf("(1) Добавить экзамен\n");
        printf("(2) Удалить экзамен\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            addExam(student, student->headExam);
            printf("\nЭкзамен был создан\n");


        }
        else if (choice == 2)
        {
            deleteExam(student);
            printf("\nЭкзамен был удален\n");
        }
        break;
    default:
        break;
    }
    
}





int main() {
    system("chcp 1251 >> null");

    
    
    

    //addStudent(&head);
    mainMenu();

    //addStudent(&head, "Андрей");
    //addExam(head, head->headExam, "литература", "01.01.23");
    //addExam(head, head->headExam, "информатика", "01.01.23");
    //

    //addStudent(&head, "Саша");

    //addStudent(&head, "Вика");
    //addExam(head, head->headExam, "литература", "01.01.23");
    //addExam(head, head->headExam, "матика", "01.01.23");

    //addStudent(&head, "Лиза");

    //addExam(head, head->headExam, "матика", "01.01.23");

   

    //printStudentInfo(head, "fullInfo");

    ////head = removeStudent(head, "Лиза");
    //printf("\n------------\n");
    ////head = sortStudent(head);





    ////printStudentInfo(head, "fullInfo");
    //printStudentInfo(head, "findInfo", "Андрей");
    //printStudentInfo(head, "findInfo", "Андрей");
    //printf("\n------------\n");
    //toChangeDataStudent(head);




    //printStudentInfo(head, "fullInfo");



    //addStudent(&head);

    //char name[50];
    //scanf("%s", &name);
    //findStudent(head, name);



	return 0;
}