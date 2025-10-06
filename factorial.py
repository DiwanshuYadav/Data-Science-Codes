def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)
    
n = int(input("Enter a non-negative integer: "))
if n < 0:
    print("Invalid input. Please enter a non-negative integer.")
else:
    print(factorial(n)) 