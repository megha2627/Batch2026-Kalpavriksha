

/*
Assignment 1: Calculator Problem Statement

Description:
Design a console-based calculator program in C that accepts mathematical
expressions as input in the form of strings. The program should evaluate the
expression and return the result. Supported operations include addition (+),
subtraction (-), multiplication (*), and division (/). The program should handle
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

#define MAX_EXPR 1000


int strLength(char str[]) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

// Remove newline if present
void trimNewline(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}


    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}


int applyMulDiv(int a, int b, char op, int *error) {
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0) {
            *error = 1; 
            return 0;
        }
        return a / b;
    }
    return 0; 
}

// Evaluate full expression using stacks for DMAS
int evaluateExpression(char expr[], int *errorFlag) {
    int numStack[MAX_EXPR], numTop = -1;
    char opStack[MAX_EXPR]; int opTop = -1;

    int i = 0, len = strLength(expr);

    while (i < len) {
     
        if (isspace((unsigned char)expr[i])) { i++; continue; }


        int sign = 1;
        if ((expr[i] == '+' || expr[i] == '-') &&
            (i == 0 || isOperator(expr[i-1]))) {
            if (expr[i] == '-') sign = -1;
            i++;
        }

      
        if (isdigit((unsigned char)expr[i])) {
            int num = 0;
            while (i < len && isdigit((unsigned char)expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            num *= sign;
           
            if (opTop >= 0 && (opStack[opTop] == '*' || opStack[opTop] == '/')) {
                char op = opStack[opTop--];
                int prev = numStack[numTop--];
                numStack[++numTop] = applyMulDiv(prev, num, op, errorFlag);
                if (*errorFlag) return 0;
            } else {
                numStack[++numTop] = num;
            }
        }
       
        else if (isOperator(expr[i])) {
          
            if (i == 0 || (i > 0 && isOperator(expr[i-1]))) {
                printf("Error: Invalid expression.\n");
                *errorFlag = 1;
                return 0;
            }
            opStack[++opTop] = expr[i++];
        }
        else {
            printf("Error: Invalid expression.\n");
            *errorFlag = 1;
            return 0;
        }
    }

    int result = numStack[0];
    int numIndex = 1;
    for (int j = 0; j <= opTop; j++) {
        char op = opStack[j];
        int num = numStack[numIndex++];
        if (op == '+') result += num;
        else if (op == '-') result -= num;
    }

    return result;
}

int main() {
    char expression[MAX_EXPR];
    int error = 0;

    printf("Enter a mathematical expression (+, -, *, /):\n");
    fgets(expression, sizeof(expression), stdin);
    trimNewline(expression);

    int result = evaluateExpression(expression, &error);
    if (!error) {
        printf("Result: %d\n", result);
    }
    return 0;
}
