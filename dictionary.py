# Example: Using Dictionary in Python
# Dictionary stores data as {key: value}

# Create a dictionary
student_grades = {
    "John": 85,
    "Emma": 92,
    "Liam": 78
}

# Accessing values by key (O(1) operation)
print("Emma's Grade:", student_grades["Emma"])  

# Adding a new key-value pair
student_grades["Sophia"] = 90  

# Updating existing value
student_grades["Liam"] = 80  

# Deleting a key-value pair
del student_grades["John"]

# Iterating through dictionary
for name, grade in student_grades.items():
    print(name, ":", grade)

# Output will show Sophia added, John removed, Liam updated