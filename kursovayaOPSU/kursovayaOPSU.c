#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include "student.h";
#include <string.h>



int main() {
    Student** studentsList = (Student*)malloc(sizeof(Student));
    system("chcp 1251 >> null");
    
    mainMenu(&studentsList);


    free(studentsList);
	return 0;
}