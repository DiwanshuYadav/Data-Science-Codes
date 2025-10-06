# Take Input

A = [[1, 2, 3],
     [4, 5, 6]]

B = [[7, 8],
     [9, 10],
     [11, 12]]

result = [[0 for _ in range(len(B[0]))] for _ in range(len(A))]

for i in range(len(A)):
    for j in range(len(B[0])):
        for k in range(len(B)):
            result[i][j] += A[i][k] * B[k][j]

print("Result:")
for row in result:
    print(row)




# What is a sparse matrix??
# A sparse matrix is a matrix in which most of the elements are zero.