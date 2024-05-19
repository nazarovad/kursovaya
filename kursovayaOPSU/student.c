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
        printf("������������ ���-�� ��������� 20.\n");
        return;
    }
    char name[50]; // ���
    char surname[50]; // �������
    char middleName[50]; // ��������
    char birthday[50]; // ���� ��������
    char choice;
    

    Student* newStudent = (Student*)malloc(sizeof(Student));
    COUNT_STUDENTS++;

    newStudent->countExams = 0;

    //---���������� ������ ���������
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

    newStudent->headExam = NULL;
    newStudent->next = NULL;

    newStudent->prev = *head;
    if (*head != NULL) {
        (*head)->next = newStudent;
    }

    *head = newStudent;



    fseek(stdin, 0, SEEK_END);
    printf("�������� �������� ��� ��������?(y/n)(default no): ");
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

//---headExam ��� �� �����-----
void addExam(Student* head) {
    system("cls");
    printStudentInfo(head, "findInfo", head->name);
    if (head->countExams == 5) {
        printf("������������ ���-�� ��������� 5.\n");
        return;
    }

    Exam* newExam = (Exam*)malloc(sizeof(Exam));
    Student* pathStudent = head;

    char name[50];
    char examDate[50];
    pathStudent->countExams++;
    //printf("%s", name);

    printf("�������� �������� ��������: ");
    scanf("%s", &name); printf("\n");
    strcpy(newExam->name, name);
    
    printf("�������� ���� ��������: ");
    scanf("%s", &examDate); printf("\n");
    strcpy(newExam->examDate, examDate);


    newExam->prev = pathStudent->headExam;
    pathStudent->headExam = newExam;


    if (head->countExams < 5) {
        char choice;
        fseek(stdin, 0, SEEK_END);
        printf("�������� ��� �������?(y/n): ");
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



//---� �������� ��������� �� �������� ������ ��������, �������� �������� �� ����� �������---
void deleteExam(Student* head) {
    if (head->headExam == NULL) {
        printf("�� ������ �������� �� �������.\n");
        return;
    }

    char nameExam[50];
    printf("������� �������� �������� ��� ��������: ");
    scanf("%s", &nameExam);

    Exam* exam = head->headExam;
    if (!strcmp(exam->name, nameExam))
    {
        Student* temp = exam;
        head->headExam = exam->prev;
        head->countExams--;
        free(temp);
        printf("������� ��� ������.\n");
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
                printf("������� ��� ������.\n");
                return;

            }
        }
        printf("������� �� ��� ������.\n");
        return;

    }

}

// ����� �� ���
Student* findStudent(Student* head, char* find) {
    Student* pthHead = head;
    if (pthHead == NULL)
    {
        printf("��������� ���");
        return false;
    }
    else
    {
        while (pthHead != NULL)
        {
            if (!strcmp(pthHead->name, find))
            {
                printf("���������� � ��������:\n");
                return pthHead;
            }
            pthHead = pthHead->prev;
        }
    }
    printf("������� �� ������\n");
    return false;
}


void removeStudent(Student** head, char* find) {
    Student* tempHead = *head;
    if (!strcmp((*head)->name, find)) { // 
        
        Student* temp = tempHead;
        if ((*head)->prev == NULL && (*head)->next == NULL) {
            *head = NULL;
            free(temp);
            COUNT_STUDENTS--;
            printf("������� ��� ������.\n");
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
        printf("������� ��� ������.\n");
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
            printf("������� ��� ������.\n");
            return;
        }
        tempHead = tempHead->prev;
    }

    printf("������� �� ��� ������");

}

//----������ ���� ���� ����� � ����-----
void saveToFile(Student* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "������ �������� ����� %s\n", filename);
        return;
    }

    Student* current = head;
    while (current != NULL) {
        fprintf(file, "���: %s\n", current->name);
        //fprintf(file, "�������: %d\n", current->age);
        fprintf(file, "���������� ���������: %d\n", current->countExams);

        Exam* exam = current->headExam;
        while (exam != NULL) {
            fprintf(file, "    �������� ��������: %s\n", exam->name);
            fprintf(file, "    ���� �����: %s\n", exam->examDate);
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
            if (strcmp(tempj->name, tempj->prev->name) > 0) // ������ ���������� ����������
            {
                if (tempj->prev->prev != NULL) // ���� � ��� �� ��������� ���� (������� �� ������ ��� else ����� �������)
                {
                    if (tempj->next == NULL) // ���� � ��� ����� ������ ����
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
                    else // ���� � ��� �� ������ ����
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
                        tempj = tempj->next; // ������� ������
                    }
                }
                else // ���� � ��� ��������� ����
                {
                    if (tempj->next == NULL) // ���� � ��� ����� ������ ����
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
                    else // ���� � ��� �� ������ ����
                    {
                        tempj->next->prev = tempj->prev;
                        tempj->next->prev->prev = tempj;
                        tempj->prev->next = tempj->next;
                        tempj->next = tempj->prev;
                        tempj->prev = NULL;

                        if (tempj == tempi) {
                            tempi = tempi->next;
                        }
                        tempj = tempj->next; // ������� ������

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

    //-----�������� �� ������ ������-----
    while (head->next != NULL) {
        head = head->next;
    }


    return head;
}

void printStudentInfo(Student* head, char* option, ...) {

    va_list args;
    if (head == NULL)
    {
        printf("��������� ���\n");
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
                printf("���: %s\n", student->name);
                printf("�������: %s\n", student->surname);
                printf("��������: %s\n", student->middleName);
                printf("���� ��������: %s\n", student->birthday);
                printf("�������� � ��������:\n");
                
                while (exam != NULL) {
                    printf("    �������� ��������: %s\n", exam->name);
                    printf("    ���� �����: %s\n", exam->examDate);
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

            printf("���: %s\n", student->name);
            printf("�������: %s\n", student->surname);
            printf("��������: %s\n", student->middleName);
            printf("���� ��������: %s\n", student->birthday);
            printf("�������� � ��������:\n");
            
            while (exam != NULL) {
                printf("    �������� ��������: %s\n", exam->name);
                printf("    ���� �����: %s\n", exam->examDate);
                exam = exam->prev;
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
                printf("    �������� ��������: %s\n", exam->name);
                printf("    ���� �����: %s\n", exam->examDate);
                exam = exam->prev;
            }

            va_end(args);
        }
    }
}

void mainMenu() {
    char choice = NULL;
    char name[50];
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
            addStudent(&head); // enable
            break;
        case '2':
            printf("������� ��� ��������, �������� ���� �������: "); // endable
            fseek(stdin, 0, SEEK_END);
            scanf("%s", &name);
            removeStudent(&head, name);
            break;
        case '6':
            system("cls");
            printStudentInfo(head, "fullInfo"); // enable
            break;
        default:
            break;
        }
    }
 }

