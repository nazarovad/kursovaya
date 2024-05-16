#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char* name;
    int grades;
    struct Exam* prev;
} Exam;

typedef struct Student {
    Exam exam;
    char* name;
    int age;
    int countExams;
    struct Exam* headExam;
    struct Student* prev;
    struct Student* next;
} Student;



void addStudent(Student **head, char* name, int age) {

    Student* newStudent = (Student*)malloc(sizeof(Student));

    newStudent->countExams = 0;
    newStudent->name = name;
    newStudent->headExam = NULL;
    newStudent->next = NULL;
    newStudent->age = age;

    newStudent->prev = *head;
    if (*head != NULL) {
        (*head)->next = newStudent;
    }

    *head = newStudent;
}

void addExam(Student** head, Student** headExam, char* name, int grades) {
    Exam* newExam = (Exam*)malloc(sizeof(Exam));
    Student* pathStudent = *head;
    
    pathStudent->countExams++;
    newExam->name = name;
    newExam->grades = grades;
    
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
        fprintf(file, "Возраст: %d\n", current->age);
        fprintf(file, "Количество экзаменов: %d\n", current->countExams);

        Exam* exam = current->headExam;
        while (exam != NULL) {
            fprintf(file, "    Название экзамена: %s\n", exam->name);
            fprintf(file, "    Оценка: %d\n", exam->grades);
            exam = exam->prev;
        }

        fprintf(file, "\n");
        current = current->prev;
    }

    fclose(file);
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
            if (tempj->countExams > tempj->prev->countExams) // Уловия выполнения сортировки
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
                    }
                    else // Если у нас не первая пара
                    {
                        tempj->next->prev = tempj->prev;
                        tempj->next->prev->prev = tempj;
                        tempj->prev->next = tempj->next;
                        tempj->next = tempj->prev;
                        tempj->prev = NULL;

                        tempj = tempj->next; // смещаем голову
                    }
                }
            }
            tempj = tempj->prev;
        }
        if (tempj->prev != NULL) {
            tempi = tempi->prev;
            tempj = head;
        }
        else {
            break;
        }
    }


    while (head->next != NULL) {
        head = head->next;
    }
    return head;
}






void printStudent(Student* head) {
    if (head == NULL)
    {
        printf("Студентов нет\n");
    }
    else
    {
        Student* pthHead = head;
        Student* pthExamHead = head->headExam;
        while (pthHead != NULL)
        {
            printf("%s %d |",pthHead->name, pthHead->countExams);
            while (pthExamHead != NULL)
            {
                printf("| %s %d ", pthExamHead->exam.name, pthExamHead->exam.grades);
                pthExamHead = pthExamHead->exam.prev;
            }
            pthHead = pthHead->prev;
            if (pthHead != NULL)
            {
                pthExamHead = pthHead->headExam;
            }
            printf("\n");
        }
    }
}

int main() {
    system("chcp 1251 >> null");

    int countStudents = 0;
    Student* head = NULL;
    Student* tail = head;
    

    addStudent(&head, "Andrey", 7);
    addExam(&head, &head->headExam, "информатика", 5);  



    addStudent(&head, "Саша", 1);
    addExam(&head, &head->headExam, "литература", 5);
    addExam(&head, &head->headExam, "матика", 5);

    addStudent(&head, "Лиза", 2);

    addExam(&head, &head->headExam, "матика", 5);
    addExam(&head, &head->headExam, "матика", 5);
    addExam(&head, &head->headExam, "устный р", 5);
    addExam(&head, &head->headExam, "матика", 5);
    addStudent(&head, "Вика", 3);

  //Liza Saha Andre
  // Saha Liza Andrey
  // Saha Andrey Liza
    printStudent(head);

    //head = removeStudent(head, "Лиза");
    printf("\n------------\n");
    head = sortStudent(head);



    printStudent(head);
    

	return 0;
}