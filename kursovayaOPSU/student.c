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
    newStudent->countTests = 0;

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
    newStudent->headTest = NULL;
    newStudent->next = NULL;

    newStudent->prev = *head;
    if (*head != NULL) {
        (*head)->next = newStudent;
    }

    *head = newStudent;



    fseek(stdin, 0, SEEK_END);
    //printf("Добавить экзамены для студента?(y/n)(default no): ");
    printf(
        "(1) Добавить экзамен для студента\n"
        "(2) Добавить зачет для студента\n"
        "(3) Продолжить\n"
        "Ваш выбор: "
    );
    scanf("%c", &choice);
    switch (choice)
    {
    case '1':
        addExam(newStudent);
        break;
    case '2':
        addTest(newStudent);
        break;
    default:
        system("cls");
        break;
    }
}

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
        printf(
            "(1) Добавить еще экзамен\n"
            "(2) Добавить еще зачет\n"
            "(3) Продолжить\n"
            "Ваш выбор: "

        );
        scanf("%c", &choice);
        switch (choice)
        {
        case '1':
            addExam(head);
            break;
        case '2':
            addTest(head);
            break;
        default:
            system("cls");
            break;
        }
    }

}

//----Добавить зачет----
void addTest(Student* head) {
    system("cls");
    printStudentInfo(head, "findInfo", head->name);
    if (head->countTests == 10) {
        printf("Максимальное кол-во зачетов 10.\n");
        return;
    }

    Test* newTest = (Test*)malloc(sizeof(Test));
    Student* pathStudent = head;

    char name[50];
    char testDate[50];
    pathStudent->countTests++;
    //printf("%s", name);

    printf("Добавьте название зачета: ");
    scanf("%s", &name); printf("\n");
    strcpy(newTest->name, name);

    printf("Добавьте дату зачета: ");
    scanf("%s", &testDate); printf("\n");
    strcpy(newTest->testDate, testDate);


    newTest->prev = pathStudent->headTest;
    pathStudent->headTest = newTest;


    if (head->countTests < 10) {
        char choice;
        fseek(stdin, 0, SEEK_END);
        printf(
            "(1) Добавить еще зачет\n"
            "(2) Добавить еще экзамен\n"
            "(3) Продолжить\n"
            "Ваш выбор: "
        );
        scanf("%c", &choice);
        switch (choice)
        {
        case '1':
            addTest(head);
            break;
        case '2':
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





void deleteTest(Student* head) {
    if (head->headTest == NULL) {
        printf("Ни одного зачета не найдено.\n");
        return;
    }

    char nameTest[50];
    printf("Введить название зачета для удаления: ");
    scanf("%s", &nameTest);

    Test* test = head->headTest;
    if (!strcmp(test->name, nameTest))
    {
        Student* temp = test;
        head->headTest = test->prev;
        head->countTests--;
        free(temp);
        printf("Зачет был удален.\n");
        return;
    }
    else
    {
        while (test->prev != NULL) {
            if (!strcmp(test->prev->name, nameTest))
            {
                Student* temp = test->prev;
                test->prev = test->prev->prev;
                head->countTests--;
                free(temp);
                printf("Зачет был удален.\n");
                return;

            }
        }
        printf("Зачет не был найден.\n");
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
                return pthHead;
            }
            pthHead = pthHead->prev;
        }
    }
    printf("Студент не найден\n");
    return false;
}

//---Нужно сделать очистку памяти для зачетов и экзаменов---
void removeStudent(Student** head, char* find) {
    Student* tempHead = *head;
    if (!strcmp((*head)->name, find)) { // 
        
        Student* temp = tempHead;
        if ((*head)->prev == NULL && (*head)->next == NULL) {
            *head = NULL;
            free(temp);
            COUNT_STUDENTS--;
            printf("Студент был удален.\n");
            return;
        }
        if ((*head)->prev != NULL) {
            (*head)->prev->next = (*head)->next;
        }
        else {
            (*head)->next->prev = NULL;
        }
        if ((*head)->next != NULL) {
            (*head)->next->prev = (*head)->prev;
        }
        else {
            (*head)->prev->next = NULL;
        }
        *head = (*head)->prev;
        free(temp);
        COUNT_STUDENTS--;
        printf("Студент был удален.\n");
        return;
    }
    while (tempHead != NULL) {
        if (!strcmp(tempHead->name, find)) {
            Student* temp = tempHead;
            if (tempHead->prev != NULL) {
                tempHead->prev->next = tempHead->next;
            }
            else {
                tempHead->next->prev = NULL;
            }
            if (tempHead->next != NULL) {
                tempHead->next->prev = tempHead->prev;
            }
            else {
                tempHead->prev->next = NULL;
            }

            free(temp);
            COUNT_STUDENTS--;
            printf("Студент был удален.\n");
            return;
        }
        tempHead = tempHead->prev;
    }

    printf("Студент не был найден");

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
    if (head == NULL) {
        printf("Студентов нет\n");
        return NULL;
    }
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
            Test* test;
            while (student != NULL)
            {
                exam = student->headExam;
                test = student->headTest;
                printf("Имя: %s\n", student->name);
                printf("Фамилия: %s\n", student->surname);
                printf("Отчество: %s\n", student->middleName);
                printf("Дата рождения: %s\n", student->birthday);
                printf("Сведения о экзаменах:\n");
                
                while (exam != NULL) {
                    printf("    Название экзамена: %s\n", exam->name);
                    printf("    Дата сдачи: %s\n", exam->examDate);
                    exam = exam->prev;
                }

                printf("Сведения о зачетах:\n");
                while (test != NULL) {
                    printf("    Название зачета: %s\n", test->name);
                    printf("    Дата сдачи: %s\n", test->testDate);
                    test = test->prev;
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
            Test* test = student->headTest;

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

            printf("Сведения о зачетах:\n");
            while (test != NULL) {
                printf("    Название зачета: %s\n", test->name);
                printf("    Дата сдачи: %s\n", test->testDate);
                test = test->prev;
            }

            va_end(args);
            system("pause");
            system("cls");
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
        else if (option == "findTestInfo") {
            va_start(args, option);
            char* find = va_arg(args, char*);
            Student* student = findStudent(head, find);
            if (student == false) {
                return;
            }

            Test* test = student->headTest;
            while (test != NULL) {
                printf("    Название зачета: %s\n", test->name);
                printf("    Дата сдачи: %s\n", test->testDate);
                test = test->prev;
            }

            va_end(args);
        }
        
    }
}

void mainMenu() {
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
            addStudent(&head); // enabled
            break;
        case '2':
            printf("Введите имя студента, которого надо удалить: "); 
            fseek(stdin, 0, SEEK_END);
            scanf("%s", &name);
            removeStudent(&head, name); // enabled
            break;
        case '3':
            system("cls");
            toChangeDataStudent(head); // enabled
            break;
        case '4':
            system("cls");
            fseek(stdin, 0, SEEK_END);
            printf("Введите ФИО искомого студента: ");
            scanf("%s", &name);
            findedStudent = findStudent(head, name); // enabled
            if (findedStudent != false) {
                printf("Для вывода информации о найденном студенте выполните (7)\n");
                system("pause");
;            }
            system("cls");
            break;
        case '5':
            system("cls");
            head = sortStudent(head); // enabled
            if (head != NULL) {
                printf("Список был отсортирован\n");
            }
            break;
        case '6':
            system("cls");
            printStudentInfo(head, "fullInfo"); // enabled
            break;
        case '7':
            system("cls");
            printStudentInfo(head, "findInfo", findedStudent->name); // enabled
            break;
        default:
            break;
        }
    }
 }

void toChangeDataStudent(Student* head) {

    char name[50];
    printf("Для корректировки введите имя студента: ");
    fseek(stdin, 0, SEEK_END);
    scanf("%s", &name);
    Student* student = findStudent(head, name);
    if (student == false) {
        return;
    }

    printStudentInfo(head, "findInfo", name);

    int choice = -1;
    char endterString[50];
    int enterInteher;
    while (choice != 0)
    {
        printf("Выбери действие: \n");
        printf("(0) Выход для програмы\n");
        printf("(1) Изменить имя студента \n");
        printf("(2) Изменить фамилию студента \n");
        printf("(3) Изменить отчество студента \n");
        printf("(4) Изменить дату рождения студента \n");
        printf("(5) Изменить экзаменационные сведения\n");
        printf("(6) Изменить зачетные сведения\n");
        printf("Ваш выбор: ");
        fseek(stdin, 0, SEEK_END);
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            system("cls");
            printf("Имя студента %s\n", student->name);
            printf("Для изменения введите имя: ");
            fseek(stdin, 0, SEEK_END);
            scanf("%s", &endterString);
            strcpy(student->name, endterString);
            system("cls");
            break;
        case 2:
            system("cls");
            printf("Фамилия студента %s\n", student->surname);
            printf("Для изменения введите фамилию: ");
            fseek(stdin, 0, SEEK_END);
            scanf("%s", &endterString);
            strcpy(student->surname, endterString);
            system("cls");
            break;
        case 3:
            system("cls");
            printf("Отчество студента %s\n", student->middleName);
            printf("Для изменения введите отчество: ");
            fseek(stdin, 0, SEEK_END);
            scanf("%s", &endterString);
            strcpy(student->middleName, endterString);
            system("cls");
            break;
        case 4:
            system("cls");
            printf("Дата рождения студента %s\n", student->birthday);
            printf("Для изменения введите дату рождения: ");
            fseek(stdin, 0, SEEK_END);
            scanf("%s", &endterString);
            strcpy(student->birthday, endterString);
            system("cls");
            break;
        case 5:
            system("cls");
            printf("Экзаменационные сведения: \n");

            printStudentInfo(head, "findExamInfo", name);

            printf("Выбери действие:\n");
            printf("(1) Добавить экзамен\n");
            printf("(2) Удалить экзамен\n");
            printf("(3) Назад\n");
            printf("Ваш выбор: ");
            fseek(stdin, 0, SEEK_END);
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("Информация об экзаменах:\n");
                printStudentInfo(student, "findExamInfo", student->name);
                addExam(student, student->headExam);
                printf("Экзамен был создан\n");
                break;

            }
            else if (choice == 2)
            {
                deleteExam(student);
                system("cls");
                printf("Экзамен был удален\n");
                break;
            }
            else if (choice == 3)
            {
                system("cls");
                break;
            }
            system("cls");
            break;
        case 6:
            system("cls");
            printf("Зачетные сведения: \n");

            printStudentInfo(head, "findTestInfo", name);

            printf("Выбери действие:\n");
            printf("(1) Добавить зачет\n");
            printf("(2) Удалить зачет\n");
            printf("(3) Назад\n");
            printf("Ваш выбор: ");
            fseek(stdin, 0, SEEK_END);
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("Информация о зачетах:\n");
                printStudentInfo(student, "findTestInfo", student->name);
                addTest(student, student->headTest);
                printf("Зачет был создан\n");
                break;

            }
            else if (choice == 2)
            {
                deleteTest(student);
                system("cls");
                printf("Зачет был удален\n");
                break;
            }
            else if (choice == 3)
            {
                system("cls");
                break;
            }
            system("cls");
            break;
        default:
            break;
        }
    }

    system("cls");
}