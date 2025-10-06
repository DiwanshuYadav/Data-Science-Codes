# TODO: Count the number of digits in a number using recurrsion
def count_digits(n):
    if n == 0:
        return 0
    return 1 + count_digits(n // 10)

number = int(input("Enter a number: "))
print("Number of digits:", count_digits(number))