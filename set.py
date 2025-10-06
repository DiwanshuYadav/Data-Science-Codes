# Example: Using Set in Python

# Creating a set
unique_numbers = {1, 2, 3, 4, 4, 5}  # duplicate '4' is ignored

print("Unique Numbers:", unique_numbers)  

# Adding an element
unique_numbers.add(6)

# Removing an element
unique_numbers.remove(3)

# Membership test (O(1))
print("Is 2 in the set?", 2 in unique_numbers)

# Set operations (important in Data Structures)
a = {1, 2, 3}
b = {3, 4, 5}

print("Union:", a | b)         # {1, 2, 3, 4, 5}
print("Intersection:", a & b)  # {3}
print("Difference:", a - b)    # {1, 2}