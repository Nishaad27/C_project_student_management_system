#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 10
#define MAX_GRADE_LENGTH 3

struct Student {
    char name[MAX_NAME_LENGTH];
    char id[MAX_ID_LENGTH];
    char grade[MAX_GRADE_LENGTH];
};

void add_student() {
    FILE *fp;
    fp = fopen("students.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    
    struct Student student;
    printf("Enter name: ");
    fgets(student.name, MAX_NAME_LENGTH, stdin);
    student.name[strcspn(student.name, "\n")] = 0; // remove trailing newline
    printf("Enter ID: ");
    fgets(student.id, MAX_ID_LENGTH, stdin);
    student.id[strcspn(student.id, "\n")] = 0;
    printf("Enter grade: ");
    fgets(student.grade, MAX_GRADE_LENGTH, stdin);
    student.grade[strcspn(student.grade, "\n")] = 0;
    
    fprintf(fp, "%s,%s,%s\n", student.name, student.id, student.grade);
    printf("Student added successfully!\n");
    
    fclose(fp);
}

void display_students() {
    FILE *fp;
    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    
    struct Student student;
    printf("Name\t\tID\t\tGrade\n");
    printf("------------------------------------------------\n");
    while (fscanf(fp, "%[^,],%[^,],%s\n", student.name, student.id, student.grade) == 3) {
        printf("%s\t\t%s\t\t%s\n", student.name, student.id, student.grade);
    }
    
    fclose(fp);
}

void search_student() {
    FILE *fp;
    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    
    char search_id[MAX_ID_LENGTH];
    printf("Enter ID to search: ");
    fgets(search_id, MAX_ID_LENGTH, stdin);
    search_id[strcspn(search_id, "\n")] = 0;
    
    struct Student student;
    int found = 0;
    while (fscanf(fp, "%[^,],%[^,],%s\n", student.name, student.id, student.grade) == 3) {
        if (strcmp(search_id, student.id) == 0) {
            printf("Name: %s\n", student.name);
            printf("ID: %s\n", student.id);
            printf("Grade: %s\n", student.grade);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Student not found!\n");
    }
    
    fclose(fp);
}

int main() {
    int choice;
    do {
        printf("\nStudent Database Management System\n");
        printf("===================================\n");
        printf("1. Add student\n");
        printf("2. Display all students\n");
        printf("3. Search for a student\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // remove trailing newline
        
        switch (choice) {
            case 1:
            add_student();
            break;
            case 2:
             display_students();
            case 3:
             search_student();
             break;
             case 4:
             exit(0);
             break;
            default:
            exit(0);
        }
        
    }while(1);
    return 0;
}