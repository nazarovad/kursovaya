#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include "student.h";
#include <string.h>



void toChangeDataStudent(Student* head) {
    char* name = "Андрей";
    printf("Введите имя студента");
    //scanf("%s", &name);
    Student* student = findStudent(head, name);
    if (student == false) {
        return;
    }
    system("cls");
    printf("Данные студента: \n");
    printStudentInfo(head, "findInfo", name);

    int choice = 5;
    char* endterString;
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
        student->name = endterString;
        break;
    case 2:
        system("cls");
        printf("Фамилия студента %s\n", student->surname);
        printf("Для изменения введите фамилию: ");
        scanf("%s", &endterString);
        student->surname = endterString;
        break;
    case 3:
        system("cls");
        printf("Отчество студента %s\n", student->middleName);
        printf("Для изменения введите отчество: ");
        scanf("%s", &endterString);
        student->middleName = endterString;
        break;
    case 4:
        system("cls");
        printf("Дата рождения студента %s\n", student->birthday);
        printf("Для изменения введите дату рождения: ");
        scanf("%s", &endterString);
        student->birthday = endterString;
        break;
    case 5:
        system("pause");
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
            //---Не забыть очистить---
            char* nameExam = (char*)malloc(50);
            char* dataExam = (char*)malloc(50);
            
            printf("Введите название предмета: ");
            scanf("%s", nameExam);

            printf("Введите дату сдачи предмета: ");
            scanf("%s", dataExam);
            addExam(student, student->headExam, nameExam, dataExam);
            printf("\nЭкзамен был создан\n");

        }
        else if (choice == 2)
        {
            deleteExam(student, "информатика");
        }
        break;
    default:
        break;
    }
    
}

//void deleteExam(Student* head, char* nameExam) {
//    Exam* exam = head->headExam;
//    if (exam->name == nameExam)
//    {
//        Student* temp = exam;
//        head->headExam = exam->prev;
//        free(temp);
//    }
//    else
//    {
//        while (exam->prev != NULL) {
//            if (exam->prev->name == nameExam)
//            {
//                Student* temp = exam->prev;
//                exam->prev = exam->prev->prev;
//                free(temp);
//
//            }
//        }
//
//    }
// 
//}



int main() {
    system("chcp 1251 >> null");

    int countStudents = 0;
    Student* head = NULL;
    

    addStudent(&head, "Андрей");
    addExam(head, head->headExam, "литература", "01.01.23");
    addExam(head, head->headExam, "информатика", "01.01.23");
    

    addStudent(&head, "Саша");

    addStudent(&head, "Вика");
    addExam(head, head->headExam, "литература", "01.01.23");
    addExam(head, head->headExam, "матика", "01.01.23");

    addStudent(&head, "Лиза");

    addExam(head, head->headExam, "матика", "01.01.23");

   

    printStudentInfo(head, "fullInfo");

    //head = removeStudent(head, "Лиза");
    printf("\n------------\n");
    //head = sortStudent(head);





    //printStudentInfo(head, "fullInfo");
    printStudentInfo(head, "findInfo", "Андрей");
    printStudentInfo(head, "findInfo", "Андрей");
    printf("\n------------\n");
    toChangeDataStudent(head);




    printStudentInfo(head, "fullInfo");

    



	return 0;
}