#operation on set 

#creating a set
my_set = {1, 2, 3}

#accessing elements
print(1 in my_set)  # Output: True
print(4 in my_set)  # Output: False

# Slicing is not supported in sets

# Adding elements
my_set.add(4)
print(my_set)  # Output: {1, 2, 3, 4}

# Removing elements
my_set.remove(2)
print(my_set)  # Output: {1, 3, 4}

#reversing
for item in reversed(my_set):
    print(item)

# Set operations
another_set = {3, 4, 5}
print(my_set.union(another_set))  # Output: {1, 3, 4, 5}
print(my_set.intersection(another_set))  # Output: {3, 4}
print(my_set.difference(another_set))  # Output: {1}

#using sum
print(sum(my_set))  # Output: 8

#using all : it checks if all elements are True
print(all(my_set))  # Output: True
#what if we add a 0 : it will make all() return False because 0 is considered False in a boolean context
my_set.add(0)
print(all(my_set))  # Output: False

#using any : it checks if any element is True
print(any(my_set))  # Output: True

#using not : it checks if all elements are False
print(not any(my_set))  # Output: False

#using isdisjoint : it checks if two sets have no elements in common
print(my_set.isdisjoint(another_set))  # Output: False

#is set mutable?
print(my_set)  # Output: {0, 1, 3, 4}
#yes, we can add or remove elements
my_set.add(5)
print(my_set)  # Output: {0, 1, 3, 4, 5}
my_set.remove(0)
print(my_set)  # Output: {1, 3, 4, 5}

#transformation
my_set = {x * 2 for x in my_set}
print(my_set)  # Output: {2, 6, 8, 10}

#transversing : it is the process of visiting each element in a set
for element in my_set:
    print(element)

#iteration : it is the process of visiting each element in a set
for element in my_set:
    print(element)

#difference in iteration and traversing
# In traversing, we are just visiting each element, while in iteration, we are typically using the elements in some way (e.g., applying a function, collecting results).

#insertion in sets
my_set.add(12)
print(my_set)  # Output: {2, 6, 8, 10, 12}

#deletion in sets
my_set.remove(12)
print(my_set)  # Output: {2, 6, 8, 10}

#searching in sets
print(2 in my_set)  # Output: True
print(5 in my_set)  # Output: False

#time complexity
# Insertion, deletion, and searching in sets all have an average time complexity of O(1).
# This is because sets are implemented as hash tables in Python.
# Hash tables allow for fast access to elements based on their hash value.
#what is a hash table?
# A hash table is a data structure that stores key-value pairs.
# It uses a hash function to compute an index into an array of buckets or slots,
# from which the desired value can be found.
# Hash tables are commonly used to implement sets and dictionaries in Python.
#how hash table is different for set and dictionary?
# In a set, the hash table is used to store unique elements.
# In a dictionary, the hash table is used to store key-value pairs.
#how hash table is implemented in set and dictionary?
# In a set, the hash table stores the elements themselves as keys, with no associated values.
# In a dictionary, the hash table stores key-value pairs, where each key is hashed to find its corresponding value.
#worst case
# The worst-case time complexity for insertion, deletion, and searching in a hash table is O(n),
# where n is the number of elements in the table.
# This can occur when there are many hash collisions, and all elements are stored in a single bucket.
