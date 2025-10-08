

/*
Assignment 1: Calculator Problem Statement

Description:
Design a console-based calculator program in C that accepts mathematical
expressions as input in the form of strings. The program should evaluate the
expression and return the result. Supported operations include addition (+),
subtraction (-), multiplication (*), and dsiivision (/). The program should handle
integer operations and output the result as an integer, even if the result of
division has a remainder.

Requirements:
1. The input should be a mathematical expression in the form of a string.
2. The input string contains integers and operators (+, -, *, /) only.
3. The program should handle whitespace between numbers and operators, which should be ignored.
4. The program should output the result of the expression as an integer.
5. If division by zero occurs, the program should display an error message: 
   'Error: Division by zero.'
6. If the input expression is invalid (e.g., contains invalid characters), the program should display an error message: 
   'Error: Invalid expression.'
7. The program should follow the order of operations (DMAS), where multiplication 
   and division are performed before addition and subtraction.
8. Consider handling precedence and associativity while evaluating the expression.

Input Format:
- A single line containing the mathematical expression as a string.

Output Format:
- A single integer or an error message depending on the evaluation result.

Test Cases:
1. Input: "3 + 5 * 2"
   Output: 13

2. Input: "3 + a * 2"
   Output: Error: Invalid expression
*/



#include <stdio.h>
#include <ctype.h>
#include <string.h>

int stringLength(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int main() {
    char stringExpression[1000];
   
    printf("Enter the expression using only +, -, *, / operators:\n");
    fgets(stringExpression, sizeof(stringExpression), stdin);
   
    int len = stringLength(stringExpression);
    if (len > 0 && stringExpression[len-1] == '\n')
        stringExpression[len-1] = '\0';

    int lengthOfString = stringLength(stringExpression);

    int currentNumber = 0;
    int lastNumber = 0;
    char currentSign = '+'; 
    int sumOfExpression = 0;
    char prevChar = 0;


    for (int i = 0; i < lengthOfString; i++) {
        unsigned char chr = (unsigned char)stringExpression[i]; 
        if (i == 0 && (chr == '+' || chr == '*' || chr == '/')) {
            printf("Error: Invalid expression \n");
            return 0;
        }
         
        if (i == 0 && chr == '-') {
            currentSign = '-';
            continue;
        }

        if (isdigit(chr)) {
            currentNumber = currentNumber * 10 + (chr - '0');
        }

        if ((!isdigit(chr) && chr != ' ') || i == lengthOfString - 1) {
            if ((prevChar == '+' || prevChar == '-' || prevChar == '*' || prevChar == '/') && 
                (chr == '+' || chr == '-' || chr == '*' || chr == '/')) {
                printf("Error: Invalid expression.\n");
                return 0;
            }    
        

           
            if (chr == '+' || chr == '-' || chr == '*' || chr == '/') {
                prevChar = chr;
            }



           
            if (chr != '+' && chr != '-' && chr != '*' && chr != '/' && !isdigit(chr) && !isspace(chr)) {
                printf("Error: Invalid expression.\n");
                return 0;
            }

           
            if (i == lengthOfString - 1 && !isdigit(chr)) {
                printf("Error: Invalid expression.\n");
                return 0;
            }

           
            if (currentSign == '+') {
                sumOfExpression += lastNumber;
                lastNumber = currentNumber;
            } else if (currentSign == '-') {
                sumOfExpression += lastNumber;
                lastNumber = -currentNumber;
            } else if (currentSign == '*') {
                lastNumber = lastNumber * currentNumber;
            } else if (currentSign == '/') {
                if (currentNumber == 0) {
                    printf("Error: Division by zero.\n");
                    return 0;
                }
                lastNumber = lastNumber / currentNumber;
            }

            currentSign = chr;
            currentNumber = 0;
        }
    }

    sumOfExpression += lastNumber;
    printf("%d\n", sumOfExpression);
    return 0;
}
