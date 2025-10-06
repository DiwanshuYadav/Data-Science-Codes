lst = [1,2,3,4,5]
for i in lst:
    print(i)

lst.append(19)
print("after append:", lst)
lst.insert(2,41)
print("After insert: ", lst)
lst.extend([70,80])
print("After extend: ", lst)


print(lst*3)