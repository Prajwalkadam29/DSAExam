#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

char stack[MAX];
int top = -1;

// Stack for characters
void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

char peek() {
    return stack[top];
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// -------- Infix to Prefix --------
void reverse(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void swapBrackets(char str[]) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == '(') str[i] = ')';
        else if (str[i] == ')') str[i] = '(';
    }
}

void infixToPrefix(char infix[], char prefix[]) {
    char rev[MAX], temp[MAX];
    int i, j = 0;

    strcpy(rev, infix);
    reverse(rev);
    swapBrackets(rev);

    top = -1;
    for (i = 0; rev[i]; i++) {
        char c = rev[i];

        if (isalnum(c)) {
            temp[j++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top != -1 && peek() != '(')
                temp[j++] = pop();
            pop(); // remove '('
        }
        else if (isOperator(c)) {
            while (top != -1 && precedence(peek()) >= precedence(c))
                temp[j++] = pop();
            push(c);
        }
    }

    while (top != -1)
        temp[j++] = pop();

    temp[j] = '\0';
    reverse(temp);
    strcpy(prefix, temp);
}

// -------- Prefix Evaluation --------
int stackInt[MAX];
int topInt = -1;

void pushInt(int val) {
    stackInt[++topInt] = val;
}

int popInt() {
    return stackInt[topInt--];
}

int evaluatePrefix(char prefix[]) {
    int i, a, b;
    int len = strlen(prefix);

    for (i = len - 1; i >= 0; i--) {
        char c = prefix[i];

        if (isdigit(c)) {
            pushInt(c - '0');  // convert char to int
        }
        else if (isOperator(c)) {
            a = popInt();
            b = popInt();
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
    char infix[MAX], prefix[MAX];

    printf("Enter infix expression (use digits only, e.g. 2+3*4): ");
    scanf("%s", infix);

    infixToPrefix(infix, prefix);

    printf("Prefix: %s\n", prefix);
    printf("Evaluation Result: %d\n", evaluatePrefix(prefix));

    return 0;
}
