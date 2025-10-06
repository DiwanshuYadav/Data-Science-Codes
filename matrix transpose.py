matrix = [[1,2,3],[4,5,6],[7,8,9]]
transpose = []

for i in range(len(matrix)):
    for j in range(len(matrix[i])):
        if j >= len(transpose):
            transpose.append([])
        transpose[j].append(matrix[i][j])

print(transpose)



