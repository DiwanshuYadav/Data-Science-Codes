#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

// ADT (Abstract Data Type) for an inventory item
struct Item {
    int id;
    string name;
    int quantity;
    double price;
};

// Structure for representing non-zero entries in a sparse matrix
struct SparseEntry {
    int row;
    int col;
    int value;
};

class InventorySystem {
private:
    // The inventory array is given an explicit limit with this constant.
    static const int INVENTORY_LIMIT = 100;
    Item items[INVENTORY_LIMIT];
    int itemCount; // Tracks the current number of items in the array

    // Helper function to convert a string to lowercase for case-insensitive searching
    string toLower(string s) {
        string lower_s = s;
        for (int i = 0; i < lower_s.length(); i++) {
            lower_s[i] = tolower(lower_s[i]);
        }
        return lower_s;
    }

public:
    // Default constructor to initialize the system
    InventorySystem() {
        itemCount = 0; // Inventory is initially empty
        cout << "Inventory System Initialized." << endl;
    }

    // --- Core Inventory Operations ---

    // Adds a new item to the inventory
    void addItemRecord(int id, string name, int quantity, double price) {
        if (itemCount >= INVENTORY_LIMIT) {
            cout << "Error: Inventory is full. Cannot add new items." << endl << endl;
            return;
        }
        for (int i = 0; i < itemCount; i++) {
            if (items[i].id == id) {
                cout << "Error: Item with ID " << id << " already exists." << endl << endl;
                return;
            }
        }
        items[itemCount] = {id, name, quantity, price};
        itemCount++;
        cout << "Success: Item '" << name << "' added to inventory." << endl << endl;
    }

    // Removes an item from the inventory by its ID
    void removeItemRecord(int id) {
        int foundIndex = -1;
        for (int i = 0; i < itemCount; i++) {
            if (items[i].id == id) {
                foundIndex = i;
                break;
            }
        }
        if (foundIndex != -1) {
            // Shift elements to the left to fill the gap
            for (int i = foundIndex; i < itemCount - 1; i++) {
                items[i] = items[i + 1];
            }
            itemCount--;
            cout << "Success: Item with ID " << id << " has been removed." << endl << endl;
        } else {
            cout << "Error: Item with ID " << id << " not found." << endl << endl;
        }
    }

    // Updates the quantity and price of an existing item
    void updateItem(int id, int newQuantity, double newPrice) {
        for (int i = 0; i < itemCount; i++) {
            if (items[i].id == id) {
                cout << "Updating item '" << items[i].name << "'..." << endl;
                items[i].quantity = newQuantity;
                items[i].price = newPrice;
                cout << "Success: Item ID " << id << " updated." << endl << endl;
                return;
            }
        }
        cout << "Error: Item with ID " << id << " not found for update." << endl << endl;
    }

    // Searches for an item by its ID (integer)
    void searchByItem(int id) {
        for (int i = 0; i < itemCount; i++) {
            if (items[i].id == id) {
                cout << "--- Item Found ---" << endl;
                cout << "ID: " << items[i].id << ", Name: " << items[i].name << ", Quantity: " << items[i].quantity << ", Price: $" << fixed << setprecision(2) << items[i].price << endl;
                cout << "------------------" << endl << endl;
                return;
            }
        }
        cout << "Search: Item with ID '" << id << "' not found." << endl << endl;
    }
    
    // Displays all items currently in the inventory
    void displayInventory(){
        if (itemCount == 0) {
            cout << "Inventory is empty." << endl;
        } else {
            for (int i = 0; i < itemCount; i++) {
                cout << "ID: " << items[i].id << ", Name: " << items[i].name << ", Quantity: " << items[i].quantity << ", Price: $" << fixed << setprecision(2) << items[i].price << endl;
            }
        }
        cout << "-------------------------" << endl << endl;
    }
    
    // --- Advanced Features ---

    // Demonstrates accessing a 2D array using row-major and column-major logic
    void managePriceQuantity() {
        cout << "--- Row-Major vs. Column-Major Demonstration ---" << endl;
        if (itemCount == 0) {
            cout << "Error: No items in inventory. Please add items first." << endl << endl;
            return;
        }
        
        // Display the price-quantity matrix for all items
        cout << "\nPrice-Quantity Matrix (Items x Attributes):" << endl;
        cout << "-------------------------------------------" << endl;
        cout << setw(15) << "Item Name" << setw(12) << "Price ($)" << setw(12) << "Quantity" << endl;
        cout << "-------------------------------------------" << endl;
        
        for (int i = 0; i < itemCount; i++) {
            cout << setw(15) << items[i].name << setw(12) << fixed << setprecision(2) << items[i].price << setw(12) << items[i].quantity << endl;
        }
        cout << "-------------------------------------------" << endl;
        
        // Demonstrate row-major vs column-major access
        if (itemCount >= 2) {
            cout << "\nDemonstrating Array Access Methods:" << endl;
            cout << "Conceptual 2D Array: [Items][Attributes] where Attributes = {Price, Quantity}" << endl;
            
            // Choose an item to demonstrate (e.g., item at index 1)
            int demo_row = 1;
            int demo_col = 0; // 0 for price, 1 for quantity
            int total_rows = itemCount;
            int total_cols = 2; // price and quantity
            
            cout << "\nAccessing Item '" << items[demo_row].name << "' (Row " << demo_row << "):" << endl;
            
            // Row-Major Order
            int row_major_index = (demo_row * total_cols) + demo_col;
            cout << "  Row-Major Index (Price): (" << demo_row << " * " << total_cols << ") + " << demo_col << " = " << row_major_index << endl;
            cout << "  Value: $" << items[demo_row].price << endl;
            
            demo_col = 1;
            row_major_index = (demo_row * total_cols) + demo_col;
            cout << "  Row-Major Index (Quantity): (" << demo_row << " * " << total_cols << ") + " << demo_col << " = " << row_major_index << endl;
            cout << "  Value: " << items[demo_row].quantity << endl;
            
            // Column-Major Order
            cout << "\n  Column-Major Index (Price): (" << 0 << " * " << total_rows << ") + " << demo_row << " = " << demo_row << endl;
            cout << "  Value: $" << items[demo_row].price << endl;
            
            cout << "  Column-Major Index (Quantity): (" << 1 << " * " << total_rows << ") + " << demo_row << " = " << (total_rows + demo_row) << endl;
            cout << "  Value: " << items[demo_row].quantity << endl;
            
            cout << "\nNote: Row-major stores data row-by-row, Column-major stores column-by-column." << endl << endl;
        }
    }
    
    // Helper function for the sparse matrix demonstration
    int getValueFromSparse(const SparseEntry arr[], int size, int r, int c) {
        for(int i = 0; i < size; ++i) {
            if (arr[i].row == r && arr[i].col == c) {
                return arr[i].value;
            }
        }
        return 0; // Default value for elements not in the list is 0
    }

    // Demonstrates using a sparse representation (COO) to save space
    void optimizeSparseStorage() {
        cout << "--- Sparse Matrix Storage Demonstration ---" << endl;
        
        if (itemCount == 0) {
            cout << "Error: No items in inventory. Please add items first." << endl << endl;
            return;
        }
        
        cout << "Scenario: Tracking inventory across multiple store branches." << endl;
        cout << "\nFull Matrix Representation (ItemID x BranchID):" << endl;
        cout << "Most cells would be 0 (no stock), wasting memory." << endl;
        
        // Create sparse entries from current inventory
        // Simulate: Each item has stock only in specific branches
        const int NUM_BRANCHES = 5;
        SparseEntry sparse_inventory[INVENTORY_LIMIT * 2]; // Assuming max 2 branches per item
        int sparse_count = 0;
        
        // Create sparse entries: only store non-zero quantities
        for (int i = 0; i < itemCount && i < 5; i++) {
            // Simulate: Item exists in branch (i % NUM_BRANCHES) with its quantity
            int branch = (i % NUM_BRANCHES) + 1;
            sparse_inventory[sparse_count++] = {items[i].id, branch, items[i].quantity};
            
            // Some items might be in a second branch with reduced quantity
            if (items[i].quantity > 50) {
                int branch2 = ((i + 2) % NUM_BRANCHES) + 1;
                sparse_inventory[sparse_count++] = {items[i].id, branch2, items[i].quantity / 2};
            }
        }
        
        cout << "\nSparse Matrix (COO Format): {[ItemID, BranchID, Quantity]}" << endl;
        cout << "Only storing non-zero entries:" << endl;
        cout << "-------------------------------------------" << endl;
        cout << setw(12) << "Item ID" << setw(15) << "Branch ID" << setw(15) << "Quantity" << endl;
        cout << "-------------------------------------------" << endl;
        
        for (int i = 0; i < sparse_count; i++) {
            cout << setw(12) << sparse_inventory[i].row << setw(15) << sparse_inventory[i].col << setw(15) << sparse_inventory[i].value << endl;
        }
        cout << "-------------------------------------------" << endl;
        
        // Demonstrate querying
        if (sparse_count > 0) {
            cout << "\nQuerying Sparse Matrix:" << endl;
            int query_item = sparse_inventory[0].row;
            int query_branch = sparse_inventory[0].col;
            int result = getValueFromSparse(sparse_inventory, sparse_count, query_item, query_branch);
            cout << "Query: Stock of Item ID " << query_item << " at Branch " << query_branch << "? -> " << result << " units" << endl;
            
            // Query a non-existent entry
            result = getValueFromSparse(sparse_inventory, sparse_count, query_item, 99);
            cout << "Query: Stock of Item ID " << query_item << " at Branch 99? -> " << result << " units (not stored)" << endl;
        }
        
        cout << "\nMemory Efficiency:" << endl;
        cout << "Full Matrix: " << itemCount << " items x " << NUM_BRANCHES << " branches = " 
             << (itemCount * NUM_BRANCHES) << " cells" << endl;
        cout << "Sparse Storage: Only " << sparse_count << " non-zero entries stored" << endl;
        cout << "Space Saved: " << fixed << setprecision(1) 
             << (100.0 * (itemCount * NUM_BRANCHES - sparse_count) / (itemCount * NUM_BRANCHES))  << "%" << endl << endl;
    }
};

// Function to display the menu options
void displayMenu() {
    cout << "\n=== Inventory Management System ===" << endl;
    cout << "1. Add a new item" << endl;
    cout << "2. Remove an item" << endl;
    cout << "3. Update an item" << endl;
    cout << "4. Search for an item" << endl;
    cout << "5. Display all items" << endl;
    cout << "6. Demonstrate Price-Quantity Matrix" << endl;
    cout << "7. Demonstrate Sparse Storage" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice (1-8): ";
}

// Main function to run the program with interactive menu
int main() {
    InventorySystem my_store;
    int choice;
    
    do {
        displayMenu();
        cin >> choice;
        
        // Clear input buffer
        while (cin.get() != '\n');
        
        switch(choice) {
            case 1: {
                // Add a new item
                int id, quantity;
                string name;
                double price;
                
                cout << "\n--- Add New Item ---" << endl;
                cout << "Enter item ID: ";
                cin >> id;
                
                cout << "Enter item name: ";
                getline(cin >> ws, name);
                
                cout << "Enter quantity: ";
                cin >> quantity;
                
                cout << "Enter price: ";
                cin >> price;
                
                my_store.addItemRecord(id, name, quantity, price);
                cout << "Item added successfully!" << endl;
                cout << "Name: Diwanshu Yadav" << endl;
                cout << "Roll No: 2401730034" << endl;
                break;
            }
            case 2: {
                // Remove an item
                int id;
                cout << "\n--- Remove Item ---" << endl;
                cout << "Enter item ID to remove: ";
                cin >> id;
                my_store.removeItemRecord(id);
                cout << "Item removed successfully!" << endl;
                cout << "Name: Diwanshu Yadav" << endl;
                cout << "Roll No: 2401730034" << endl;
                break;
            }
            case 3: {
                // Update an item
                int id, quantity;
                double price;
                
                cout << "\n--- Update Item ---" << endl;
                cout << "Enter item ID to update: ";
                cin >> id;
                
                cout << "Enter new quantity: ";
                cin >> quantity;
                
                cout << "Enter new price: ";
                cin >> price;
                
                my_store.updateItem(id, quantity, price);
                cout << "Item updated successfully!" << endl;
                cout << "Name: Diwanshu Yadav" << endl;
                cout << "Roll No: 2401730034" << endl;
                break;
            }
            case 4: {
                // Search for an item
                int id;
                cout << "\n--- Search Item ---" << endl;
                cout << "Enter item ID to search: ";
                cin >> id;
                my_store.searchByItem(id);
                cout << "Name: Diwanshu Yadav" << endl;
                cout << "Roll No: 2401730034" << endl;
                break;
            }
            case 5:
                // Display all items
                cout << "\n--- Current Inventory ---" << endl;
                my_store.displayInventory();
                cout << "Name: Diwanshu Yadav" << endl;
                cout << "Roll No: 2401730034" << endl;
                break;
            case 6:
                // Demonstrate Price-Quantity Matrix
                my_store.managePriceQuantity();
                cout << "Name: Diwanshu Yadav" << endl;
                cout << "Roll No: 2401730034" << endl;
                break;
            case 7:
                // Demonstrate Sparse Storage
                my_store.optimizeSparseStorage();
                cout << "Name: Diwanshu Yadav" << endl;
                cout << "Roll No: 2401730034" << endl;
                break;
            case 8:
                cout << "Exiting... Thank you for using the Inventory Management System!" << endl;
                cout << "Name: Diwanshu Yadav" << endl;
                cout << "Roll No: 2401730034" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                cout << "Name: Diwanshu Yadav" << endl;
                cout << "Roll No: 2401730034" << endl;
        }
        
    } while (choice != 8);
    
    return 0;
}