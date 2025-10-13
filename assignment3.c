
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

void printStudentDetails(studentDetails studenti){
    printf("Roll :%d\n",studenti.rollNumber);
    printf("Name :%s\n",studenti.studentName);
    printf("Total :%d\n",studenti.subject1Marks+studenti.subject2Marks+studenti.subject3Marks);
    printf("Average :%.2f\n",(studenti.subject1Marks+studenti.subject2Marks+studenti.subject3Marks)/3.0);
    float average=(studenti.subject1Marks+studenti.subject2Marks+studenti.subject3Marks)/3.0;
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
void printRollNumber(studentDetails student[],int n,int count){
    if(count==n){
        return;
    }
    printf("%d ",student[count].rollNumber);
    printRollNumber(student,n,count+1);
}
int main(){
    printf("enter the number of students:");
    int n;
    scanf("%d",&n);
    studentDetails student[n];

    for (int i = 0; i <n;i++){
        
        printf("enter the Roll Number,name,subject1Marks,subject2Marks,subject3Marks of students\n");
        scanf("%d %s %d %d %d",&student[i].rollNumber,student[i].studentName,&student[i].subject1Marks,&student[i].subject2Marks,&student[i].subject3Marks);
    }
    printf("\n");
    for (int i = 0; i < n; i++)
    {

        printStudentDetails(student[i]);
        printf("\n");
    }
    printf("List Of Roll Numbers [via recursion]:");
    printRollNumber(student,n,0);
    printf("\n");
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    return 0;
}