#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "student.h";


int COUNT_STUDENTS = 0;
Student* head = NULL;

void addStudent(Student** head) {
    system("cls");
    if (COUNT_STUDENTS >= 20) {
        printf("Максимальное кол-во студентов 20.\n");
        return;
    }
    char name[50]; // Имя
    char surname[50]; // Фамилия
    char middleName[50]; // Отчество
    char birthday[50]; // День рождения
    char choice;
    

    Student* newStudent = (Student*)malloc(sizeof(Student));
    COUNT_STUDENTS++;

    newStudent->countExams = 0;

    //---Заполнение анкеты стендента
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

    newStudent->headExam = NULL;
    newStudent->next = NULL;

    newStudent->prev = *head;
    if (*head != NULL) {
        (*head)->next = newStudent;
    }

    *head = newStudent;



    fseek(stdin, 0, SEEK_END);
    printf("Добавить экзамены для студента?(y/n)(default no): ");
    scanf("%c", &choice);
    switch (choice)
    {
    case 'y':
        addExam(newStudent, newStudent->headExam);
        break;
    default:
        system("cls");
        break;
    }
}

//---headExam нам не нужен-----
void addExam(Student* head) {
    system("cls");
    printStudentInfo(head, "findInfo", head->name);
    if (head->countExams == 5) {
        printf("Максимальное кол-во экзаменов 5.\n");
        return;
    }

    Exam* newExam = (Exam*)malloc(sizeof(Exam));
    Student* pathStudent = head;

    char name[50];
    char examDate[50];
    pathStudent->countExams++;
    //printf("%s", name);

    printf("Добавьте название экзамена: ");
    scanf("%s", &name); printf("\n");
    strcpy(newExam->name, name);
    
    printf("Добавьте дату экзамена: ");
    scanf("%s", &examDate); printf("\n");
    strcpy(newExam->examDate, examDate);


    newExam->prev = pathStudent->headExam;
    pathStudent->headExam = newExam;


    if (head->countExams < 5) {
        char choice;
        fseek(stdin, 0, SEEK_END);
        printf("Добавить еще экзамен?(y/n): ");
        scanf("%c", &choice);
        switch (choice)
        {
        case 'y':
            addExam(head);
            break;
        default:
            system("cls");
            break;
        }
    }

}



//---В качестве аргумента мы передаем данные студента, экзамены которого мы хотим удалить---
void deleteExam(Student* head) {
    if (head->headExam == NULL) {
        printf("Ни одного экзамена не найдено.\n");
        return;
    }

    char nameExam[50];
    printf("Введить название экзамена для удаления: ");
    scanf("%s", &nameExam);

    Exam* exam = head->headExam;
    if (!strcmp(exam->name, nameExam))
    {
        Student* temp = exam;
        head->headExam = exam->prev;
        head->countExams--;
        free(temp);
        printf("Экзамен был удален.\n");
        return;
    }
    else
    {
        while (exam->prev != NULL) {
            if (!strcmp(exam->prev->name, nameExam)) 
            {
                Student* temp = exam->prev;
                exam->prev = exam->prev->prev;
                head->countExams--;
                free(temp);
                printf("Экзамен был удален.\n");
                return;

            }
        }
        printf("Экзамен не был найден.\n");
        return;

    }

}

// Поиск по ФИО
Student* findStudent(Student* head, char* find) {
    Student* pthHead = head;
    if (pthHead == NULL)
    {
        printf("Студентов нет");
        return false;
    }
    else
    {
        while (pthHead != NULL)
        {
            if (!strcmp(pthHead->name, find))
            {
                printf("Информация о студенте:\n");
                return pthHead;
            }
            pthHead = pthHead->prev;
        }
    }
    printf("Студент не найден\n");
    return false;
}

Student* removeStudent(Student* head, char* find) {
    Student* tempHead = head;
    if (!strcmp(head->name, find)) { // 
        Student* temp = head;
        head = head->prev;
        head->next = NULL;
        free(temp);
        COUNT_STUDENTS--;
        printf("Студент был удален.\n");
        return head;
    }
    while (head != NULL) {
        if (!strcmp(head->name, find)) {
            Student* temp = head;
            if (head->prev != NULL) {
                head->prev->next = head->next;
            }
            else {
                head->next->prev = NULL;
            }
            if (head->next != NULL) {
                head->next->prev = head->prev;
            }
            else {
                head->prev->next = NULL;
            }


            head->prev = head;
            free(temp);
            COUNT_STUDENTS--;
            printf("Студент был удален.\n");
            return tempHead;
        }
        head = head->prev;
    }

    printf("Студент не был найден");
    return tempHead;

}

//----Запись всей базы даных в файл-----
void saveToFile(Student* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Ошибка открытия файла %s\n", filename);
        return;
    }

    Student* current = head;
    while (current != NULL) {
        fprintf(file, "Имя: %s\n", current->name);
        //fprintf(file, "Возраст: %d\n", current->age);
        fprintf(file, "Количество экзаменов: %d\n", current->countExams);

        Exam* exam = current->headExam;
        while (exam != NULL) {
            fprintf(file, "    Название экзамена: %s\n", exam->name);
            fprintf(file, "    Дата сдачи: %s\n", exam->examDate);
            exam = exam->prev;
        }

        fprintf(file, "\n");
        current = current->prev;
    }

    fclose(file);
}


//----boubleSort----
Student* sortStudent(Student* head) {
    if (head->prev == NULL && head->next == NULL) {
        return head;
    }
    Student* tempi = head;
    Student* tempj = head;

    while (tempi->prev != NULL) {
        while (tempj->prev != NULL) {
            if (strcmp(tempj->name, tempj->prev->name) > 0) // Уловия выполнения сортировки
            {
                if (tempj->prev->prev != NULL) // Если у нас не последняя пара (главное не забыть для else также сделать)
                {
                    if (tempj->next == NULL) // Если у нас самая первая пара
                    {
                        tempj->prev = tempj->prev->prev;
                        tempj->next = tempj->prev->next;
                        tempj->prev->next = tempj;
                        tempj->next->prev = tempj;
                        tempj->next->next = NULL;

                        tempj = tempj->next;
                        if (tempi->next != NULL) {
                            tempi = tempi->next;
                        }

                        head = head->next;

                    }
                    else // Если у нас не первая пара
                    {
                        tempj->next->prev = tempj->prev;
                        tempj->prev = tempj->prev->prev;
                        tempj->next->prev->prev = tempj;
                        tempj->next->prev->next = tempj->next;
                        tempj->next = tempj->prev;
                        tempj->next = tempj->next->next;
                        tempj->prev->next = tempj;

                        if (tempj == tempi) {
                            tempi = tempi->next;
                        }
                        tempj = tempj->next; // смещаем голову
                    }
                }
                else // если у нас последняя пара
                {
                    if (tempj->next == NULL) // Если у нас самая первая пара
                    {
                        tempj->prev->next = NULL;
                        tempj->prev->prev = tempj;
                        tempj->next = tempj->prev;
                        tempj->prev = NULL;

                        tempj = tempj->next;
                        if (tempi->next != NULL) {
                            tempi = tempi->next;
                        }
                        head = head->next;

                    }
                    else // Если у нас не первая пара
                    {
                        tempj->next->prev = tempj->prev;
                        tempj->next->prev->prev = tempj;
                        tempj->prev->next = tempj->next;
                        tempj->next = tempj->prev;
                        tempj->prev = NULL;

                        if (tempj == tempi) {
                            tempi = tempi->next;
                        }
                        tempj = tempj->next; // смещаем голову

                    }
                }
            }
            tempj = tempj->prev;
        }
        if (tempi->prev != NULL) {
            tempj = head;
            //tempj = tempi;
            tempi = tempi->prev;

        }
        else {
            break;
        }
    }

    //-----проверка на всяких случай-----
    while (head->next != NULL) {
        head = head->next;
    }


    return head;
}

void printStudentInfo(Student* head, char* option, ...) {

    va_list args;
    if (head == NULL)
    {
        printf("Студентов нет\n");
    }
    else
    {
        if (option == "fullInfo")
        {
            Student* student = head;
            Exam* exam;
            while (student != NULL)
            {
                exam = student->headExam;
                printf("Имя: %s\n", student->name);
                printf("Фамилия: %s\n", student->surname);
                printf("Отчество: %s\n", student->middleName);
                printf("Дата рождения: %s\n", student->birthday);
                printf("Сведения о экзаенах:\n");
                
                while (exam != NULL) {
                    printf("    Название экзамена: %s\n", exam->name);
                    printf("    Дата сдачи: %s\n", exam->examDate);
                    exam = exam->prev;
                }
                printf("\n");
                student = student->prev;
            }
        }
        else if (option == "findInfo") {
            va_start(args, option);
            char* find = va_arg(args, char*);
            Student* student = findStudent(head, find);
            if (student == false) {
                return;
            }
            Exam* exam = student->headExam;

            printf("Имя: %s\n", student->name);
            printf("Фамилия: %s\n", student->surname);
            printf("Отчество: %s\n", student->middleName);
            printf("Дата рождения: %s\n", student->birthday);
            printf("Сведения о экзаенах:\n");
            
            while (exam != NULL) {
                printf("    Название экзамена: %s\n", exam->name);
                printf("    Дата сдачи: %s\n", exam->examDate);
                exam = exam->prev;
            }

            va_end(args);
        }
        else if (option == "findExamInfo") {
            va_start(args, option);
            char* find = va_arg(args, char*);
            Student* student = findStudent(head, find);
            if (student == false) {
                return;
            }

            Exam* exam = student->headExam;
            while (exam != NULL) {
                printf("    Название экзамена: %s\n", exam->name);
                printf("    Дата сдачи: %s\n", exam->examDate);
                exam = exam->prev;
            }

            va_end(args);
        }
    }
}

void mainMenu() {
    char choice = NULL;
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
            addStudent(&head);
            break;
        case '6':
            printStudentInfo(head, "fullInfo");
            break;
        default:
            break;
        }
    }
 }

