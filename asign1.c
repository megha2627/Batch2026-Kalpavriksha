

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



#include<stdio.h>
#include<ctype.h>
#include <string.h>
int main(){
    char str[1000];
    printf("enter the string of expression using only +,-,*,/ operators:\n");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0; 

    int p=strlen(str);
    int curr=0;
    int last = 0;
    
    char sign = '+';
    int result = 0;
    for (int i = 0; i < p;i++){ 
        char chr = str[i];
        if(isdigit(chr)){
            curr = curr * 10 + chr - '0';
        }
        if((!isdigit(chr) && chr != ' ') || i == p- 1){
            if(chr !='+'  && chr!='-' && chr!='*' && chr!='/'&& !isdigit(chr) && !isspace(chr)){
                printf("Error: Invalid expression.\n");
                return 0;
            
            
                
            }
            if (i == p - 1 && !isdigit(chr)) {
                printf("Error: Invalid expression.\n");
                return 0;
            }
            
            if(sign=='+'){
                result = result + last;
                last = curr;
            }
            else if(sign=='-'){
                result = result + last;
                last = -curr;
            }
            else if(sign=='*'){
                last = last * curr;
            }
            else if(sign=='/'){
                if(curr==0){
                    printf("Error: Division by zero.\n");
                    return 0;
                     
                }
                last = last / curr;
            }
            
            sign = chr;
            curr = 0;
                
            
        }
       
       
    }
    result=result+last;
    printf("%d\n", result);
    return 0;
}