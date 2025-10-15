
/*1. Student Performance Analyzer
Design a console-based Student Performance Analyzer program in C that accepts student
details as input and evaluates their academic performance based on marks obtained in
three subjects.
The program should calculate total marks, average marks, assign a grade, and display a
performance pattern using stars (*) based on the grade. It should also demonstrate
programming concepts like arithmetic operators, control flow, loops, functions, recursion,
structures, and variable scope.
Requirements
 The program should use a structure to store student details: Roll Number, Name, Marks
in three subjects.
 The program should calculate Total Marks and Average Marks using arithmetic
operators.
 Assign a Grade using if-else or switch-case logic.
| Average | Grade |
|----------|--------|
| ≥ 85 | A |
| ≥ 70 | B |
| ≥ 50 | C |
| ≥ 35 | D |
| &lt; 35 | F |
 Display a Performance Pattern of stars based on the grade (A: 5, B: 4, C: 3, D: 2).
 If a student’s average is below 35, skip printing the star pattern using continue
statement.
 Include loops to iterate over multiple students, functions to compute
total/average/grade, recursion to print roll numbers, and demonstrate variable scope.
 Use proper input/output formatting to clearly show results for each student.
 Constraints
1. Number of students: 1 ≤ N ≤ 100
2. Marks in each subject: 0 ≤ Marks ≤ 100

Input Format
First line: An integer N (number of students)

Next N lines: (Each line contains the following data separated by spaces)
Roll_Number1 Name1 Marks1 Marks2 Marks3
Roll_Number2 Name2 Marks1 Marks2 Marks3

Output Format
For each student, print the following details:
Roll: &lt;roll_number&gt;
Name: &lt;name&gt;
Total: &lt;total_marks&gt;
Average: &lt;average_marks&gt;
Grade: &lt;grade&gt;
Performance: &lt;pattern of * based on grade&gt;
-- At the end, print:
List of Roll Numbers (via recursion): 1 2 3 ... N*/



//Here is the code for student perfromance analyzer 

/*1. Student Performance Analyzer
Design a console-based Student Performance Analyzer program in C that accepts student
details as input and evaluates their academic performance based on marks obtained in
three subjects.
The program should calculate total marks, average marks, assign a grade, and display a
performance pattern using stars (*) based on the grade. It should also demonstrate
programming concepts like arithmetic operators, control flow, loops, functions, recursion,
structures, and variable scope.
Requirements
 The program should use a structure to store student details: Roll Number, Name, Marks
in three subjects.
 The program should calculate Total Marks and Average Marks using arithmetic
operators.
 Assign a Grade using if-else or switch-case logic.
| Average | Grade |
|----------|--------|
| ≥ 85 | A |
| ≥ 70 | B |
| ≥ 50 | C |
| ≥ 35 | D |
| &lt; 35 | F |
 Display a Performance Pattern of stars based on the grade (A: 5, B: 4, C: 3, D: 2).
 If a student’s average is below 35, skip printing the star pattern using continue
statement.
 Include loops to iterate over multiple students, functions to compute
total/average/grade, recursion to print roll numbers, and demonstrate variable scope.
 Use proper input/output formatting to clearly show results for each student.
 Constraints
1. Number of students: 1 ≤ N ≤ 100
2. Marks in each subject: 0 ≤ Marks ≤ 100

Input Format
First line: An integer N (number of students)

Next N lines: (Each line contains the following data separated by spaces)
Roll_Number1 Name1 Marks1 Marks2 Marks3
Roll_Number2 Name2 Marks1 Marks2 Marks3

Output Format
For each student, print the following details:
Roll: &lt;roll_number&gt;
Name: &lt;name&gt;
Total: &lt;total_marks&gt;
Average: &lt;average_marks&gt;
Grade: &lt;grade&gt;
Performance: &lt;pattern of * based on grade&gt;
-- At the end, print:
List of Roll Numbers (via recursion): 1 2 3 ... N*/



//Here is the code for student perfromance analyzer 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct studentDetails{
    int rollNumber;
    char studentName[50];
    int subject1Marks;
    int subject2Marks;
    int subject3Marks;
} studentDetails;

void printStudentDetails(studentDetails student) {
    int total = student.subject1Marks + student.subject2Marks + student.subject3Marks;
    float average = total / 3.0;

    printf("\nRoll : %d\n", student.rollNumber);
    printf("Name : %s\n", student.studentName);
    printf("Total : %d\n", total);
    printf("Average : %.2f\n", average);

    char grade;

   
    int avgGroup = (int)(average / 10); 

    switch (avgGroup) {
        case 10:
        case 9:
        case 8:
            grade = 'A'; 
            break;
        case 7:
            grade = 'B'; 
            break;
        case 6:
        case 5:
            grade = 'C'; 
            break;
        case 4:
        case 3:
            if (average >= 35)
                grade = 'D';
            else
                grade = 'F';
            break;
        default:
            grade = 'F'; 
            break;
    }

    printf("Grade : %c\n", grade);

    
    if (grade == 'F') {
        printf("Performance: (Skipped due to failing grade)\n");
        return;
    }

    printf("Performance: ");
    int stars;
    switch (grade) {
        case 'A': stars = 5; break;
        case 'B': stars = 4; break;
        case 'C': stars = 3; break;
        case 'D': stars = 2; break;
        default: stars = 0; break;
    }

    for (int i = 0; i < stars; i++)
        printf("*");
    printf("\n");
}


void printRollNumber(studentDetails student[],int numberOfStudents,int count){
    if(count==numberOfStudents){
        return;
    }
    printf("%d ",student[count].rollNumber);
    printRollNumber(student,numberOfStudents,count+1);
}
int getValidNumberOfStudents() {
    char input[10];
    int num;

    while (1) {
        printf("Enter number of students 1–100: ");
        scanf("%s", input);

        
        int valid = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("Invalid input! Please enter a numeric value.\n");
            continue;
        }

        num = atoi(input);
        if (num < 1 || num > 100) {
            printf("Number of students must be between 1 and 100.\n");
            continue;
        }
        return num; 
    }
}


int getValidRollNumber(studentDetails students[], int count) {
    char input[10];
    int roll;

    while (1) {
        printf("Enter Roll Number: ");
        scanf("%s", input);

        // Check if all digits
        int valid = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("Invalid input! Roll number must be numeric.\n");
            continue;
        }

        roll = atoi(input);
        if (roll <= 0) {
            printf("Roll number must be positive.\n");
            continue;
        }

        // Check for duplicate roll number
        int duplicate = 0;
        for (int i = 0; i < count; i++) {
            if (students[i].rollNumber == roll) {
                duplicate = 1;
                break;
            }
        }

        if (duplicate) {
            printf("Duplicate roll number found! Enter unique roll number.\n");
            continue;
        }

        return roll; 
    }
}
int getValidName(char name[]) {
    char input[50];
    while (1) {
        printf("Enter Name: ");
        scanf(" %[^\n]", input); 

        int valid = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isalpha(input[i]) && input[i] != ' ') { 
                valid = 0; 
                break; 
            }
        }

        if (!valid) {
            printf("Invalid input! Name must contain only letters and spaces.\n");
            continue;
        }

        strcpy(name, input); 
        return 1;
    }
}



int getValidMarks(char subjectName[]) {
    char input[10];
    int marks;

    while (1) {
        printf("Enter marks for %s 0–100: ", subjectName);
        scanf("%s", input);

        // Check if input has only digits
        int valid = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("Invalid input! Marks must be numeric.\n");
            continue;
        }

        marks = atoi(input);
        if (marks < 0 || marks > 100) {
            printf("Marks must be between 0 and 100.\n");
            continue;
        }

        return marks;
    }
}


void printRollNumbers(studentDetails students[], int n, int i) {
    if (i == n) return;
    printf("%d ", students[i].rollNumber);
    printRollNumbers(students, n, i + 1);
}

int main() {
    int n = getValidNumberOfStudents();
    studentDetails students[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter roll no. for Student %d:\n", i + 1);
        students[i].rollNumber = getValidRollNumber(students, i);

        getValidName(students[i].studentName);

        students[i].subject1Marks = getValidMarks("Subject 1");
        students[i].subject2Marks = getValidMarks("Subject 2");
        students[i].subject3Marks = getValidMarks("Subject 3");
    }

    
    for (int i = 0; i < n; i++) {
        printStudentDetails(students[i]);
    }

    printf("\nList of Roll Numbers (via recursion): ");
    printRollNumbers(students, n, 0);
    printf("\n-----------------------------------------------------------------------------------------------------\n");

    return 0;
}