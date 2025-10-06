#factorial using recursion
def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)
n= int(input("enter a non negative integer: "))
if n<0:
    print("factorial is not defined for negative numbers")
else :
    print(factorial(n))


#fibonacci using recursion
def fibonacci(n):
    if n <= 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fibonacci(n - 1) + fibonacci(n - 2)

n = int(input("Enter a non-negative integer for Fibonacci sequence: "))
if n < 0:
    print("Fibonacci is not defined for negative numbers")
else:
    print(fibonacci(n))

#string reversal using recursion
def reverse_string(s):
    if len(s) == 0:
        return s
    else:
        return s[-1] + reverse_string(s[:-1])

input_string = input("Enter a string to reverse: ")
print(reverse_string(input_string))