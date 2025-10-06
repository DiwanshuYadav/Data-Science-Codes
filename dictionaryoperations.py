#operation on dictionaries

# Creating a dictionary
my_dict = {"name": "Alice", "age": 30, "city": "New York"}

# Accessing elements
print(my_dict["name"])  # Output: Alice

# Adding elements
my_dict["email"] = "alice@example.com"

# Modifying elements
my_dict["age"] = 31

# Removing elements
del my_dict["city"]

# Checking membership
print("name" in my_dict)  # Output: True
print("city" in my_dict)  # Output: False

# Iterating through keys
for key in my_dict:
    print(key, my_dict[key])

# Iterating through values
for value in my_dict.values():
    print(value)

# Iterating through key-value pairs
for key, value in my_dict.items():
    print(key, value)

# Getting the keys and values as lists
keys = list(my_dict.keys())
values = list(my_dict.values())

# Dictionary comprehension
squared_dict = {x: x**2 for x in range(5)}

# Printing the squared dictionary
print(squared_dict)

#iteration
for key, value in squared_dict.items():
    print(key, value)

#transversal
for key in squared_dict:
    print(key, squared_dict[key])

#insertion
squared_dict[5] = 25
print(squared_dict)  # Output: {0: 0, 1: 1, 2: 4, 3: 9, 4: 16, 5: 25}

#deletion
del squared_dict[0]    
print(squared_dict)  # Output: {1: 1, 2: 4, 3: 9, 4: 16, 5: 25}

#updating
squared_dict[5] = 30
print(squared_dict)  # Output: {1: 1, 2: 4, 3: 9, 4: 16, 5: 30}

#searching
print(5 in squared_dict)  # Output: True
print(10 in squared_dict)  # Output: False

#using get() method
print(squared_dict.get(5))  # Output: 30
print(squared_dict.get(10))  # Output: None

#using any()
print(any(key in squared_dict for key in [5, 10]))  # Output: True

#using all()
print(all(key in squared_dict for key in [5, 10]))  # Output: False

#using filter() : it filters the keys
#how it filters the keys: it checks each key in the list [5, 10] against the dictionary keys
print(list(filter(lambda key: key in squared_dict, [5, 10])))  # Output: [5]

#how it works: it applies the lambda function to each element in the list [5, 10]
#the lambda function checks if the key is in the dictionary
#what is lambda function? A lambda function is a small anonymous function defined with the lambda keyword.
#what is the use of lambda function? Lambda functions are often used for short, throwaway functions that are not reused elsewhere.
#how does a lambda function work? A lambda function can take any number of arguments, but can only have one expression.

#is dictionary comprehension? Yes, dictionary comprehension is a concise way to create dictionaries in Python. It consists of key-value pairs enclosed in curly braces, with an optional condition.

#time complexity
# The average time complexity for accessing, inserting, and deleting elements in a dictionary is O(1).
# However, the worst-case time complexity can be O(n) in cases of hash collisions.

# Insertion and deletion operations may also require rehashing, which can impact performance.

#is dictionary ordered or unordered? In Python 3.7 and later, dictionaries are ordered collections, meaning they maintain the insertion order of keys.

#is it mutable or immutable? Dictionaries are mutable, meaning their contents can be changed after creation.

#does it allow duplicate keys? No, dictionaries do not allow duplicate keys. If a duplicate key is used, the last value assigned to that key will overwrite any previous value.
