#TODO: Delete a element in Array
def delete_element(arr, element):
    for i in arr:
        if arr[i]==element:
            arr.pop(element)
            position = i
    for i in range(position):
        arr[i] = arr[i+1]
        
