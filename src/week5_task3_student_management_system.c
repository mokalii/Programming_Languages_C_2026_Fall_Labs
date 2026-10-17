/*
 * week5_task3_student_management_system.c
 * Name:Ali Berk Surname: Cetin Student ID:251ADB185
 * Task 3: Student management system
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;
int load_students(Student arr[], int max);
int save_students(const Student arr[], int count);
void add_student(Student arr[], int *count);
void list_students(const Student arr[], int count);
int read_line(const char *prompt, char *buf, size_t size);
int main(void) {
    Student students[MAX_STUDENTS];
    int count = load_students(students, MAX_STUDENTS);
    char input[LINE_LEN];
    int running = 1;
    printf("Loaded %d student(s) from %s\n", count, DATA_FILE);
    while (running) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");

        int choice;
        if (read_line("Select an option: ", input, sizeof input) != 0) {
            choice = 3;
        } else {
            char *end;
            long value = strtol(input, &end, 10);
            choice = (end != input && *end == '\0') ? (int)value : 0;
        }
        switch (choice) {
            case 1:
                list_students(students, count);
                break;

            case 2:
                add_student(students, &count);
                break;

            case 3:
                if (save_students(students, count) == -1) {
                    printf("Error saving data.\n");
                    return EXIT_FAILURE;
                }
                printf("Data saved. Goodbye!\n");
                running = 0;
                break;

            default:
                printf("Invalid option. Try again.\n");
        }
    }
    return EXIT_SUCCESS;
}
int read_line(const char *prompt, char *buf, size_t size) {
    printf("%s", prompt);
    fflush(stdout);

    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }
    size_t len = strcspn(buf, "\r\n");

    if (buf[len] == '\0' && len == size - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    buf[len] = '\0';
    return 0;
}
// load students from file
int load_students(Student arr[], int max) {
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        return 0;
    }
    char line[LINE_LEN];
    int count = 0;
    while (count < max && fgets(line, sizeof line, fp) != NULL) {
        Student s;
        if (sscanf(line, "%49[^,],%d,%f",
                   s.name, &s.id, &s.gpa) == 3) {
            arr[count] = s;
            count++;
        }
    }
    fclose(fp);
    return count;
}
// ssave students to file
int save_students(const Student arr[], int count) {
    FILE *fp = fopen(DATA_FILE, "w");

    if (fp == NULL) {
        return -1;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%d,%.2f\n",
                arr[i].name, arr[i].id, arr[i].gpa);
    }
    if (fclose(fp) != 0) {
        return -1;
    }
    return 0;
}
//add a new student
void add_student(Student arr[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students (limit reached).\n");
        return;
    }
    char name[LINE_LEN];
    char id_text[LINE_LEN];
    char gpa_text[LINE_LEN];
    char *end;
    if (read_line("Enter name: ", name,sizeof name) != 0) {
        return;
    }

    if (strlen(name)==0 || strlen(name)>= NAME_LEN ||
        strchr(name, ',') != NULL) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    if (read_line("Enter ID: ", id_text, sizeof id_text) != 0) {
        return;
    }
    long id = strtol(id_text, &end, 10);
    if (end == id_text || *end!='\0') {
        printf("Invalid input. Student not added.\n");
        return;
    }
    if (read_line("Enter GPA: ", gpa_text, sizeof gpa_text) != 0) {
        return;
    }
    float gpa = strtof(gpa_text, &end);
    if (end == gpa_text || *end !='\0' ||
        !(gpa >= 0.0f && gpa <= 4.0f)) {
        printf("Invalid input. Student not added.\n");
        return;
    }
    strcpy(arr[*count].name, name);
    arr[*count].id= (int)id;
    arr[*count].gpa =gpa;
    (*count)++;
    printf("Student added successfully!\n");
}
// list all students
void list_students(const Student arr[], int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }
    printf("%-5s %-20s %s\n", "ID", "Name", "GPA");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %.2f\n",
               arr[i].id, arr[i].name, arr[i].gpa);
    }
}