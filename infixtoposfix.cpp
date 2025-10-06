#include <iostream>   // For input and output
using namespace std;

#define MAX 100       // Maximum size of stack

// Global stack and top variable
char stackArr[MAX];   // Array to act like stack
int top = -1;         // Initially stack is empty

// Function to push element into stack
void push(char c) {
    stackArr[++top] = c;   // Increase top and add element
}

// Function to pop element from stack
char pop() {
    return stackArr[top--];   // Return element and reduce top
}

// Function to see top element of stack
char peek() {
    return stackArr[top];
}

// Function to check if stack is empty
bool isEmpty() {
    return (top == -1);
}

// Function to check precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;   // Lowest
    if (op == '*' || op == '/') return 2;   // Higher
    if (op == '^') return 3;                // Highest
    return 0;
}

// Function to convert Infix to Postfix
void infixToPostfix(char infix[], char postfix[]) {
    int i = 0, j = 0;   // i for infix, j for postfix

    while (infix[i] != '\0') {   // Loop until end of string
        char c = infix[i];

        // 1. If operand (A-Z, a-z, 0-9) → directly to postfix
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            postfix[j++] = c;
        }

        // 2. If '(' → push into stack
        else if (c == '(') {
            push(c);
        }

        // 3. If ')' → pop until '('
        else if (c == ')') {
            while (!isEmpty() && peek() != '(') {
                postfix[j++] = pop();
            }
            pop(); // remove '(' from stack
        }

        // 4. If operator
        else {
            while (!isEmpty() && precedence(peek()) >= precedence(c)) {
                postfix[j++] = pop();
            }
            push(c);
        }
        i++; // Move to next character
    }

    // Pop remaining operators
    while (!isEmpty()) {
        postfix[j++] = pop();
    }

    postfix[j] = '\0'; // Null terminate string
}

// Main function
int main() {
    char infix[100], postfix[100];

    cout << "Enter Infix Expression: ";
    cin >> infix;

    infixToPostfix(infix, postfix);

    cout << "Postfix Expression: " << postfix << endl;

    return 0;
}

//  Stack
//  Push, Pop and Peek
//  How to check underflow(Push) and overflow(Pop)