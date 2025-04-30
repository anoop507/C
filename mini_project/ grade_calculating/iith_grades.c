#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();
double CGPA();
double SGPA(int);
void printDetails();
int gradePoint(char[]);
void addCourseDetail();

int main() {

    // Run this line of code at the beginning of using this prgroam. This is for adding the header and all to the "courses.txt"
    // FILE* file = fopen("courses.txt","w");
    // char s[] = "Course Name";
    // fprintf(file,"Semester | %-30s | Total Credits | Grade |\n",s);
    // fclose(file);

    menu();

    return 0;
}

void menu() {
    printf("\n1. CGPA\n"
        "2. SPGA\n"
        "3. Show details\n"
        "4. Add course detail\n"
        "5. Exit\n"
        "Enter your choice: "
    );
    int ch;
    scanf("%d",&ch);

    switch (ch) {
        case 1:
            printf("CGPA = %.2lf\n",CGPA());
            menu();
            break;
        case 2:
            int semester;
            printf("Enter the semester: ");
            scanf("%d",&semester);
            while (!(semester>=1&&semester<=8)) {
                printf("Invalid input for semester!\nEnter a valid input: ");
                scanf("%d",&semester);
            }
            printf("SGPA of semester %d: %.2lf\n",semester,SGPA(semester));
            menu();
            break;
        case 3:
            printDetails();
            menu();
            break;
        case 4:
            addCourseDetail();
            menu();
            break;
        default:
            return;
    }
}

double CGPA() {
    FILE* file = fopen("courses.txt","r");
    fseek(file,68,SEEK_SET);
    int totalCredit;
    double cgpa;

    char buff[100];
    while (fgets(buff,69,file)) {
        int credit = buff[44] - 48;
        int grade_point;
        if (buff[61] != ' ') {
            char grade[3];
            grade[0] = buff[60];
            grade[1] = buff[61];
            grade[2] = '\0';
            grade_point = gradePoint(grade);
        } else {
            char grade[2];
            grade[0] = buff[60];
            grade[1] = '\0';
            grade_point = gradePoint(grade);
        }
        totalCredit += credit;
        cgpa += credit * grade_point;
    }
    fclose(file);
    return cgpa/totalCredit;
}

double SGPA(int semester) {
    FILE* file = fopen("courses.txt","r");
    fseek(file,68,SEEK_SET);
    int totalCredit;
    double cgpa;

    char buff[100];
    while (fgets(buff,69,file)) {
        if (buff[0]-48 == semester) {
            int credit = buff[44] - 48;
            int grade_point;
            if (buff[61] != ' ') {
                char grade[3];
                grade[0] = buff[60];
                grade[1] = buff[61];
                grade[2] = '\0';
                grade_point = gradePoint(grade);
            } else {
                char grade[2];
                grade[0] = buff[60];
                grade[1] = '\0';
                grade_point = gradePoint(grade);
            }
            totalCredit += credit;
            cgpa += credit * grade_point;
        } else continue;    
    }
    fclose(file);
    if (totalCredit==0) {
        printf("Entries for the given semester doesn't exist!\n");
        return 0;
    } else return cgpa/totalCredit;
}

void printDetails() {
    FILE* file = fopen("courses.txt","r");
    char buff[100];
    while (fgets(buff,69,file)) {
        printf("%s",buff);
    }
    fclose(file);
}

int gradePoint(char grade[]) {
    if (!strcmp(grade,"A+") || !strcmp(grade,"A")) return 10;
    else if (!strcmp(grade,"A-")) return 9;
    else if (!strcmp(grade,"B")) return 8;
    else if (!strcmp(grade,"B-")) return 7;
    else if (!strcmp(grade,"C")) return 6;
    else if (!strcmp(grade,"C-")) return 5;
    else if (!strcmp(grade,"D")) return 4;
    else return 0;
}

void addCourseDetail() {
    FILE* file = fopen("courses.txt","a");
    int semester,totalCredit;
    char course_name[30];
    char grade[3];
    int n;
    printf("Which semester: "); scanf("%d",&semester);
    char c = 'y';
    int i=1;
    while (c == 'y') {
        printf("Course %d:\n",i++);
        printf("\tCourse Name: "); getchar(); fgets(course_name,30,stdin);
        if (course_name[strlen(course_name)-1]=='\n') course_name[strlen(course_name)-1] = '\0';
        printf("\tCredits: "); scanf("%d",&totalCredit);
        printf("\tGrade: "); scanf("%s",grade);
        fprintf(file,"%-8d | %-30s | %-13d | %-5s |\n",semester,course_name,totalCredit,grade);
        getchar();
        printf("To continue adding, enter y.\n");
        c = getchar();
    }
    fclose(file);
}
