def fibonacci(n):
    if n <= 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fibonacci(n - 1) + fibonacci(n - 2)

n = int(input("Enter a positive integer: "))
if n < 0:
    print("Invalid input. Please enter a positive integer.")
else:
    print(fibonacci(n))

#Using Loop
def fibonacci_loop(n):
    a, b = 0, 1
    for _ in range(n):
        a, b = b, a + b
    return a

n = int(input("Enter a positive integer: "))
if n < 0:
    print("Invalid input. Please enter a positive integer.")
else:
    print(fibonacci_loop(n))