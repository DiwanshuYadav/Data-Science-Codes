# Example: Using Frozenset in Python

# Creating a frozenset
fset = frozenset([1, 2, 3, 2, 1])  # duplicates removed automatically

print("Frozenset:", fset)

# Frozenset does not allow adding or removing elements
# fset.add(4)  # ❌ ERROR
# fset.remove(2)  # ❌ ERROR

# But we can still do set operations
a = frozenset([1, 2, 3])
b = frozenset([3, 4, 5])

print("Union:", a | b)         # frozenset({1, 2, 3, 4, 5})
print("Intersection:", a & b)  # frozenset({3})
print("Difference:", a - b)    # frozenset({1, 2})