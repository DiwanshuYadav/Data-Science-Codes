#operations on tuples

# Creating a tuple
my_tuple = (1, 2, 3)

# Accessing elements
print(my_tuple[0])  # Output: 1

# Slicing
print(my_tuple[1:3])  # Output: (2, 3)

# Concatenation
another_tuple = (4, 5)
print(my_tuple + another_tuple)  # Output: (1, 2, 3, 4, 5)

# Repetition
print(my_tuple * 2)  # Output: (1, 2, 3, 1, 2, 3)

# Checking membership
print(2 in my_tuple)  # Output: True

# Finding the index of an element

# Counting occurrences of an element
print(my_tuple.index(2))  # Output: 1
print(my_tuple.count(2))  # Output: 1

# Finding the maximum element
print(max(my_tuple))  # Output: 3

# Finding the minimum element
print(min(my_tuple))  # Output: 1

# Finding the sum of elements
print(sum(my_tuple))  # Output: 6

# Finding the product of elements
product = 1
for num in my_tuple:
    product *= num
print(product)  # Output: 6

# Finding the average of elements
average = sum(my_tuple) / len(my_tuple)
print(average)  # Output: 2.0

#count function
print(my_tuple.count(2))  # Output: 1

# Finding the length of the tuple
print(len(my_tuple))  # Output: 3

# Finding the sorted version of the tuple
print(sorted(my_tuple))  # Output: [1, 2, 3]

#Finding max
print(max(my_tuple))  # Output: 3

# Finding min
print(min(my_tuple))  # Output: 1

#Finding sum
print(sum(my_tuple))  # Output: 6

# Using any
print(any(my_tuple))  # Output: True

#using all
print(all(my_tuple))  # Output: True

#conversion to list
print(list(my_tuple))  # Output: [1, 2, 3]

# Conversion to set
print(set(my_tuple))  # Output: {1, 2, 3}

#conversion to dictionary
print(dict(enumerate(my_tuple)))  # Output: {0: 1, 1: 2, 2: 3}

#conversion to string
print(str(my_tuple))  # Output: "(1, 2, 3)"

#reversing the tuple
print(my_tuple[::-1])  # Output: (3, 2, 1)

#using hash 
print(hash(my_tuple))  # Output: Hash value of the tuple
#what is hash? : it is 

# Finding the memory address
print(id(my_tuple))  # Output: Memory address of the tuple

#iteration : what is iteration
# Iteration is the process of looping through elements in a collection (like a tuple) one at a time.
for element in my_tuple:
    print(element)

#packing
packed = my_tuple
print(packed)  # Output: (1, 2, 3)

# unpacking
a, b, c = my_tuple
print(a, b, c)  # Output: 1 2 3

#nested tuples
nested_tuple = (1, 2, (3, 4))
print(nested_tuple)  # Output: (1, 2, (3, 4))

# Accessing elements in a nested tuple
print(nested_tuple[2][0])  # Output: 3

#immutability : Tuples are immutable, meaning their elements cannot be changed after creation.

#time complexity
# The time complexity of common tuple operations:
# - Access: O(1)
# - Slicing: O(k) where k is the size of the slice
# - Concatenation: O(n) where n is the size of the resulting tuple
# - Membership test: O(n) in the worst case

#does tuple allow duplicates?
# Yes, tuples can contain duplicate elements.

#is it ordered?
# Yes, tuples maintain the order of elements.
# The elements in a tuple are ordered, meaning you can access them by index and rely on their order.

#is it mutable?
# No, tuples are immutable, meaning you cannot change their elements after they are created.

#is it hashable?
# Yes, tuples are hashable because they are immutable.

