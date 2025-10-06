#operations and functions on lists

#creating lists
list_1 = [1, 2, 3, 4, 5]

#accessing elements
#slicing
print(list_1[1:4])  # Output: [2, 3, 4]

#indexing
print(list_1[0])  # Output: 1
print(list_1[2])  # Output: 3

#negative indexing
print(list_1[-1])  # Output: 5
print(list_1[-3])  # Output: 3

#Adding elements

#using append - adds single elements to the end of the list
list_1.append(6)
print(list_1)  # Output: [1, 2, 3, 4, 5, 6]

#using insert - adds elements at a specific position
list_1.insert(0, 0)
print(list_1)  # Output: [0, 1, 2, 3, 4, 5, 6]

#using extend - adds multiple elements to the end of the list
list_1.extend([7, 8, 9])
print(list_1)  # Output: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

#removing elements

#using remove - removes the first occurrence of a value
list_1.remove(4)
print(list_1)  # Output: [0, 1, 2, 3, 5, 6, 7, 8, 9]

#using pop - removes an element at a specific position
list_1.pop(0)
print(list_1)  # Output: [1, 2, 3, 5, 6, 7, 8, 9]

#using del - removes an element at a specific position
del list_1[0]
print(list_1)  # Output: [1, 2, 3, 5, 6, 7, 8, 9]

#using clear - removes all elements from the list
list_1.clear()
print(list_1)  # Output: []

#using sorting and reversing

#using sort - sorts the elements of the list
list_1 = [3, 1, 4, 1, 5, 9]
list_1.sort()
print(list_1)  # Output: [1, 1, 3, 4, 5, 9]

#using sorted - returns a new sorted list without modifying the original
list_2 = [3, 1, 4, 1, 5, 9]
sorted_list = sorted(list_2)
print(sorted_list)  # Output: [1, 1, 3, 4, 5, 9]
print(list_2)  # Output: [3, 1, 4, 1, 5, 9]

#using reverse - reverses the elements of the list
list_1.reverse()
print(list_1)  # Output: [9, 5, 4, 3, 1, 1]

#using reversed - returns a new reversed iterator without modifying the original
list_2 = [3, 1, 4, 1, 5, 9]
reversed_list = list(reversed(list_2))
print(reversed_list)  # Output: [9, 5, 1, 4, 1, 3]
print(list_2)  # Output: [3, 1, 4, 1, 5, 9]

#making list in single statement

#using list comprehension - creates a new list by applying an expression to each element
squared_list = [x**2 for x in list_2]
print(squared_list)  # Output: [9, 1, 16, 1, 25, 81]

#using other functions

#using copy
list_3 = list_2.copy()
print(list_3)  # Output: [3, 1, 4, 1, 5, 9]

#using slicing
list_4 = list_2[1:4]
print(list_4)  # Output: [1, 4, 1]

#using  list_4 as constructor
list_5 = list(list_4)
print(list_5)  # Output: [1, 4, 1]

#using index - returns the first occurrence of a value
print(list_2.index(4))  # Output: 2

#using count - returns the number of occurrences of a value
print(list_2.count(1))  # Output: 2

#using any - returns True if any element of the list is True
print(any(list_2))  # Output: True

#using all - returns True if all elements of the list are True
print(all(list_2))  # Output: False

#using len - returns the number of elements in the list
print(len(list_2))  # Output: 6

#using sum - returns the sum of all elements in the list
print(sum(list_2))  # Output: 22

#using min - returns the smallest element in the list
print(min(list_2))  # Output: 1

#using max - returns the largest element in the list
print(max(list_2))  # Output: 9 

#nested list - moreover like matrix.
nested_list = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
#accessing elements in a nested list
print(nested_list[0][1])  # Output: 2
print(nested_list[1][2])  # Output: 6
print(nested_list[2][0])  # Output: 7

#transversing - it is the process of visiting each element in a list
for sublist in nested_list:
    for item in sublist:
        print(item)

#does list allow duplicates?
# Yes, lists allow duplicate elements.
# If you add the same element multiple times, it will be stored in the list each time.

#is list ordered?
# Yes, lists maintain the order of elements.
# The elements in a list are ordered, meaning you can access them by index and rely on their order.

#is it mutable?
# Yes, lists are mutable, meaning you can change their elements after they are created.

#is it hashable?
# No, lists are not hashable because they are mutable.

#defining time complexity : it is the computational complexity that describes the amount of time it takes to run an algorithm.
#how it is found? : Time complexity is found by analyzing the algorithm and determining how the runtime increases as the input size increases.
#example of how it is calculated : 
# For example, if an algorithm takes 1 millisecond to process 1 item and 2 milliseconds to process 2 items, the time complexity is O(n), where n is the number of items.

# The time complexity for operations on lists is generally O(1) for appending elements and O(n) for accessing or removing elements.
# This is because lists are implemented as dynamic arrays, which allow for fast appends but require shifting elements for removals.
