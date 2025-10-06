#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <random>
#include <cctype>

using namespace std;
using namespace std::chrono;

// Inventory Item ADT Implementation
class InventoryItem {
private:
    int itemID;
    string itemName;
    int quantity;
    float price;

public:
    // Constructor
    InventoryItem(int id = 0, string name = "", int qty = 0, float p = 0.0)
        : itemID(id), itemName(name), quantity(qty), price(p) {}
    
    // Getter methods
    int getItemID() const { return itemID; }
    string getItemName() const { return itemName; }
    int getQuantity() const { return quantity; }
    float getPrice() const { return price; }
    
    // Setter methods
    void setItemID(int id) { itemID = id; }
    void setItemName(string name) { itemName = name; }
    void setQuantity(int qty) { quantity = qty; }
    void setPrice(float p) { price = p; }
    
    // Check if item is low stock
    bool isLowStock() const {
        return quantity < 10;
    }
    
    // Display method
    void display() const {
        cout << "ID: " << itemID << ", Name: " << itemName << ", Quantity: " << quantity << ", Price: ₹" << fixed << setprecision(2) << price;
        if(isLowStock()) cout << " [LOW STOCK]";
        cout << endl;
    }
};

// Sparse Entry for rarely restocked products
struct SparseEntry {
    int itemIndex;
    int attribute; // 0=price, 1=quantity
    float value;
    
    SparseEntry(int idx, int attr, float val) : itemIndex(idx), attribute(attr), value(val) {}
};

// Main Inventory Management System
class InventoryManagementSystem {
private:
    static const int MAX_ITEMS = 10;
    static const int ATTRIBUTES = 3; // Price, Quantity, Category
    static const float MISSING_VALUE = -1.0;
    
    // Single dimensional array for item storage
    InventoryItem itemArray[MAX_ITEMS];
    
    // Multi-dimensional array: Rows=Items, Columns=(Price, Quantity, Category)
    float priceQuantityTable[MAX_ITEMS][ATTRIBUTES];
    
    // Sparse matrix for rarely restocked items
    vector<SparseEntry> sparseMatrix;
    
    // Item tracking
    int itemCount;
    map<string, int> nameToIndex; // For case-insensitive search
    
    // Realistic Indian grocery items
    vector<string> groceryItems = {
        "Basmati Rice", "Toor Dal", "Sunflower Oil", "Amul Milk", 
        "Britannia Bread", "Maggi Noodles", "Tata Tea", "Parle-G Biscuits",
        "Organic Honey", "Premium Ghee"
    };
    
    vector<float> basePrices = {
        120.0, 85.0, 140.0, 25.0, 30.0, 14.0, 180.0, 20.0, 450.0, 520.0
    };

public:
    InventoryManagementSystem() : itemCount(0) {
        // Initialize arrays
        for(int i = 0; i < MAX_ITEMS; i++) {
            for(int j = 0; j < ATTRIBUTES; j++) {
                priceQuantityTable[i][j] = MISSING_VALUE;
            }
        }
    }
    
    // Convert string to lowercase for case-insensitive comparison
    string toLowerCase(string str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }
    
    // Add item record to the system
    bool addItemRecord() {
        if(itemCount >= MAX_ITEMS) {
            cout << "Error: Inventory is full!\n";
            return false;
        }
        
        int id = itemCount + 1;
        string name = groceryItems[itemCount];
        float price = basePrices[itemCount];
        
        // Generate random quantity (some items will be sparse - 25%)
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> qtyDist(0, 50);
        uniform_real_distribution<> sparseDist(0.0, 1.0);
        
        int quantity;
        bool isSparse = sparseDist(gen) < 0.25; // 25% sparse
        
        if(isSparse) {
            quantity = 0; // Rarely restocked
        } else {
            quantity = qtyDist(gen);
        }
        
        // Create and store item
        itemArray[itemCount] = InventoryItem(id, name, quantity, price);
        
        // Update multi-dimensional array
        priceQuantityTable[itemCount][0] = price;
        priceQuantityTable[itemCount][1] = quantity;
        priceQuantityTable[itemCount][2] = itemCount % 3; // Category index
        
        // Add to sparse matrix if rarely restocked
        if(isSparse) {
            sparseMatrix.push_back(SparseEntry(itemCount, 0, price));
            sparseMatrix.push_back(SparseEntry(itemCount, 1, 0)); // quantity = 0
        }
        
        // Update name mapping for search
        nameToIndex[toLowerCase(name)] = itemCount;
        
        itemCount++;
        return true;
    }
    
    // Remove item record from array
    bool removeItemRecord(int itemID) {
        int index = -1;
        for(int i = 0; i < itemCount; i++) {
            if(itemArray[i].getItemID() == itemID) {
                index = i;
                break;
            }
        }
        
        if(index == -1) return false;
        
        // Remove from name mapping
        nameToIndex.erase(toLowerCase(itemArray[index].getItemName()));
        
        // Shift array elements
        for(int i = index; i < itemCount - 1; i++) {
            itemArray[i] = itemArray[i + 1];
            for(int j = 0; j < ATTRIBUTES; j++) {
                priceQuantityTable[i][j] = priceQuantityTable[i + 1][j];
            }
        }
        
        // Remove from sparse matrix
        sparseMatrix.erase(
            remove_if(sparseMatrix.begin(), sparseMatrix.end(), [index](const SparseEntry& entry) {
                        return entry.itemIndex == index;
                    }),
            sparseMatrix.end()
        );
        
        itemCount--;
        return true;
    }
    
    // Search by item ID or name (case-insensitive)
    int searchByItem(const string& searchTerm) {
        // Try to parse as ID first
        try {
            int id = stoi(searchTerm);
            for(int i = 0; i < itemCount; i++) {
                if(itemArray[i].getItemID() == id) {
                    return i;
                }
            }
        } catch(...) {
            // Not a number, search by name
        }
        
        // Search by name (case-insensitive)
        string lowerTerm = toLowerCase(searchTerm);
        auto it = nameToIndex.find(lowerTerm);
        if(it != nameToIndex.end()) {
            return it->second;
        }
        
        return -1; // Not found
    }
    
    // Populate initial inventory
    void populateInventory() {
        cout << "\n=== Populating Grocery Store Inventory ===\n";
        
        for(int i = 0; i < MAX_ITEMS; i++) {
            addItemRecord();
        }
        
        cout << "Inventory populated with " << itemCount << " items\n";
        cout << "Sparse items (rarely restocked): " << sparseMatrix.size() / 2 << "\n";
    }
    
    // Row-major ordering for price-quantity management
    void managePriceQuantityRowMajor() {
        cout << "\n=== Row-Major Access (Item-wise) ===\n";
        auto start = high_resolution_clock::now();
        
        cout << setw(4) << "ID" << setw(20) << "Item Name" << setw(10) << "Price" << setw(10) << "Quantity" << setw(10) << "Category\n";
        cout << string(60, '-') << "\n";
        
        for(int item = 0; item < itemCount; item++) {
            cout << setw(4) << item + 1;
            cout << setw(20) << itemArray[item].getItemName().substr(0, 18);
            for(int attr = 0; attr < ATTRIBUTES; attr++) {
                cout << setw(10) << fixed << setprecision(2) << priceQuantityTable[item][attr];
            }
            cout << "\n";
        }
        
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "Row-major access time: " << duration.count() << " microseconds\n";
    }
    
    // Column-major ordering for attribute analysis
    void managePriceQuantityColumnMajor() {
        cout << "\n=== Column-Major Access (Attribute-wise) ===\n";
        auto start = high_resolution_clock::now();
        
        vector<string> attrNames = {"Price", "Quantity", "Category"};
        
        for(int attr = 0; attr < ATTRIBUTES; attr++) {
            cout << "\n" << attrNames[attr] << " Analysis:\n";
            cout << setw(4) << "ID" << setw(20) << "Item Name" << setw(12) << attrNames[attr] << "\n";
            cout << string(36, '-') << "\n";
            
            for(int item = 0; item < itemCount; item++) {
                cout << setw(4) << item + 1;
                cout << setw(20) << itemArray[item].getItemName().substr(0, 18);
                cout << setw(12) << fixed << setprecision(2) << priceQuantityTable[item][attr];
                cout << "\n";
            }
        }
        
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "Column-major access time: " << duration.count() << " microseconds\n";
    }
    
    // Optimize sparse storage for rarely restocked products
    void optimizeSparseStorage() {
        cout << "\n=== Sparse Storage Optimization ===\n";
        cout << "Rarely restocked products (Coordinate List format):\n";
        cout << "Format: (Item_Index, Attribute, Value)\n";
        
        for(const auto& entry : sparseMatrix) {
            string attrName = (entry.attribute == 0) ? "Price" : "Quantity";
            cout << "(" << entry.itemIndex << ", " << attrName << ", " << entry.value << ") -> " << itemArray[entry.itemIndex].getItemName() << "\n";
        }
        
        cout << "\nStorage efficiency:\n";
        cout << "Full table storage: " << MAX_ITEMS * ATTRIBUTES * sizeof(float) << " bytes\n";
        cout << "Sparse storage: " << sparseMatrix.size() * sizeof(SparseEntry) << " bytes\n";
        cout << "Memory savings: " << fixed << setprecision(1)
             << (100.0 * (1.0 - (sparseMatrix.size() * sizeof(SparseEntry)) 
                               / (MAX_ITEMS * ATTRIBUTES * sizeof(float)))) << "%\n";
    }
    
    // Display complete inventory
    void displayInventory() {
        cout << "\n=== Complete Grocery Store Inventory ===\n";
        cout << setw(4) << "ID" << setw(20) << "Item Name" << setw(10) << "Price" << setw(10) << "Stock" << setw(15) << "Status\n";
        cout << string(70, '-') << "\n";
        
        for(int i = 0; i < itemCount; i++) {
            cout << setw(4) << itemArray[i].getItemID();
            cout << setw(20) << itemArray[i].getItemName().substr(0, 18);
            cout << setw(10) << "₹" << fixed << setprecision(2) << itemArray[i].getPrice();
            cout << setw(9) << itemArray[i].getQuantity();
            cout << setw(15) << (itemArray[i].isLowStock() ? "LOW STOCK" : "In Stock");
            cout << "\n";
        }
    }
    
    // Generate low stock alerts
    void generateLowStockAlerts() {
        cout << "\n=== Low Stock Alerts ===\n";
        bool hasLowStock = false;
        
        for(int i = 0; i < itemCount; i++) {
            if(itemArray[i].isLowStock()) {
                cout << "⚠️  " << itemArray[i].getItemName() << " (ID: " << itemArray[i].getItemID() << ") - Only " << itemArray[i].getQuantity() << " units left!\n";
                hasLowStock = true;
            }
        }
        
        if(!hasLowStock) {
            cout << "✅ All items are well stocked!\n";
        }
    }
    
    // Complexity analysis for all functions
    void analyzeComplexity() {
        cout << "\n=== Time & Space Complexity Analysis ===\n";
        
        cout << "\n1. INSERT Operation (addItemRecord):\n";
        cout << "   Time Complexity: O(1) - Direct array insertion\n";
        cout << "   Space Complexity: O(1) - Fixed space allocation\n";
        
        cout << "\n2. DELETE Operation (removeItemRecord):\n";
        cout << "   Time Complexity: O(n) - Linear search + array shifting\n";
        cout << "   Space Complexity: O(1) - In-place operation\n";
        
        cout << "\n3. SEARCH Operation (searchByItem):\n";
        cout << "   Time Complexity: O(1) average for hash map, O(n) worst case\n";
        cout << "   Space Complexity: O(n) - Additional hash map storage\n";
        
        cout << "\n4. ROW-MAJOR Access:\n";
        cout << "   Time Complexity: O(n*m) where n=items, m=attributes\n";
        cout << "   Space Complexity: O(1) - No additional space\n";
        cout << "   Cache Performance: Excellent (sequential access)\n";
        
        cout << "\n5. COLUMN-MAJOR Access:\n";
        cout << "   Time Complexity: O(n*m) where n=items, m=attributes\n";
        cout << "   Space Complexity: O(1) - No additional space\n";
        cout << "   Cache Performance: Poor (stride access pattern)\n";
        
        cout << "\n6. SPARSE Matrix Storage:\n";
        cout << "   Time Complexity: O(k) for operations, k=sparse entries\n";
        cout << "   Space Complexity: O(k) instead of O(n*m)\n";
        cout << "   Memory Efficiency: High for sparse data (>20% missing)\n";
    }
    
    // Performance comparison between access methods
    void compareAccessMethods() {
        cout << "\n=== Access Method Performance Comparison ===\n";
        
        // Row-major timing
        auto start = high_resolution_clock::now();
        int rowOperations = 0;
        for(int item = 0; item < itemCount; item++) {
            for(int attr = 0; attr < ATTRIBUTES; attr++) {
                volatile float temp = priceQuantityTable[item][attr];
                rowOperations++;
            }
        }
        auto end = high_resolution_clock::now();
        auto rowTime = duration_cast<nanoseconds>(end - start).count();
        
        // Column-major timing
        start = high_resolution_clock::now();
        int colOperations = 0;
        for(int attr = 0; attr < ATTRIBUTES; attr++) {
            for(int item = 0; item < itemCount; item++) {
                volatile float temp = priceQuantityTable[item][attr];
                colOperations++;
            }
        }
        end = high_resolution_clock::now();
        auto colTime = duration_cast<nanoseconds>(end - start).count();
        
        cout << "Row-major access time: " << rowTime << " nanoseconds\n";
        cout << "Column-major access time: " << colTime << " nanoseconds\n";
        cout << "Performance difference: " << 
                (rowTime < colTime ? "Row-major is faster" : "Column-major is faster") << "\n";
        cout << "Cache efficiency ratio: " << fixed << setprecision(2) << (double)max(rowTime, colTime) / min(rowTime, colTime) << "x\n";
    }
    
    // Test insert operation
    void testInsertOperation(const InventoryItem& item) {
        cout << "\nTesting INSERT operation:\n";
        auto start = high_resolution_clock::now();
        
        if(itemCount < MAX_ITEMS) {
            itemArray[itemCount] = item;
            priceQuantityTable[itemCount][0] = item.getPrice();
            priceQuantityTable[itemCount][1] = item.getQuantity();
            priceQuantityTable[itemCount][2] = itemCount % 3;
            nameToIndex[toLowerCase(item.getItemName())] = itemCount;
            itemCount++;
            cout << "✅ Item inserted successfully\n";
        } else {
            cout << "❌ Inventory full\n";
        }
        
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "Insert operation time: " << duration.count() << " microseconds\n";
    }
    
    // Test delete operation
    void testDeleteOperation(int itemID) {
        cout << "\nTesting DELETE operation for ID " << itemID << ":\n";
        auto start = high_resolution_clock::now();
        
        bool success = removeItemRecord(itemID);
        
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        
        cout << (success ? "✅ Item deleted successfully" : "❌ Item not found") << "\n";
        cout << "Delete operation time: " << duration.count() << " microseconds\n";
    }
    
    // Test search operation
    void testSearchOperation(const string& searchTerm) {
        cout << "\nTesting SEARCH operation for '" << searchTerm << "':\n";
        auto start = high_resolution_clock::now();
        
        int index = searchByItem(searchTerm);
        
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        
        if(index != -1) {
            cout << "✅ Item found: ";
            itemArray[index].display();
        } else {
            cout << "❌ Item not found\n";
        }
        cout << "Search operation time: " << duration.count() << " microseconds\n";
    }
};

// Main demonstration function
int main() {
    cout << "=== Grocery Store Inventory Management System ===\n";
    cout << "Developed for CSE Data Structures Lab Assignment\n";
    cout << "Managing 10 Indian grocery items with 25% sparse data\n";
    
    InventoryManagementSystem inventory;
    
    // Step 1: Populate inventory
    inventory.populateInventory();
    
    // Step 2: Display complete inventory
    inventory.displayInventory();
    
    // Step 3: Test ADT operations
    cout << "\n=== Testing Inventory Item ADT Operations ===\n";
    
    // Test insert
    InventoryItem newItem(11, "Bournvita", 25, 280.0);
    inventory.testInsertOperation(newItem);
    
    // Test search by name (case-insensitive)
    inventory.testSearchOperation("basmati rice");
    inventory.testSearchOperation("TOOR DAL");
    inventory.testSearchOperation("5");
    
    // Test delete
    inventory.testDeleteOperation(3);
    
    // Step 4: Demonstrate array access methods
    inventory.managePriceQuantityRowMajor();
    inventory.managePriceQuantityColumnMajor();
    inventory.compareAccessMethods();
    
    // Step 5: Show sparse storage optimization
    inventory.optimizeSparseStorage();
    
    // Step 6: Generate reports
    inventory.generateLowStockAlerts();
    
    // Step 7: Complexity analysis
    inventory.analyzeComplexity();
    
    cout << "\n=== Lab Assignment Implementation Complete ===\n";
    cout << "All array operations, sparse handling, and complexity analysis implemented.\n";
    
    return 0;
}
