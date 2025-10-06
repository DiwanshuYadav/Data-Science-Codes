class Node:
    def _init_(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def _init_(self):
        self.head = None

    # 1. Display list
    def display(self):
        if self.head is None:
            print("List is empty!")
            return
        temp = self.head
        print("Linked List:", end=" ")
        while temp:
            print(temp.data, end=" -> ")
            temp = temp.next
        print("NULL")

    # 2. Insert at beginning
    def insert_at_beginning(self, val):
        new_node = Node(val)
        new_node.next = self.head
        self.head = new_node

    # 3. Insert at end
    def insert_at_end(self, val):
        new_node = Node(val)
        if self.head is None:
            self.head = new_node
            return
        temp = self.head
        while temp.next:
            temp = temp.next
        temp.next = new_node

    # 4. Insert at position
    def insert_at_position(self, pos, val):
        if pos < 0:
            print("Invalid position!")
            return
        if pos == 0:
            self.insert_at_beginning(val)
            return
        new_node = Node(val)
        temp = self.head
        for _ in range(pos - 1):
            if temp is None:
                print("Position out of range!")
                return
            temp = temp.next
        if temp is None:
            print("Position out of range!")
            return
        new_node.next = temp.next
        temp.next = new_node

    # 5. Delete at beginning
    def delete_at_beginning(self):
        if self.head is None:
            print("List is empty!")
            return
        self.head = self.head.next

    # 6. Delete at end
    def delete_at_end(self):
        if self.head is None:
            print("List is empty!")
            return
        if self.head.next is None:
            self.head = None
            return
        temp = self.head
        while temp.next.next:
            temp = temp.next
        temp.next = None

    # 7. Delete at position
    def delete_at_position(self, pos):
        if pos < 0 or self.head is None:
            print("Invalid position or empty list!")
            return
        if pos == 0:
            self.delete_at_beginning()
            return
        temp = self.head
        for _ in range(pos - 1):
            if temp is None:
                print("Position out of range!")
                return
            temp = temp.next
        if temp is None or temp.next is None:
            print("Position out of range!")
            return
        temp.next = temp.next.next

    # 8. Search element
    def search(self, val):
        temp = self.head
        index = 0
        while temp:
            if temp.data == val:
                print(f"Element {val} found at position {index}")
                return
            temp = temp.next
            index += 1
        print("Element not found!")

# Main program
if _name_ == "_main_":
    ll = LinkedList()

    while True:
        print("\nMenu:")
        print("1. Display List")
        print("2. Insert at Beginning")
        print("3. Insert at End")
        print("4. Insert at Position")
        print("5. Delete at Beginning")
        print("6. Delete at End")
        print("7. Delete at Position")
        print("8. Search Element")
        print("9. Exit")

        choice = int(input("Enter your choice: "))

        if choice == 1:
            ll.display()
        elif choice == 2:
            val = int(input("Enter value: "))
            ll.insert_at_beginning(val)
        elif choice == 3:
            val = int(input("Enter value: "))
            ll.insert_at_end(val)
        elif choice == 4:
            pos = int(input("Enter position (0-based index): "))
            val = int(input("Enter value: "))
            ll.insert_at_position(pos, val)
        elif choice == 5:
            ll.delete_at_beginning()
        elif choice == 6:
            ll.delete_at_end()
        elif choice == 7:
            pos = int(input("Enter position: "))
            ll.delete_at_position(pos)
        elif choice == 8:
            val = int(input("Enter value to search: "))
            ll.search(val)
        elif choice == 9:
            print("Exiting program...")
            break
        else:
            print("Invalid choice! Try again.")