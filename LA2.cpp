#include <iostream>
#include <string>
#include <limits>

using namespace std;

// ADT for a support ticket, also serves as a linked list node
struct TicketNode {
    int ticketID;
    string customerName;
    string issueDescription;
    int priority;
    TicketNode* next;
};

// Node for the undo stack
struct UndoNode {
    int ticketID;
    UndoNode* next;
};

// Node for polynomial terms
struct TermNode {
    int coefficient;
    int exponent;
    TermNode* next;
};

const int CQUEUE_SIZE = 5; // Fixed size for the circular queue

class TicketSystem {
private:
    TicketNode* ticketListHead;      // Head of the main ticket list
    UndoNode* undoStackTop;        // Top of the undo stack
    TicketNode* priorityQueueHead;   // Head of the priority queue
    
    // Circular Queue components
    TicketNode* circularQueue[CQUEUE_SIZE];
    int front, rear;

public:
    // Constructor
    TicketSystem() {
        ticketListHead = NULL;
        undoStackTop = NULL;
        priorityQueueHead = NULL;
        front = -1;
        rear = -1;
        for (int i = 0; i < CQUEUE_SIZE; i++) {
            circularQueue[i] = NULL;
        }
        cout << "Customer Support Ticket System Initialized." << endl;
    }

    // --- Helper function to delete a ticket by ID ---
    bool deleteTicket(int id) {
        TicketNode* temp = ticketListHead;
        TicketNode* prev = NULL;

        if (temp != NULL && temp->ticketID == id) {
            ticketListHead = temp->next;
            delete temp;
            return true;
        }

        while (temp != NULL && temp->ticketID != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) return false;

        prev->next = temp->next;
        delete temp;
        return true;
    }

    // --- Core Ticket and Undo Operations ---
    void addTicketRecord() {
        int id;
        cout << "\n--- Create New Ticket ---" << endl;
        cout << "Enter Ticket ID: ";
        cin >> id;

        // Check for duplicate ID
        TicketNode* current = ticketListHead;
        while (current != NULL) {
            if (current->ticketID == id) {
                cout << "Error: Ticket ID " << id << " already exists." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return;
            }
            current = current->next;
        }

        TicketNode* newNode = new TicketNode();
        newNode->ticketID = id;
        cout << "Enter Customer Name: ";
        cin.ignore();
        getline(cin, newNode->customerName);
        cout << "Enter Issue Description: ";
        getline(cin, newNode->issueDescription);
        newNode->next = NULL;

        // Append to the end of the list
        if (ticketListHead == NULL) {
            ticketListHead = newNode;
        } else {
            current = ticketListHead;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }

        // Push ID to undo stack
        UndoNode* newUndo = new UndoNode();
        newUndo->ticketID = id;
        newUndo->next = undoStackTop;
        undoStackTop = newUndo;

        cout << "Success: Ticket created and logged." << endl;
    }

    void undoTicketOperation() {
        if (undoStackTop == NULL) {
            cout << "No operations to undo." << endl;
            return;
        }
        int idToUndo = undoStackTop->ticketID;
        UndoNode* temp = undoStackTop;
        undoStackTop = undoStackTop->next;
        delete temp;

        cout << "Undoing creation of Ticket ID " << idToUndo << "..." << endl;
        if (deleteTicket(idToUndo)) {
            cout << "Success: Last ticket creation has been reverted." << endl;
        } else {
            cout << "Info: The ticket to undo was already deleted or processed." << endl;
        }
    }

    void displayAllTickets() {
        cout << "\n--- All Submitted Tickets ---" << endl;
        if (ticketListHead == NULL) {
            cout << "No tickets in the system." << endl;
            return;
        }
        TicketNode* current = ticketListHead;
        while (current != NULL) {
            cout << "ID: " << current->ticketID << " | Customer: " << current->customerName << " | Issue: " << current->issueDescription << endl;
            current = current->next;
        }
    }
    
    // --- Priority Queue ---
    void processPriorityTickets() {
        int choice;
        cout << "\n--- Priority Ticket Menu ---" << endl;
        cout << "1. Add Urgent Ticket\n2. Process Next Urgent Ticket\n3. View Queue\nEnter choice: ";
        cin >> choice;

        if (choice == 1) { // Enqueue
            TicketNode* newNode = new TicketNode();
            cout << "Enter Ticket ID: "; cin >> newNode->ticketID;
            cout << "Enter Customer Name: "; cin.ignore(); getline(cin, newNode->customerName);
            cout << "Enter Issue: "; getline(cin, newNode->issueDescription);
            cout << "Enter Priority (1-5, 1 is highest): "; cin >> newNode->priority;
            newNode->next = NULL;

            if (priorityQueueHead == NULL || newNode->priority < priorityQueueHead->priority) {
                newNode->next = priorityQueueHead;
                priorityQueueHead = newNode;
            } else {
                TicketNode* current = priorityQueueHead;
                while (current->next != NULL && current->next->priority <= newNode->priority) {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }
            cout << "Urgent ticket added to priority queue." << endl;

        } else if (choice == 2) { // Dequeue
            if (priorityQueueHead == NULL) {
                cout << "Priority queue is empty." << endl;
                return;
            }
            TicketNode* temp = priorityQueueHead;
            priorityQueueHead = priorityQueueHead->next;
            cout << "\nProcessing ticket ID " << temp->ticketID << " (Priority: " << temp->priority << ") for " << temp->customerName << endl;
            delete temp;
        } else if (choice == 3) { // Display
            cout << "\n--- Priority Queue ---" << endl;
            if(priorityQueueHead == NULL) { cout << "Empty." << endl; return; }
            TicketNode* current = priorityQueueHead;
            while(current != NULL) {
                cout << "P" << current->priority << " - ID: " << current->ticketID << " (" << current->customerName << ")" << endl;
                current = current->next;
            }
        }
    }

    // --- Circular Queue ---
    void processRoundRobinTickets() {
        int choice;
        cout << "\n--- Round-Robin Ticket Menu ---" << endl;
        cout << "1. Add Ticket\n2. Process Next Ticket\n3. View Queue\nEnter choice: ";
        cin >> choice;

        if (choice == 1) { // Enqueue
            if ((rear + 1) % CQUEUE_SIZE == front) {
                cout << "Round-robin queue is full." << endl;
                return;
            }
            if (front == -1) front = 0;
            rear = (rear + 1) % CQUEUE_SIZE;
            
            TicketNode* newNode = new TicketNode();
            cout << "Enter Ticket ID: "; cin >> newNode->ticketID;
            cout << "Enter Customer Name: "; cin.ignore(); getline(cin, newNode->customerName);
            newNode->issueDescription = "General Query";
            circularQueue[rear] = newNode;
            cout << "Ticket added to round-robin queue." << endl;

        } else if (choice == 2) { // Dequeue
            if (front == -1) {
                cout << "Round-robin queue is empty." << endl;
                return;
            }
            TicketNode* temp = circularQueue[front];
            cout << "\nProcessing ticket ID " << temp->ticketID << " for " << temp->customerName << endl;
            delete temp;
            circularQueue[front] = NULL;
            if (front == rear) { front = rear = -1; } 
            else { front = (front + 1) % CQUEUE_SIZE; }

        } else if (choice == 3) { // Display
            cout << "\n--- Round-Robin Queue ---" << endl;
            if (front == -1) { cout << "Empty." << endl; return; }
            int i = front;
            while(true) {
                cout << "ID: " << circularQueue[i]->ticketID << " (" << circularQueue[i]->customerName << ")" << endl;
                if (i == rear) break;
                i = (i + 1) % CQUEUE_SIZE;
            }
        }
    }

    // --- Polynomial Comparison ---
    void compareBillingHistory() {
        // Create two sample billing histories
        TermNode* hist1 = new TermNode{5, 2, new TermNode{3, 1, new TermNode{2, 0, NULL}}}; // 5x^2 + 3x + 2
        TermNode* hist2 = new TermNode{5, 2, new TermNode{3, 1, new TermNode{2, 0, NULL}}}; // 5x^2 + 3x + 2
        TermNode* hist3 = new TermNode{4, 2, new TermNode{1, 0, NULL}}; // 4x^2 + 1
        
        cout << "\n--- Billing History Comparison ---" << endl;
        cout << "Comparing History 1 and History 2..." << endl;
        bool isEqual = true;
        TermNode *p1 = hist1, *p2 = hist2;
        while(p1 != NULL && p2 != NULL) {
            if (p1->coefficient != p2->coefficient || p1->exponent != p2->exponent) {
                isEqual = false;
                break;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        if (p1 != NULL || p2 != NULL) isEqual = false; // Different lengths

        if (isEqual) cout << "Result: Histories 1 and 2 are IDENTICAL." << endl;
        else cout << "Result: Histories 1 and 2 are DIFFERENT." << endl;
    }
};

void displayMenu() {
    cout << "\n========================================" << endl;
    cout << "   Customer Support Ticket System" << endl;
    cout << "========================================" << endl;
    cout << "1. Create New Ticket" << endl;
    cout << "2. Undo Last Ticket Creation" << endl;
    cout << "3. Display All Tickets" << endl;
    cout << "4. Manage Priority Tickets" << endl;
    cout << "5. Manage Round-Robin Tickets" << endl;
    cout << "6. Compare Billing History (Demo)" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice (1-7): ";
}

int main() {
    TicketSystem ts;
    int choice;
    do {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1: ts.addTicketRecord(); break;
            case 2: ts.undoTicketOperation(); break;
            case 3: ts.displayAllTickets(); break;
            case 4: ts.processPriorityTickets(); break;
            case 5: ts.processRoundRobinTickets(); break;
            case 6: ts.compareBillingHistory(); break;
            case 7: cout << "Exiting system. Goodbye!" << endl; break;
            default: cout << "Invalid choice. Please try again." << endl;
        }
        if (choice != 7) {
            cout << "\nName: Diwanshu Yadav" << endl;
            cout << "Roll No: 2401730034" << endl;
        }
    } while (choice != 7);

    return 0;
}