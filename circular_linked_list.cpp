#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class CircularLinkedList {
private:
    Node* head;

public:
    CircularLinkedList() {
        head = nullptr;
    }

    // 1. Display
    void display() {
        if (!head) {
            cout << "List is empty!" << endl;
            return;
        }
        Node* temp = head;
        cout << "Circular Linked List: ";
        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);
        cout << "(back to head)" << endl;
    }

    // 2. Insert at beginning
    void insertAtBeginning(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            newNode->next = head;
            return;
        }
        Node* temp = head;
        while (temp->next != head) temp = temp->next;
        newNode->next = head;
        temp->next = newNode;
        head = newNode;
    }

    // 3. Insert at end
    void insertAtEnd(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            newNode->next = head;
            return;
        }
        Node* temp = head;
        while (temp->next != head) temp = temp->next;
        temp->next = newNode;
        newNode->next = head;
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
        for (int i = 0; i < pos - 1 && temp->next != head; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // 5. Delete at beginning
    void deleteAtBeginning() {
        if (!head) {
            cout << "List is empty!" << endl;
            return;
        }
        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next != head) temp = temp->next;
        Node* toDelete = head;
        temp->next = head->next;
        head = head->next;
        delete toDelete;
    }

    // 6. Delete at end
    void deleteAtEnd() {
        if (!head) {
            cout << "List is empty!" << endl;
            return;
        }
        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next->next != head) temp = temp->next;
        Node* toDelete = temp->next;
        temp->next = head;
        delete toDelete;
    }

    // 7. Delete at position
    void deleteAtPosition(int pos) {
        if (!head || pos < 0) {
            cout << "Invalid position or empty list!" << endl;
            return;
        }
        if (pos == 0) {
            deleteAtBeginning();
            return;
        }
        Node* temp = head;
        for (int i = 0; i < pos - 1 && temp->next != head; i++) {
            temp = temp->next;
        }
        if (temp->next == head) {
            cout << "Position out of range!" << endl;
            return;
        }
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    }

    // 8. Search
    void search(int val) {
        if (!head) {
            cout << "List is empty!" << endl;
            return;
        }
        Node* temp = head;
        int index = 0;
        do {
            if (temp->data == val) {
                cout << "Element " << val << " found at position " << index << endl;
                return;
            }
            temp = temp->next;
            index++;
        } while (temp != head);
        cout << "Element not found!" << endl;
    }
};