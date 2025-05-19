#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

char stack[MAX];
int top = -1;

// Stack functions for characters
void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

char peek() {
    return stack[top];
}

// Priority of operators
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Check if character is operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// -------- INFIX to POSTFIX --------
void infixToPostfix(char infix[], char postfix[]) {
    int i, j = 0;
    char c;

    for (i = 0; infix[i] != '\0'; i++) {
        c = infix[i];

        if (isalnum(c)) {
            postfix[j++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top != -1 && peek() != '(')
                postfix[j++] = pop();
            pop(); // remove '('
        }
        else if (isOperator(c)) {
            while (top != -1 && precedence(peek()) >= precedence(c))
                postfix[j++] = pop();
            push(c);
        }
    }

    while (top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';
}

// -------- POSTFIX EVALUATION --------
int stackInt[MAX];
int topInt = -1;

void pushInt(int val) {
    stackInt[++topInt] = val;
}

int popInt() {
    return stackInt[topInt--];
}

int evaluatePostfix(char postfix[]) {
    int i, a, b;

    for (i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        if (isdigit(c)) {
            pushInt(c - '0');  // convert char to int
        }
        else {
            b = popInt();
            a = popInt();
            switch (c) {
                case '+': pushInt(a + b); break;
                case '-': pushInt(a - b); break;
                case '*': pushInt(a * b); break;
                case '/': pushInt(a / b); break;
                case '^': pushInt((int)pow(a, b)); break;
            }
        }
    }

    return popInt();
}

// -------- MAIN --------
int main() {
    char infix[MAX], postfix[MAX];
    
    printf("Enter infix expression (use digits only, e.g. 2+3*4): ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix: %s\n", postfix);
    printf("Evaluation Result: %d\n", evaluatePostfix(postfix));

    return 0;
}
