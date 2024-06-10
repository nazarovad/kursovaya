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
    if (newStudent == NULL) {
        printf("��� ��������� ������");
        return;
    }
    COUNT_STUDENTS++;

    newStudent->countExams = 0;
    newStudent->countTests = 0;

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
    newStudent->headTest = NULL;
    newStudent->next = NULL;

    newStudent->prev = *head;
    if (*head != NULL) {
        (*head)->next = newStudent;
    }

    *head = newStudent;



    fseek(stdin, 0, SEEK_END);
    //printf("�������� �������� ��� ��������?(y/n)(default no): ");
    printf(
        "(1) �������� ������� ��� ��������\n"
        "(2) �������� ����� ��� ��������\n"
        "(3) ����������\n"
        "��� �����: "
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
        printf(
            "(1) �������� ��� �������\n"
            "(2) �������� ��� �����\n"
            "(3) ����������\n"
            "��� �����: "

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

//----�������� �����----
void addTest(Student* head) {
    system("cls");
    printStudentInfo(head, "findInfo", head->name);
    if (head->countTests == 10) {
        printf("������������ ���-�� ������� 10.\n");
        return;
    }

    Test* newTest = (Test*)malloc(sizeof(Test));
    Student* pathStudent = head;

    char name[50];
    char testDate[50];
    pathStudent->countTests++;
    //printf("%s", name);

    printf("�������� �������� ������: ");
    scanf("%s", &name); printf("\n");
    strcpy(newTest->name, name);

    printf("�������� ���� ������: ");
    scanf("%s", &testDate); printf("\n");
    strcpy(newTest->testDate, testDate);


    newTest->prev = pathStudent->headTest;
    pathStudent->headTest = newTest;


    if (head->countTests < 10) {
        char choice;
        fseek(stdin, 0, SEEK_END);
        printf(
            "(1) �������� ��� �����\n"
            "(2) �������� ��� �������\n"
            "(3) ����������\n"
            "��� �����: "
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



void deleteTest(Student* head) {
    if (head->headTest == NULL) {
        printf("�� ������ ������ �� �������.\n");
        return;
    }

    char nameTest[50];
    printf("������� �������� ������ ��� ��������: ");
    scanf("%s", &nameTest);

    Test* test = head->headTest;
    if (!strcmp(test->name, nameTest))
    {
        Student* temp = test;
        head->headTest = test->prev;
        head->countTests--;
        free(temp);
        printf("����� ��� ������.\n");
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
                printf("����� ��� ������.\n");
                return;

            }
        }
        printf("����� �� ��� ������.\n");
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
            if (!strcmp(pthHead->name, find) || !strcmp(pthHead->surname, find) || !strcmp(pthHead->middleName, find))
            {
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

        Exam* exam = (*head)->headExam;
        Test* test= (*head)->headTest;

        while (exam != NULL) {
            Exam* tempExam = exam;
            exam = exam->prev;
            free(tempExam);
        }
        while (test != NULL) {
            Test* tempTest = test;
            test = test->prev;
            free(tempTest);
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


//----boubleSort----
Student* sortStudent(Student* head) {
    if (head == NULL) {
        printf("��������� ���\n");
        return NULL;
    }
    if (head->prev == NULL && head->next == NULL) {
        return head;
    }
    Student* tempi = head;
    Student* tempj = head;

    while (tempi->prev != NULL) {
        while (tempj->prev != NULL) {
            if (strcmp(tempj->surname, tempj->prev->surname) > 0) // ������ ���������� ����������
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
            Test* test;
            while (student != NULL)
            {
                exam = student->headExam;
                test = student->headTest;
                printf("���: %s\n", student->name);
                printf("�������: %s\n", student->surname);
                printf("��������: %s\n", student->middleName);
                printf("���� ��������: %s\n", student->birthday);
                printf("�������� � ���������:\n");
                
                while (exam != NULL) {
                    printf("    �������� ��������: %s\n", exam->name);
                    printf("    ���� �����: %s\n", exam->examDate);
                    exam = exam->prev;
                }

                printf("�������� � �������:\n");
                while (test != NULL) {
                    printf("    �������� ������: %s\n", test->name);
                    printf("    ���� �����: %s\n", test->testDate);
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

            printf("�������� � �������:\n");
            while (test != NULL) {
                printf("    �������� ������: %s\n", test->name);
                printf("    ���� �����: %s\n", test->testDate);
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
                printf("    �������� ��������: %s\n", exam->name);
                printf("    ���� �����: %s\n", exam->examDate);
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
                printf("    �������� ������: %s\n", test->name);
                printf("    ���� �����: %s\n", test->testDate);
                test = test->prev;
            }

            va_end(args);
        }
        
    }
}

// ���� ��� ����������
void mainMenu() {
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
            "(9) ������ ��������� �� ���� .\n"
            "(0) ��������� �������.\n"
            "��� �����: "
        );


        fseek(stdin, 0, SEEK_END);
        scanf("%c", &choice);
        switch (choice)
        {
        case '1':
            addStudent(&head); // enabled
            break;
        case '2':
            printf("������� ��� ��������, �������� ���� �������: "); 
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
            printf("������� ��� �������� ��������: ");
            scanf("%s", &name);
            findedStudent = findStudent(head, name); // enabled
            if (findedStudent != false) {
                printf("��� ������ ���������� � ��������� �������� ��������� (7)\n");
                system("pause");
;            }
            system("cls");
            break;
        case '5':
            system("cls");
            head = sortStudent(head); // enabled
            if (head != NULL) {
                printf("������ ��� ������������\n");
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
        case '8':
            system("cls");
            saveStudentsToFile(head); // enabled
            break;
        case '9': 
            system("cls");
            loadStudentsFromFile(&head); // enabled
        default:
            break;
        }
    }
    //clearData(&head);
 }

void toChangeDataStudent(Student* head) {

    char name[50];
    printf("��� ������������� ������� ��� ��������: ");
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
        printf("������ ��������: \n");
        printf("(0) ����� ��� ��������\n");
        printf("(1) �������� ��� �������� \n");
        printf("(2) �������� ������� �������� \n");
        printf("(3) �������� �������� �������� \n");
        printf("(4) �������� ���� �������� �������� \n");
        printf("(5) �������� ��������������� ��������\n");
        printf("(6) �������� �������� ��������\n");
        printf("��� �����: ");
        fseek(stdin, 0, SEEK_END);
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            system("cls");
            printf("��� �������� %s\n", student->name);
            printf("��� ��������� ������� ���: ");
            fseek(stdin, 0, SEEK_END);
            scanf("%s", &endterString);
            strcpy(student->name, endterString);
            system("cls");
            break;
        case 2:
            system("cls");
            printf("������� �������� %s\n", student->surname);
            printf("��� ��������� ������� �������: ");
            fseek(stdin, 0, SEEK_END);
            scanf("%s", &endterString);
            strcpy(student->surname, endterString);
            system("cls");
            break;
        case 3:
            system("cls");
            printf("�������� �������� %s\n", student->middleName);
            printf("��� ��������� ������� ��������: ");
            fseek(stdin, 0, SEEK_END);
            scanf("%s", &endterString);
            strcpy(student->middleName, endterString);
            system("cls");
            break;
        case 4:
            system("cls");
            printf("���� �������� �������� %s\n", student->birthday);
            printf("��� ��������� ������� ���� ��������: ");
            fseek(stdin, 0, SEEK_END);
            scanf("%s", &endterString);
            strcpy(student->birthday, endterString);
            system("cls");
            break;
        case 5:
            system("cls");
            printf("��������������� ��������: \n");

            printStudentInfo(head, "findExamInfo", name);

            printf("������ ��������:\n");
            printf("(1) �������� �������\n");
            printf("(2) ������� �������\n");
            printf("(3) �����\n");
            printf("��� �����: ");
            fseek(stdin, 0, SEEK_END);
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("���������� �� ���������:\n");
                printStudentInfo(student, "findExamInfo", student->name);
                addExam(student, student->headExam);
                printf("������� ��� ������\n");
                break;

            }
            else if (choice == 2)
            {
                deleteExam(student);
                system("cls");
                printf("������� ��� ������\n");
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
            printf("�������� ��������: \n");

            printStudentInfo(head, "findTestInfo", name);

            printf("������ ��������:\n");
            printf("(1) �������� �����\n");
            printf("(2) ������� �����\n");
            printf("(3) �����\n");
            printf("��� �����: ");
            fseek(stdin, 0, SEEK_END);
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("���������� � �������:\n");
                printStudentInfo(student, "findTestInfo", student->name);
                addTest(student, student->headTest);
                printf("����� ��� ������\n");
                break;

            }
            else if (choice == 2)
            {
                deleteTest(student);
                system("cls");
                printf("����� ��� ������\n");
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


void saveStudentsToFile(Student* head) {
    char* nameFile ;
    //printf("������� �������� ���� ������: ");
    //scanf("%s", &nameFile);
    FILE* file = fopen("student.txt", "w");
    if (file == NULL) {
        printf("�� ������� ������� ���� ��� ������.\n");
        return;
    }

    Student* current = head;
    while (current != NULL) {
        fprintf(file, "���: %s\n", current->name);
        fprintf(file, "�������: %s\n", current->surname);
        fprintf(file, "��������: %s\n", current->middleName);
        fprintf(file, "���� ��������: %s\n", current->birthday);
        fprintf(file, "���������� ���������: %d\n", current->countExams);
        fprintf(file, "���������� �������: %d\n", current->countTests);

        Exam* currentExam = current->headExam;
        if (currentExam == NULL) {
            fprintf(file, "�������: empty");
        }
        while (currentExam != NULL) {
            fprintf(file, "������� ��������: %s\n", currentExam->name);
            fprintf(file, "������� ����: %s\n", currentExam->examDate);

            currentExam = currentExam->prev;
        }


        Test* currentTest = current->headTest;
        if (currentTest == NULL) {
            fprintf(file, "\n�����: empty");
        }
        while (currentTest != NULL) {
            fprintf(file, "����� ��������: %s\n", currentTest->name);
            fprintf(file, "����� ����: %s\n", currentTest->testDate);
            currentTest = currentTest->prev;
        }

        fprintf(file, "\n");

        current = current->prev;
    }

    fclose(file);
    printf("������ � ��������� ��������� � ����.\n");
}

    void loadStudentsFromFile(Student** head) {

        if (*head != NULL) {
            printf("������ ��� ���������");
            return;
        }

        //char* nameFile;
        //printf("������� �������� ����� ������: ");
        //scanf("%s", &nameFile);
        //FILE* file = fopen(&nameFile, "r");
        FILE* file = fopen("students.txt", "r");
        if (file == NULL) {
            printf("���� �� ������ ��� ����.\n");
            return;
        }
        char line[1024]; // ����� ��� ������ ������

        Student* student = *head;

        char str1[50];
        char str2[50];


        while (fgets(line, 1024, file)) {
            if (strstr(line, "���:")) {
                if (student != NULL) {
                    student->next = NULL;
                    student->prev = *head;
                }
                if (*head != NULL) {
                    (*head)->next = student;
                }

                *head = student;
            
                student = (Student*)malloc(sizeof(Student));
                if (student == NULL) {
                    printf("������ ��������� ������");
                    return;
                }
                COUNT_STUDENTS++;
                student->headExam = NULL;
                student->headTest = NULL;
                sscanf(line, "���: %49s", student->name);
            }
            else if (strstr(line, "�������:")) {
                sscanf(line, "�������: %s", student->surname);
            }
            else if (strstr(line, "��������:")) {
                sscanf(line, "��������: %49s", student->middleName);
            }
            else if (strstr(line, "���� ��������:")) {
                sscanf(line, "���� ��������: %49s", student->birthday);
            }
            else if (strstr(line, "���������� ���������:")) {
                sscanf(line, "���������� ���������: %d", &student->countExams);
            }
            else if (strstr(line, "���������� �������:")) {
                sscanf(line, "���������� �������: %d", &student->countTests);
            }
            else if (strstr(line, "������� ��������: ")) {

                sscanf(line, "������� ��������: %s,", &str1);

                Exam* newExam = (Exam*)malloc(sizeof(Exam));

                strcpy(newExam->name, str1);

                newExam->prev = student->headExam;
                student->headExam = newExam;
            }
            else if (strstr(line, "������� ����: ")) {
                sscanf(line, "������� ����: %s,", &str1);
            
                strcpy(student->headExam->examDate, str1);
            }
            else if (strstr(line, "����� ��������: %49s")) {
                fseek(stdin, 0, SEEK_END);
                sscanf(line, "����� ��������: %49s", str1);

                Test* newTest = (Test*)malloc(sizeof(Test));

                strcpy(newTest->name, str1);

                newTest->prev = student->headTest;
                student->headTest = newTest;
       
            }
            else if (strstr(line, "����� ����: %49s")) {
                sscanf(line, "����� ����: %49s", str1);
                strcpy(student->headTest->testDate, str1);
            }
            else if (strstr(line, "�������: empty")) {
                student->headExam = NULL;
            }
            else if (strstr(line, "�����: empty")) {
                student->headTest = NULL;
            }
        }


        student->next = NULL;

        student->prev = *head;
        if (*head != NULL) {
            (*head)->next = student;
        }

        *head = student;

        printf("������ � ��������� ��������� �� �����\n");
        fclose(file);
    
    }

Student* returnArrayStudents(Student* head) {
    Student* arr = (Student*)malloc(sizeof(head));
    int count = 0;
    while (head != NULL) {
        arr = realloc(arr, (sizeof(head) + sizeof(head->prev)));
        arr[count] = *head;
        count++;

        head->prev;
    }
}


void clearData(Student** head) {
    Student* tempHead = *head;
    if ((*head)->next == NULL) { // 

        Student* temp = tempHead;
        if ((*head)->prev == NULL && (*head)->next == NULL) {
            *head = NULL;
            free(temp);
            COUNT_STUDENTS--;
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

        Exam* exam = (*head)->headExam;
        Test* test = (*head)->headTest;

        while (exam != NULL) {
            Exam* tempExam = exam;
            exam = exam->prev;
            free(tempExam);
        }
        while (test != NULL) {
            Test* tempTest = test;
            test = test->prev;
            free(tempTest);
        }

        *head = (*head)->prev;
        free(temp);
        COUNT_STUDENTS--;
        printf("������� ��� ������.\n");
        return;
    }
    while (tempHead != NULL) {

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

        
        tempHead = tempHead->prev;
    }
    free(tempHead);
}