#include <iostream>
using namespace std;

// Node structure for Doubly Linked List
struct Node {
    int data;
    Node* prev;
    Node* next;
};

// Class for Doubly Linked List
class DoublyLinkedList {
private:
    Node* head;

public:
    // Constructor
    DoublyLinkedList() {
        head = nullptr;
    }

    // Function to create a new node
    Node* createNode(int data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->prev = nullptr;
        newNode->next = nullptr;
        return newNode;
    }

    // Insertion at the beginning
    void insertAtBeginning(int data) {
        Node* newNode = createNode(data);
        if (head == nullptr) {
            head = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        cout << "Inserted " << data << " at the beginning.\n";
    }

    // Insertion at the end
    void insertAtEnd(int data) {
        Node* newNode = createNode(data);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
        cout << "Inserted " << data << " at the end.\n";
    }

    // Insertion at a specific position (1-based index)
    void insertAtPosition(int data, int position) {
        if (position < 1) {
            cout << "Invalid position.\n";
            return;
        }
        if (position == 1) {
            insertAtBeginning(data);
            return;
        }

        Node* newNode = createNode(data);
        Node* temp = head;

        for (int i = 1; temp != nullptr && i < position - 1; i++) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Position out of bounds.\n";
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;

        if (temp->next != nullptr)
            temp->next->prev = newNode;

        temp->next = newNode;
        cout << "Inserted " << data << " at position " << position << ".\n";
    }

    // Deletion from beginning
    void deleteFromBeginning() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = head;
        head = head->next;
        if (head != nullptr)
            head->prev = nullptr;
        cout << "Deleted " << temp->data << " from beginning.\n";
        delete temp;
    }

    // Deletion from end
    void deleteFromEnd() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;
        if (temp->next == nullptr) {
            cout << "Deleted " << temp->data << " from end.\n";
            delete temp;
            head = nullptr;
            return;
        }

        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->prev->next = nullptr;
        cout << "Deleted " << temp->data << " from end.\n";
        delete temp;
    }

    // Deletion from a specific position
    void deleteFromPosition(int position) {
        if (head == nullptr || position < 1) {
            cout << "Invalid position or empty list.\n";
            return;
        }

        Node* temp = head;

        if (position == 1) {
            deleteFromBeginning();
            return;
        }

        for (int i = 1; temp != nullptr && i < position; i++) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Position out of bounds.\n";
            return;
        }

        if (temp->prev != nullptr)
            temp->prev->next = temp->next;

        if (temp->next != nullptr)
            temp->next->prev = temp->prev;

        cout << "Deleted " << temp->data << " from position " << position << ".\n";
        delete temp;
    }

    // Display list from beginning to end
    void displayForward() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;
        cout << "List (forward): ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Display list from end to beginning
    void displayBackward() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        cout << "List (backward): ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout << endl;
    }

    // Search for a value
    void search(int key) {
        Node* temp = head;
        int position = 1;
        while (temp != nullptr) {
            if (temp->data == key) {
                cout << "Value " << key << " found at position " << position << ".\n";
                return;
            }
            temp = temp->next;
            position++;
        }
        cout << "Value " << key << " not found in the list.\n";
    }
};

// Main function
int main() {
    DoublyLinkedList dll;
    int choice, value, position;

    while (true) {
        cout << "\n--- Doubly Linked List Menu ---\n";
        cout << "1. Insert at Beginning\n";
        cout << "2. Insert at End\n";
        cout << "3. Insert at Position\n";
        cout << "4. Delete from Beginning\n";
        cout << "5. Delete from End\n";
        cout << "6. Delete from Position\n";
        cout << "7. Display Forward\n";
        cout << "8. Display Backward\n";
        cout << "9. Search\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            dll.insertAtBeginning(value);
            break;
        case 2:
            cout << "Enter value: ";
            cin >> value;
            dll.insertAtEnd(value);
            break;
        case 3:
            cout << "Enter value and position: ";
            cin >> value >> position;
            dll.insertAtPosition(value, position);
            break;
        case 4:
            dll.deleteFromBeginning();
            break;
        case 5:
            dll.deleteFromEnd();
            break;
        case 6:
            cout << "Enter position: ";
            cin >> position;
            dll.deleteFromPosition(position);
            break;
        case 7:
            dll.displayForward();
            break;
        case 8:
            dll.displayBackward();
            break;
        case 9:
            cout << "Enter value to search: ";
            cin >> value;
            dll.search(value);
            break;
        case 0:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}