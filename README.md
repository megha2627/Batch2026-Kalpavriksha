# Student Performance Analyzer

## Description
This is a **console-based C program** that analyzes student performance.  
It accepts student details (Roll Number, Name, Marks in 3 subjects), calculates **total marks**, **average marks**, assigns a **grade**, and displays a **performance pattern using stars (\*)** based on the grade.  

The program demonstrates the use of:
- **Structures**
- **Functions**
- **Loops**
- **Recursion**
- **Arithmetic operations**
- **Control flow (if-else)**
- **Variable scope**

---

## Features
- Calculate total and average marks for each student.
- Assign grades based on average marks:

| Average Marks | Grade | Performance Pattern |
|---------------|-------|-------------------|
| ≥ 85          | A     | ***** (5 stars)   |
| ≥ 70          | B     | **** (4 stars)    |
| ≥ 50          | C     | *** (3 stars)     |
| ≥ 35          | D     | ** (2 stars)      |
| < 35          | F     |                   |

- Print all roll numbers recursively at the end.
- Handles up to **100 students** with marks ranging from 0 to 100.

---

## Sample Input Format
Enter the number of students: 2
Enter the Roll Number, name, subject1Marks, subject2Marks, subject3Marks of students
1 Arti 78 82 90
Enter the Roll Number, name, subject1Marks, subject2Marks, subject3Marks of students
2 Meena 32 28 35


## Sample Output Format
Roll :1
Name :Arti
Total :250
Average :83.33
Grade :B
Performance:****

Roll :2
Name :Meena
Total :95
Average :31.67
Grade :F

List Of Roll Numbers [via recursion]: 1 2
