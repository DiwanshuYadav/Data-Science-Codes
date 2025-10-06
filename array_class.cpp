#include <iostream>
using namespace std;

class ArrayOperations {
private:
    int arr[];
    int size;       

public:
    ArrayOperations() {
        size = 0;
    }

    void inputArray(int n) {
        size = n;
        cout << "Enter " << n << " elements: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
    }

    void display() {
        cout << "Array elements: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void insertElement(int pos, int val) {
        if (pos < 0 || pos > size || size == 100) {
            cout << "Invalid position or array full!" << endl;
            return;
        }
        for (int i = size; i > pos; i--) {
            arr[i] = arr[i - 1];
        }
        arr[pos] = val;
        size++;
    }

    void deleteElement(int pos) {
        if (pos < 0 || pos >= size) {
            cout << "Invalid position!" << endl;
            return;
        }
        for (int i = pos; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }

    void searchElement(int val) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == val) {
                cout << "Element found at index " << i << endl;
                return;
            }
        }
        cout << "Element not found!" << endl;
    }
};

int main() {
    ArrayOperations obj;
    int choice, n;

    cout << "Enter initial size of array: ";
    cin >> n;
    obj.inputArray(n);

    do {
        cout << "\nMenu:\n";
        cout << "1. Display Array\n";
        cout << "2. Insert Element\n";
        cout << "3. Delete Element\n";
        cout << "4. Search Element\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            obj.display();
        } 
        else if (choice == 2) {
            int pos, val;
            cout << "Enter position (0-based index): ";
            cin >> pos;
            cout << "Enter value: ";
            cin >> val;
            obj.insertElement(pos, val);
        } 
        else if (choice == 3) {
            int pos;
            cout << "Enter position to delete: ";
            cin >> pos;
            obj.deleteElement(pos);
        } 
        else if (choice == 4) {
            int val;
            cout << "Enter value to search: ";
            cin >> val;
            obj.searchElement(val);
        } 
        else if (choice == 5) {
            cout << "Exiting program..." << endl;
        } 
        else {
            cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 5);

    return 0;
}