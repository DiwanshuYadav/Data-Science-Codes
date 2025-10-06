class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None
    
    def is_empty(self):
        return self.head is None
    
    def append(self, data):
        new_node = Node(data)
        if self.is_empty():
            self.head = new_node
            return
        
        current = self.head
        while current.next:
            current = current.next
        current.next = new_node
    
    def prepend(self, data):
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node
    
    def delete(self, data):
        if self.is_empty():
            return
            
        if self.head.data == data:
            self.head = self.head.next
            return
            
        current = self.head
        while current.next and current.next.data != data:
            current = current.next
            
        if current.next:
            current.next = current.next.next
    
    def search(self, data):
        current = self.head
        while current:
            if current.data == data:
                return True
            current = current.next
        return False
    
    def size(self):
        count = 0
        current = self.head
        while current:
            count += 1
            current = current.next
        return count
    
    def print_list(self):
        if self.is_empty():
            print("List is empty")
            return
            
        current = self.head
        while current:
            print(current.data, end=" -> ")
            current = current.next
        print("None")


def main():
    # Create a new linked list
    lst = LinkedList()
    
    while True:
        print("\nLinked List Operations:")
        print("1. Append an element")
        print("2. Prepend an element")
        print("3. Delete an element")
        print("4. Search for an element")
        print("5. Get size of the list")
        print("6. Print the list")
        print("7. Exit")
        
        choice = input("Enter your choice (1-7): ")
        
        if choice == '1':
            data = input("Enter data to append: ")
            lst.append(data)
            print(f"{data} has been appended to the list.")
            
        elif choice == '2':
            data = input("Enter data to prepend: ")
            lst.prepend(data)
            print(f"{data} has been prepended to the list.")
            
        elif choice == '3':
            if lst.is_empty():
                print("List is empty!")
            else:
                data = input("Enter data to delete: ")
                if lst.search(data):
                    lst.delete(data)
                    print(f"{data} has been deleted from the list.")
                else:
                    print(f"{data} not found in the list.")
                    
        elif choice == '4':
            data = input("Enter data to search: ")
            if lst.search(data):
                print(f"{data} is present in the list.")
            else:
                print(f"{data} is not present in the list.")
                
        elif choice == '5':
            print(f"Size of the list is: {lst.size()}")
            
        elif choice == '6':
            print("Linked List:")
            lst.print_list()
            
        elif choice == '7':
            print("Exiting...")
            break
            
        else:
            print("Invalid choice! Please try again.")

if __name__ == "__main__":
    main()
