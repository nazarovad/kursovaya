#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

typedef struct {
    char* name;
    char* examDate;
    struct Exam* prev;
} Exam;

typedef struct Student {
    Exam exam;
    char* name; // Имя
    char* surname; // Фамилия
    char* middleName; // Отчество
    int countExams; // Кол-во экзаменов 
    char* birthday; // День рождения
    struct Exam* headExam;
    struct Student* prev;
    struct Student* next;
} Student;



    void addStudent(Student **head, char* name) {

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

void addExam(Student** head, Student** headExam, char* name, char* examDate) {
    Exam* newExam = (Exam*)malloc(sizeof(Exam));
    Student* pathStudent = *head;
    
    pathStudent->countExams++;
    newExam->name = name;
    newExam->examDate = examDate;
    
    newExam->prev = *headExam;
    *headExam = newExam;
}

// Поиск по ФИО
Student* findStudent(Student* head, char* find) {
    Student* pthHead = head;
    if (pthHead == NULL)
    {
        printf("Студентов нет");
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


void toChangeDataStudent(Student *head) {
    //printStudentInfo(head, "fullInfo");
    
}




//----boubleSort----
Student*  sortStudent(Student* head) {
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

            va_end(args);
        }
       
    }
}

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


	return 0;
}