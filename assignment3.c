
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

void printStudentDetails(studentDetails student){
    printf("Roll :%d\n",student.rollNumber);
    printf("Name :%s\n",student.studentName);
    printf("Total :%d\n",student.subject1Marks+student.subject2Marks+student.subject3Marks);
    printf("Average :%.2f\n",(student.subject1Marks+student.subject2Marks+student.subject3Marks)/3.0);
    float average=(student.subject1Marks+student.subject2Marks+student.subject3Marks)/3.0;
    if(average>=85){
        printf("Grade :A\n");
        printf("Performance:*****\n");
    }
    else if(average>=70){
        printf("Grade :B\n");
        printf("Performance:****\n");
    }
    else if(average>=50){
        printf("Grade :C\n");
        printf("Performance:***\n");
    }
    else if(average>=35){
        printf("Grade :D\n");
        printf("Performance:**\n");
    }
    else {
        printf("Grade :F\n");
        return;
    }
  
}
void printRollNumber(studentDetails student[],int numberOfStudents,int count){
    if(count==numberOfStudents){
        return;
    }
    printf("%d ",student[count].rollNumber);
    printRollNumber(student,numberOfStudents,count+1);
}
int main(){
    printf("enter the number of students:");
    int numberOfStudents;
    scanf("%d",&numberOfStudents);
   
    studentDetails student[numberOfStudents];
    if (numberOfStudents <= 0 || numberOfStudents > 100) {
        printf("Invalid number of students! Must be between 1 and 100.\n");
        return 1;
    }

  

    for (int i = 0; i < numberOfStudents; i++) {
        printf("\nEnter details for student %d:\n", i + 1);

        // Roll Number validation
        while (1) {
            int valid = 1;
            printf("Enter Roll Number: ");
            scanf("%d", &student[i].rollNumber);

            if (student[i].rollNumber <= 0) {
                printf("Roll number must be positive. Try again.\n");
                continue;
            }

            // Check duplicate roll numbers
            for (int j = 0; j < i; j++) {
                if (student[i].rollNumber == student[j].rollNumber) {
                    printf("Duplicate roll number detected. Enter a unique one.\n");
                    valid = 0;
                    break;
                }
            }
            if (valid) break;
        }

        printf("Enter Name: ");
        scanf("%s", student[i].studentName);

        // Marks validation
        while (1) {
            printf("Enter marks in 3 subjects (0–100): ");
            scanf("%d %d %d", &student[i].subject1Marks,
                              &student[i].subject2Marks,
                              &student[i].subject3Marks);

            if (student[i].subject1Marks < 0 || student[i].subject1Marks > 100 ||
                student[i].subject2Marks < 0 || student[i].subject2Marks > 100 ||
                student[i].subject3Marks < 0 || student[i].subject3Marks > 100) {
                printf("Invalid marks entered! Each subject mark must be between 0 and 100.\n");
                continue;
            }
            break;
        }
    }
    printf("\n");
    for (int i = 0; i < numberOfStudents; i++)
    {

        printStudentDetails(student[i]);
        printf("\n");
    }
    printf("List Of Roll Numbers [via recursion]:");
    printRollNumber(student,numberOfStudents,0);
    printf("\n");
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    return 0;
}