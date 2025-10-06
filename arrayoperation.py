#operation on array

#array : it is a collection of elements, typically of the same data type, stored in contiguous memory locations.

#creating an array
array = [1, 2, 3, 4, 5]

# Accessing elements
print(array[0])  # Output: 1

# Modifying elements
array[1] = 10

# Adding elements
array.append(6)

# Removing elements
array.remove(3)

# Iterating through elements
for element in array:
    print(element)

# Slicing
print(array[1:4])  # Output: [10, 4, 5]

#transversal
for i in range(len(array)):
    print(array[i])

#insertion
array.insert(0, 0)
print(array)

#deletion
array.remove(10)
print(array)

#searching
print(5 in array)  # Output: True
print(10 in array)  # Output: False

# List comprehension
squared_array = [x**2 for x in array]
print(squared_array)

# Creating a 2D array (list of lists)
two_d_array = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]

# Accessing elements in a 2D array
print(two_d_array[0][1])  # Output: 2

# Iterating through a 2D array
for row in two_d_array:
    for element in row:
        print(element)      

#time complexity
# Accessing elements: O(1)
# Modifying elements: O(1)
# Adding elements: O(1) (amortized)
# Removing elements: O(n)
# Iterating through elements: O(n)
# Slicing: O(k) where k is the size of the slice
# Searching: O(n)

# Traversing: O(n)
# Insertion: O(n)
# Deletion: O(n)
# Searching: O(n)

# Is array ordered or unordered?
# An array is considered ordered if its elements are arranged in a specific sequence (e.g., ascending or descending order).
# An array is unordered if its elements are not arranged in any particular sequence.

# does it allow duplicate elements?
# Yes, arrays can contain duplicate elements.

# How to remove duplicates from an array?
array = [1, 2, 2, 3, 4, 4, 5]
array = list(set(array))
print(array)  # Output: [1, 2, 3, 4, 5]

# does it allow null/None elements?
# Yes, arrays can contain null/None elements.

# is it mutable or immutable?
# Arrays are mutable, meaning their elements can be changed after the array is created.q

# is it hashable?
# No, arrays are not hashable because they are mutable.