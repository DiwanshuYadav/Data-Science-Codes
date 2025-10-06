#operations and functios on frozen set 

#what is a frozen set?
# A frozen set is an immutable version of a set in Python.
# Once a frozen set is created, its elements cannot be changed, added, or removed.
# This makes frozen sets hashable and usable as keys in dictionaries or elements in other sets.

#creating a frozen set
frozen_set_1 = frozenset([1, 2, 3, 4, 5])
frozen_set_2 = frozenset([4, 5, 6, 7, 8])

# Set operations
print(frozen_set_1.union(frozen_set_2))  # Output: frozenset({1, 2, 3, 4, 5, 6, 7, 8})
print(frozen_set_1.intersection(frozen_set_2))  # Output: frozenset({4, 5})
print(frozen_set_1.difference(frozen_set_2))  # Output: frozenset({1, 2, 3})

# Accessing elements
print(1 in frozen_set_1)  # Output: True
print(6 in frozen_set_1)  # Output: False

# Accessing elements in a frozen set is similar to a regular set.
# You can use the 'in' keyword to check for membership.

# However, you cannot modify the elements of a frozen set.
#example
try:
    frozen_set_1.add(6)
except AttributeError as e:
    print(e)  # Output: 'frozenset' object has no attribute 'add'

# You cannot remove elements from a frozen set either.
try:
    frozen_set_1.remove(1)
except AttributeError as e:
    print(e)  # Output: 'frozenset' object has no attribute 'remove'

# You cannot clear a frozen set either.
try:
    frozen_set_1.clear()
except AttributeError as e:
    print(e)  # Output: 'frozenset' object has no attribute 'clear'

#using any
print(any(x in frozen_set_1 for x in [1, 6]))  # Output: True

# using all
print(all(x in frozen_set_1 for x in [1, 2]))  # Output: True

#using none
print(none(x in frozen_set_1 for x in [1, 6]))  # Output: False

#using sum
print(sum(x in frozen_set_1 for x in [1, 2, 3, 6]))  # Output: 3

#transversal
for item in frozen_set_1:
    print(item)

#iteration
for item in frozen_set_1:
    print(item)

#reversing
for item in reversed(frozen_set_1):
    print(item)

#insertion: Not allowed

#deletion: Not allowed

#searching
print(1 in frozen_set_1)  # Output: True
print(6 in frozen_set_1)  # Output: False

#difference in set and frozenset
# The main difference between a set and a frozenset is mutability.
# A set is mutable, meaning you can add or remove elements after it is created.
# A frozenset is immutable, meaning once it is created, you cannot change its elements.
# This immutability makes frozensets hashable, allowing them to be used as keys in dictionaries or elements in other sets, whereas regular sets cannot be used in this way.

#do it has any impact on performance?
# Yes, the immutability of frozensets can lead to performance improvements in certain situations.
# For example, since frozensets are hashable, they can be used as keys in dictionaries, which allows for faster lookups.
# Additionally, the immutability of frozensets means that they can be safely shared between different parts of a program without the risk of modification.

#time complexity
# The time complexity for operations on frozensets is similar to that of regular sets.
# Lookups, insertions, and deletions all have an average time complexity of O(1).
# However, since frozensets are immutable, certain operations (like adding or removing elements) are not allowed.
#worst case
# The worst-case time complexity for operations on frozensets is O(n), where n is the number of elements in the frozenset.
# This can occur when there are many hash collisions, and all elements are stored in a single bucket.

#are there duplicates in frozenset?
# No, frozensets do not allow duplicate elements.
# If you try to add a duplicate element to a frozenset, it will simply be ignored.

#is it ordered?
# No, frozensets do not maintain any order among their elements.
# The elements in a frozenset are unordered, meaning you cannot access them by index or rely on any specific order.

#frozensets and memory
# Frozensets can be more memory-efficient than regular sets, especially when storing large amounts of data.
# Since frozensets are immutable, they can be optimized by the Python interpreter in ways that regular sets cannot.

#frozen sets are immutable, unordered, hashable and do not allow duplicates.

#by whom time complexity is calculated?
# Time complexity is typically calculated by algorithm designers and computer scientists.
# They analyze the algorithm's structure and behavior to determine how its runtime or space requirements grow with input size.
#how it is found?
# Time complexity is found by analyzing the algorithm and determining how the runtime increases as the input size increases.
