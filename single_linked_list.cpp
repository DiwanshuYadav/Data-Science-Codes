#include <iostream>
using namespace std;

// Node class
class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

// Linked List class
class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    // 1. Display list
    void display() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        Node* temp = head;
        cout << "Linked List: ";
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // 2. Insert at beginning
    void insertAtBeginning(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    // 3. Insert at end
    void insertAtEnd(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // 4. Insert at position
    void insertAtPosition(int pos, int val) {
        if (pos < 0) {
            cout << "Invalid position!" << endl;
            return;
        }
        if (pos == 0) {
            insertAtBeginning(val);
            return;
        }
        Node* newNode = new Node(val);
        Node* temp = head;
        for (int i = 0; temp != nullptr && i < pos - 1; i++) {
            temp = temp->next;
        }
        if (temp == nullptr) {
            cout << "Position out of range!" << endl;
            return;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // 5. Delete at beginning
    void deleteAtBeginning() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // 6. Delete at end
    void deleteAtEnd() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }

    // 7. Delete at position
    void deleteAtPosition(int pos) {
        if (pos < 0 || head == nullptr) {
            cout << "Invalid position or empty list!" << endl;
            return;
        }
        if (pos == 0) {
            deleteAtBeginning();
            return;
        }
        Node* temp = head;
        for (int i = 0; temp != nullptr && i < pos - 1; i++) {
            temp = temp->next;
        }
        if (temp == nullptr || temp->next == nullptr) {
            cout << "Position out of range!" << endl;
            return;
        }
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    }

    // 8. Search element
    void search(int val) {
        Node* temp = head;
        int index = 0;
        while (temp != nullptr) {
            if (temp->data == val) {
                cout << "Element " << val << " found at position " << index << endl;
                return;
            }
            temp = temp->next;
            index++;
        }
        cout << "Element not found!" << endl;
    }
};

// Main function (menu-driven using if-else)
int main() {
    LinkedList list;
    int choice, val, pos;

    do {
        cout << "\nMenu:\n";
        cout << "1. Display List\n";
        cout << "2. Insert at Beginning\n";
        cout << "3. Insert at End\n";
        cout << "4. Insert at Position\n";
        cout << "5. Delete at Beginning\n";
        cout << "6. Delete at End\n";
        cout << "7. Delete at Position\n";
        cout << "8. Search Element\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            list.display();
        }
        else if (choice == 2) {
            cout << "Enter value: ";
            cin >> val;
            list.insertAtBeginning(val);
        }
        else if (choice == 3) {
            cout << "Enter value: ";
            cin >> val;
            list.insertAtEnd(val);
        }
        else if (choice == 4) {
            cout << "Enter position (0-based index): ";
            cin >> pos;
            cout << "Enter value: ";
            cin >> val;
            list.insertAtPosition(pos, val);
        }
        else if (choice == 5) {
            list.deleteAtBeginning();
        }
        else if (choice == 6) {
            list.deleteAtEnd();
        }
        else if (choice == 7) {
            cout << "Enter position: ";
            cin >> pos;
            list.deleteAtPosition(pos);
        }
        else if (choice == 8) {
            cout << "Enter value to search: ";
            cin >> val;
            list.search(val);
        }
        else if (choice == 9) {
            cout << "Exiting program..." << endl;
        }
        else {
            cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 9);

    return 0;
}