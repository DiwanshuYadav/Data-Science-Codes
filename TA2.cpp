#include <iostream>
#include <string>
#include <limits> // Required for numeric_limits

using namespace std;

// ADT for a Patient Record, implemented as a Node in a Linked List
struct PatientNode {
    int patientID;
    string patientName;
    string admissionDate;
    string treatmentDetails;
    int priority; // For emergency queue
    PatientNode* next;
};

// Node for the Undo Stack
struct UndoNode {
    int patientID;
    UndoNode* next;
};

// Main class to manage all hospital operations
class HospitalSystem {
private:
    PatientNode* admittedHead;    // Head of the admitted patients linked list
    PatientNode* emergencyHead;   // Head of the emergency priority queue
    UndoNode* undoTop;            // Top of the undo stack

public:
    // Constructor
    HospitalSystem() {
        admittedHead = NULL;
        emergencyHead = NULL;
        undoTop = NULL;
        cout << "Hospital Patient Record Management System Initialized." << endl;
    }

    // --- Core Patient Management ---

    // Add a new patient record to the general admissions list
    void addPatientRecord() {
        int id;
        cout << "\n--- Add New Patient Record ---" << endl;
        cout << "Enter Patient ID: ";
        cin >> id;

        // Check for duplicate ID
        PatientNode* current = admittedHead;
        while (current != NULL) {
            if (current->patientID == id) {
                cout << "Error: Patient ID " << id << " already exists." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
                return;
            }
            current = current->next;
        }

        PatientNode* newNode = new PatientNode();
        newNode->patientID = id;
        cout << "Enter Patient Name: ";
        cin.ignore();
        getline(cin, newNode->patientName);
        cout << "Enter Admission Date (DD-MM-YYYY): ";
        getline(cin, newNode->admissionDate);
        cout << "Enter Treatment Details: ";
        getline(cin, newNode->treatmentDetails);
        newNode->next = NULL;

        if (admittedHead == NULL) {
            admittedHead = newNode;
        } else {
            current = admittedHead;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }

        // Push to undo stack
        UndoNode* newUndo = new UndoNode();
        newUndo->patientID = id;
        newUndo->next = undoTop;
        undoTop = newUndo;

        cout << "Success: Patient record added. Action pushed to undo stack." << endl;
    }
    
    // Delete a patient by ID
    void deletePatient(int id, bool showMessage) {
        PatientNode* temp = admittedHead;
        PatientNode* prev = NULL;

        // If head node itself holds the key to be deleted
        if (temp != NULL && temp->patientID == id) {
            admittedHead = temp->next;
            delete temp;
            if(showMessage) cout << "Success: Patient with ID " << id << " deleted." << endl;
            return;
        }

        // Search for the key to be deleted
        while (temp != NULL && temp->patientID != id) {
            prev = temp;
            temp = temp->next;
        }

        // If key was not present in linked list
        if (temp == NULL) {
            if(showMessage) cout << "Error: Patient with ID " << id << " not found." << endl;
            return;
        }
        
        // Unlink the node from linked list
        prev->next = temp->next;
        delete temp;
        if(showMessage) cout << "Success: Patient with ID " << id << " deleted." << endl;
    }

    // Undo the last admission
    void undoAdmission() {
        if (undoTop == NULL) {
            cout << "Nothing to undo." << endl;
            return;
        }
        int idToUndo = undoTop->patientID;
        UndoNode* temp = undoTop;
        undoTop = undoTop->next;
        delete temp;
        
        cout << "Undoing admission for Patient ID " << idToUndo << "..." << endl;
        deletePatient(idToUndo, false); // call delete without showing message again
        cout << "Success: Last admission has been reverted." << endl;
    }
    
    // Retrieve a patient's details
    void retrievePatient() {
        if(admittedHead == NULL) {
            cout << "No admitted patients in the system." << endl;
            return;
        }
        int id;
        cout << "\nEnter Patient ID to retrieve: ";
        cin >> id;

        PatientNode* current = admittedHead;
        while (current != NULL) {
            if (current->patientID == id) {
                cout << "\n--- Patient Record Found ---" << endl;
                cout << "ID: " << current->patientID << endl;
                cout << "Name: " << current->patientName << endl;
                cout << "Admission Date: " << current->admissionDate << endl;
                cout << "Treatment: " << current->treatmentDetails << endl;
                return;
            }
            current = current->next;
        }
        cout << "Error: Patient with ID " << id << " not found." << endl;
    }

    // Display all admitted patients
    void displayAdmittedPatients() {
        cout << "\n--- List of Admitted Patients ---" << endl;
        if (admittedHead == NULL) {
            cout << "No patients have been admitted." << endl;
            return;
        }
        PatientNode* current = admittedHead;
        while (current != NULL) {
            cout<< "ID: " << current->patientID << " | Name: " << current->patientName 
                << " | Admitted: " << current->admissionDate << endl;
            current = current->next;
        }
    }

    // --- Emergency Queue Management ---

    // Add a patient to the priority queue
    void addEmergencyPatient() {
        PatientNode* newNode = new PatientNode();
        cout << "\n--- Add Emergency Patient ---" << endl;
        cout << "Enter Patient ID: ";
        cin >> newNode->patientID;
        cout << "Enter Patient Name: ";
        cin.ignore();
        getline(cin, newNode->patientName);
        cout << "Enter Priority (1=Critical, 5=Minor): ";
        cin >> newNode->priority;
        newNode->next = NULL;

        if (emergencyHead == NULL || newNode->priority < emergencyHead->priority) {
            newNode->next = emergencyHead;
            emergencyHead = newNode;
        } else {
            PatientNode* current = emergencyHead;
            while (current->next != NULL && current->next->priority <= newNode->priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        cout << "Success: Patient added to emergency queue." << endl;
    }

    // Serve the next patient from the emergency queue
    void serveNextEmergency() {
        if (emergencyHead == NULL) {
            cout << "Emergency queue is empty." << endl;
            return;
        }
        PatientNode* temp = emergencyHead;
        emergencyHead = emergencyHead->next;
        cout << "\nServing next patient: " << endl;
        cout << "ID: " << temp->patientID << " | Name: " << temp->patientName << " | Priority: " << temp->priority << endl;
        delete temp;
    }

    // Display the emergency queue
    void displayEmergencyQueue() {
        cout << "\n--- Current Emergency Queue (Highest Priority First) ---" << endl;
        if (emergencyHead == NULL) {
            cout << "The emergency queue is empty." << endl;
            return;
        }
        PatientNode* current = emergencyHead;
        int pos = 1;
        while (current != NULL) {
            cout<< pos++ << ". ID: " << current->patientID << " | Name: " << current->patientName 
                << " | Priority: " << current->priority << endl;
            current = current->next;
        }
    }
    
    // --- Computational Demonstrations ---
    
    // Demonstrate postfix evaluation for inventory
    void evaluateInventory() {
        string postfix = "53*2+"; // Example: (5 * 3) + 2 = 17
        int stack[20];
        int top = -1;
        
        cout << "\n--- Postfix Expression Evaluation for Inventory ---" << endl;
        cout << "Expression: " << postfix << endl;

        for (int i = 0; i < postfix.length(); i++) {
            char ch = postfix[i];
            if (isdigit(ch)) {
                stack[++top] = ch - '0'; // Convert char to int
            } else {
                int op2 = stack[top--];
                int op1 = stack[top--];
                switch (ch) {
                    case '+': stack[++top] = op1 + op2; break;
                    case '-': stack[++top] = op1 - op2; break;
                    case '*': stack[++top] = op1 * op2; break;
                    case '/': stack[++top] = op1 / op2; break;
                }
            }
        }
        cout << "Result (e.g., total required syringes): " << stack[top] << endl;
    }
};

// --- Main Program ---

void displayMenu() {
    cout << "\n=============================================" << endl;
    cout << "   Hospital Patient Record Management System" << endl;
    cout << "=============================================" << endl;
    cout << "1. Add New Patient Record" << endl;
    cout << "2. Undo Last Admission" << endl;
    cout << "3. Retrieve Patient Record" << endl;
    cout << "4. Display All Admitted Patients" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "5. Add Patient to Emergency Queue" << endl;
    cout << "6. Serve Next Emergency Patient" << endl;
    cout << "7. Display Emergency Queue" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "8. Run Inventory Calculation (Postfix Demo)" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter your choice (1-9): ";
}

int main() {
    HospitalSystem hs;
    int choice;
    do {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0; // Reset choice to avoid infinite loop
            continue;
        }
        
        switch (choice) {
            case 1:
                hs.addPatientRecord();
                break;
            case 2:
                hs.undoAdmission();
                break;
            case 3:
                hs.retrievePatient();
                break;
            case 4:
                hs.displayAdmittedPatients();
                break;
            case 5:
                hs.addEmergencyPatient();
                break;
            case 6:
                hs.serveNextEmergency();
                break;
            case 7:
                hs.displayEmergencyQueue();
                break;
            case 8:
                hs.evaluateInventory();
                break;
            case 9:
                cout << "Exiting... Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        cout << "\nName: Diwanshu Yadav" << endl;
        cout << "Roll No: 2401730034" << endl;
    } while (choice != 9);

    return 0;
}