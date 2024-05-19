#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "student.h";


void addStudent(Student** head, char* name) {

    Student* newStudent = (Student*)malloc(sizeof(Student));

    newStudent->countExams = 0;
    newStudent->name = name;
    newStudent->headExam = NULL;
    newStudent->next = NULL;

    newStudent->prev = *head;
    if (*head != NULL) {
        (*head)->next = newStudent;
    }

    *head = newStudent;
}

//---headExam нам не нужен-----
void addExam(Student* head, Student* headExam, char* name, char* examDate) {
    Exam* newExam = (Exam*)malloc(sizeof(Exam));
    Student* pathStudent = head;

    pathStudent->countExams++;
    //printf("%s", name);
    newExam->name = name;
    newExam->examDate = examDate;

    newExam->prev = headExam;
    pathStudent->headExam = newExam;
}




void deleteExam(Student* head, char* nameExam) {
    Exam* exam = head->headExam;
    if (exam->name == nameExam)
    {
        Student* temp = exam;
        head->headExam = exam->prev;
        free(temp);
    }
    else
    {
        while (exam->prev != NULL) {
            if (exam->prev->name == nameExam)
            {
                Student* temp = exam->prev;
                exam->prev = exam->prev->prev;
                free(temp);

            }
        }

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

Student* removeStudent(Student* head, char* find) {
    Student* tempHead = head;
    if (head->name == find) {
        Student* temp = head;
        head = head->prev;
        head->next = NULL;
        free(temp);
        return head;
    }
    while (head != NULL) {
        if (head->name == find) {
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
                /*printf("Фамилия: %s\n", student->surname);
                printf("Отчество: %s\n", student->middleName);
                printf("Дата рождения: %s\n", student->birthday);
                printf("Сведения о экзаенах:\n");
                */
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
            /*printf("Фамилия: %s\n", student->surname);
            printf("Отчество: %s\n", student->middleName);
            printf("Дата рождения: %s\n", student->birthday);
            printf("Сведения о экзаенах:\n");
            */
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