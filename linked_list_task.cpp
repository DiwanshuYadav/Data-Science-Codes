#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = nullptr;

// Insert at beginning
void insertAtBeginning(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
    cout << "Inserted " << value << " at the beginning.\n";
}

// Insert at end
void insertAtEnd(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    cout << "Inserted " << value << " at the end.\n";
}

// Insert at a position
void insertAtPosition(int value, int pos) {
    Node* newNode = new Node();
    newNode->data = value;

    if (pos == 1) {
        newNode->next = head;
        head = newNode;
        cout << "Inserted " << value << " at position " << pos << ".\n";
        return;
    }

    Node* temp = head;
    for (int i = 1; temp != nullptr && i < pos - 1; i++) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Position out of range!\n";
        delete newNode;
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    cout << "Inserted " << value << " at position " << pos << ".\n";
}

// Delete from beginning
void deleteBeginning() {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }
    Node* temp = head;
    head = head->next;
    cout << "Deleted " << temp->data << " from beginning.\n";
    delete temp;
}

// Delete from end
void deleteEnd() {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }
    if (head->next == nullptr) {
        cout << "Deleted " << head->data << " from end.\n";
        delete head;
        head = nullptr;
        return;
    }
    Node* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    cout << "Deleted " << temp->next->data << " from end.\n";
    delete temp->next;
    temp->next = nullptr;
}

// Delete from specific position
void deleteAtPosition(int pos) {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }

    if (pos == 1) {
        Node* temp = head;
        head = head->next;
        cout << "Deleted " << temp->data << " from position " << pos << ".\n";
        delete temp;
        return;
    }

    Node* temp = head;
    for (int i = 1; temp != nullptr && i < pos - 1; i++) {
        temp = temp->next;
    }

    if (temp == nullptr || temp->next == nullptr) {
        cout << "Position out of range!\n";
        return;
    }

    Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    cout << "Deleted " << nodeToDelete->data << " from position " << pos << ".\n";
    delete nodeToDelete;
}

// Search an element
void searchElement(int value) {
    Node* temp = head;
    int pos = 1;
    while (temp != nullptr) {
        if (temp->data == value) {
            cout << "Element " << value << " found at position " << pos << ".\n";
            return;
        }
        temp = temp->next;
        pos++;
    }
    cout << "Element " << value << " not found in the list.\n";
}

// Traverse
void traverse() {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }
    Node* temp = head;
    cout << "Linked List: ";
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

int main() {
    int choice, value, pos;
    while (true) {
        cout << "\n--- Menu ---\n";
        cout << "1. Insert at Beginning\n";
        cout << "2. Insert at End\n";
        cout << "3. Insert at Position\n";
        cout << "4. Delete from Beginning\n";
        cout << "5. Delete from End\n";
        cout << "6. Delete from Position\n";
        cout << "7. Search Element\n";
        cout << "8. Traverse\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                insertAtBeginning(value);
                break;
            case 2:
                cout << "Enter value: ";
                cin >> value;
                insertAtEnd(value);
                break;
            case 3:
                cout << "Enter value and position: ";
                cin >> value >> pos;
                insertAtPosition(value, pos);
                break;
            case 4:
                deleteBeginning();
                break;
            case 5:
                deleteEnd();
                break;
            case 6:
                cout << "Enter position: ";
                cin >> pos;
                deleteAtPosition(pos);
                break;
            case 7:
                cout << "Enter value to search: ";
                cin >> value;
                searchElement(value);
                break;
            case 8:
                traverse();
                break;
            case 0:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid option! Try again.\n";
        }
    }
}
