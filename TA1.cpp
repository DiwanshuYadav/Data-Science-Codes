#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Define constants for the dimensions of our data array and sentinel value
const int NUM_CITIES = 5;
const int NUM_YEARS = 5;
const int START_YEAR = 2021;
const double SENTINEL_VALUE = -999.0; // Represents missing data

// Pre-defined list of cities. The index in this array corresponds to the column in the 2D array.
const string CITIES[NUM_CITIES] = {"Delhi", "Gurgaon", "Rewari", "Noida", "Pune"};

// The ADT for a single weather record (used conceptually for insert/delete)
struct WeatherRecord {
    int year;
    string city;
    double temperature;
};

class WeatherDataSystem {
private:
    // 2D array to store temperature data
    // Rows represent years, columns represent cities
    double temperatureData[NUM_YEARS][NUM_CITIES];

    // Helper to get the column index for a given city name
    int getCityIndex(string city) {
        for (int i = 0; i < NUM_CITIES; ++i) {
            if (CITIES[i] == city) {
                return i;
            }
        }
        return -1; // Return -1 if city is not found
    }

public:
    // Constructor
    WeatherDataSystem() {
        populateArray(); // Initialize array on creation
        cout << "Weather Data System Initialized." << endl;
    }

    // Initialize the array with a sentinel value to represent sparse data
    void populateArray() {
        for (int i = 0; i < NUM_YEARS; ++i) {
            for (int j = 0; j < NUM_CITIES; ++j) {
                temperatureData[i][j] = SENTINEL_VALUE;
            }
        }
    }

    // --- Core ADT Methods ---

    // Insert a new weather record into the system
    void insert(WeatherRecord data) {
        int yearIndex = data.year - START_YEAR;
        int cityIndex = getCityIndex(data.city);

        if (yearIndex >= 0 && yearIndex < NUM_YEARS && cityIndex != -1) {
            temperatureData[yearIndex][cityIndex] = data.temperature;
            cout << "Success: Inserted temperature " << data.temperature << " for " << data.city << " in " << data.year << "." << endl << endl;
        } else {
            cout << "Error: Invalid year or city for insertion." << endl << endl;
        }
    }
    
    // "Deletes" a record by resetting it to the sentinel value
    void remove(int year, string city) {
        int yearIndex = year - START_YEAR;
        int cityIndex = getCityIndex(city);

        if (yearIndex >= 0 && yearIndex < NUM_YEARS && cityIndex != -1) {
            temperatureData[yearIndex][cityIndex] = SENTINEL_VALUE;
            cout << "Success: Deleted data for " << city << " in " << year << "." << endl << endl;
        } else {
            cout << "Error: Invalid year or city for deletion." << endl << endl;
        }
    }

    // Retrieve temperature data for a specific city and year
    void retrieve(int year, string city) {
        int yearIndex = year - START_YEAR;
        int cityIndex = getCityIndex(city);

        if (yearIndex >= 0 && yearIndex < NUM_YEARS && cityIndex != -1) {
            double temp = temperatureData[yearIndex][cityIndex];
            if (temp == SENTINEL_VALUE) {
                cout << "Data for " << city << " in " << year << ": Not Available." << endl << endl;
            } else {
                cout << "Temperature for " << city << " in " << year << ": " << fixed << setprecision(2) << temp << " C" << endl << endl;
            }
        } else {
            cout << "Error: Cannot retrieve data for invalid year or city." << endl << endl;
        }
    }
    
    // Display the entire 2D array in a table format
    void displayAllData() {
        cout << "\n--- Complete Temperature Data Matrix ---" << endl;
        cout << "Matrix Structure: temperatureData[YEAR][CITY]" << endl;
        cout << "Rows = Years (" << NUM_YEARS << "), Columns = Cities (" << NUM_CITIES << ")" << endl << endl;
        
        // Header row with city names
        cout << setw(8) << "Year";
        for (int j = 0; j < NUM_CITIES; j++) {
            cout << setw(12) << CITIES[j];
        }
        cout << endl;
        cout << string(8 + NUM_CITIES * 12, '-') << endl;
        
        // Data rows
        for (int i = 0; i < NUM_YEARS; i++) {
            cout << setw(8) << (START_YEAR + i);
            for (int j = 0; j < NUM_CITIES; j++) {
                if (temperatureData[i][j] == SENTINEL_VALUE) {
                    cout << setw(12) << "---";
                } else {
                    cout << setw(12) << fixed << setprecision(2) << temperatureData[i][j];
                }
            }
            cout << endl;
        }
        cout << string(8 + NUM_CITIES * 12, '-') << endl << endl;
    }
    
    // --- Row/Column Major Access Demonstration ---

    // Access data using row-major logic
    void rowMajorAccess(int year, string city) {
        cout << "\n=== ROW-MAJOR ORDER DEMONSTRATION ===" << endl;
        int r = year - START_YEAR;
        int c = getCityIndex(city);

        if (r >= 0 && r < NUM_YEARS && c != -1) {
            cout << "\nConcept: In Row-Major order, elements are stored ROW by ROW in memory." << endl;
            cout << "Formula: Linear Index = (row * total_columns) + column" << endl;
            
            cout << "\n2D Array Structure: temperatureData[" << NUM_YEARS << "][" << NUM_CITIES << "]" << endl;
            cout << "Total Rows (Years): " << NUM_YEARS << endl;
            cout << "Total Columns (Cities): " << NUM_CITIES << endl;
            
            cout << "\nMemory Layout (Row-Major):" << endl;
            cout << "Row 0: [0,0] [0,1] [0,2] [0,3] [0,4]" << endl;
            cout << "Row 1: [1,0] [1,1] [1,2] [1,3] [1,4]" << endl;
            cout << "Row 2: [2,0] [2,1] [2,2] [2,3] [2,4]" << endl;
            cout << "Row 3: [3,0] [3,1] [3,2] [3,3] [3,4]" << endl;
            cout << "Row 4: [4,0] [4,1] [4,2] [4,3] [4,4]" << endl;
            
            cout << "\nAccessing: Year " << year << " (" << CITIES[c] << ")" << endl;
            cout << "2D Position: [" << r << "][" << c << "]" << endl;
            
            int index = (r * NUM_CITIES) + c;
            cout << "\nCalculation:" << endl;
            cout << "  Linear Index = (" << r << " * " << NUM_CITIES << ") + " << c << endl;
            cout << "  Linear Index = " << (r * NUM_CITIES) << " + " << c << endl;
            cout << "  Linear Index = " << index << endl;
            
            cout << "\nThis means the element is at position " << index << " in linear memory." << endl;
            
            double value = temperatureData[r][c];
            if (value == SENTINEL_VALUE) {
                cout << "Value: No data available" << endl;
            } else {
                cout << "Value: " << fixed << setprecision(2) << value << " C" << endl;
            }
            cout << "\n" << string(50, '=') << endl << endl;
        } else {
            cout << "Error: Invalid coordinates for access." << endl << endl;
        }
    }
    
    // Access data using column-major logic
    void columnMajorAccess(int year, string city) {
        cout << "\n=== COLUMN-MAJOR ORDER DEMONSTRATION ===" << endl;
        int r = year - START_YEAR;
        int c = getCityIndex(city);

        if (r >= 0 && r < NUM_YEARS && c != -1) {
            cout << "\nConcept: In Column-Major order, elements are stored COLUMN by COLUMN in memory." << endl;
            cout << "Formula: Linear Index = (column * total_rows) + row" << endl;
            
            cout << "\n2D Array Structure: temperatureData[" << NUM_YEARS << "][" << NUM_CITIES << "]" << endl;
            cout << "Total Rows (Years): " << NUM_YEARS << endl;
            cout << "Total Columns (Cities): " << NUM_CITIES << endl;
            
            cout << "\nMemory Layout (Column-Major):" << endl;
            cout << "Col 0: [0,0] [1,0] [2,0] [3,0] [4,0]" << endl;
            cout << "Col 1: [0,1] [1,1] [2,1] [3,1] [4,1]" << endl;
            cout << "Col 2: [0,2] [1,2] [2,2] [3,2] [4,2]" << endl;
            cout << "Col 3: [0,3] [1,3] [2,3] [3,3] [4,3]" << endl;
            cout << "Col 4: [0,4] [1,4] [2,4] [3,4] [4,4]" << endl;
            
            cout << "\nAccessing: Year " << year << " (" << CITIES[c] << ")" << endl;
            cout << "2D Position: [" << r << "][" << c << "]" << endl;
            
            int index = (c * NUM_YEARS) + r;
            cout << "\nCalculation:" << endl;
            cout << "  Linear Index = (" << c << " * " << NUM_YEARS << ") + " << r << endl;
            cout << "  Linear Index = " << (c * NUM_YEARS) << " + " << r << endl;
            cout << "  Linear Index = " << index << endl;
            
            cout << "\nThis means the element is at position " << index << " in linear memory." << endl;
            
            double value = temperatureData[r][c];
            if (value == SENTINEL_VALUE) {
                cout << "Value: No data available" << endl;
            } else {
                cout << "Value: " << fixed << setprecision(2) << value << " C" << endl;
            }
            
            cout << "\nKey Difference:" << endl;
            cout << "  Row-Major: Stores all columns of row 0, then row 1, etc." << endl;
            cout << "  Column-Major: Stores all rows of column 0, then column 1, etc." << endl;
            cout << "  (C/C++ uses Row-Major, Fortran/MATLAB use Column-Major)" << endl;
            cout << "\n" << string(50, '=') << endl << endl;
        } else {
            cout << "Error: Invalid coordinates for access." << endl << endl;
        }
    }
};

// Function to display the menu options
void displayMenu() {
    cout << "\n=== Weather Data System ===" << endl;
    cout << "1. Insert temperature data" << endl;
    cout << "2. Retrieve temperature data" << endl;
    cout << "3. Delete temperature data" << endl;
    cout << "4. Display complete data matrix" << endl;
    cout << "5. Demonstrate Row-Major Access" << endl;
    cout << "6. Demonstrate Column-Major Access" << endl;
    cout << "7. List all available cities" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice (1-8): ";
}

// Function to display available cities
void displayCities() {
    cout << "\n--- Available Cities ---" << endl;
    for (int i = 0; i < NUM_CITIES; i++) {
        cout << "- " << CITIES[i] << endl;
    }
    cout << "-----------------------" << endl;
}

// Main function with interactive menu
int main() {
    WeatherDataSystem wds;
    int choice;
    
    do {
        displayMenu();
        cin >> choice;
        
        // Clear input buffer
        while (cin.get() != '\n');
        
        switch(choice) {
            case 1: {
                // Insert temperature data
                int year;
                string city;
                double temp;
                
                cout << "\n--- Insert Temperature Data ---" << endl;
                
                cout << "Enter year (" << START_YEAR << " to " << (START_YEAR + NUM_YEARS - 1) << "): ";
                cin >> year;
                
                displayCities();
                cout << "Enter city name: ";
                getline(cin >> ws, city);
                
                cout << "Enter temperature (in Celsius): ";
                cin >> temp;
                
                wds.insert({year, city, temp});
                cout << "Name: Diwanshu Yadav" << endl;
                cout << "Roll No: 2401730034" << endl;
                break;
            }
            case 2: {
                // Retrieve temperature data
                int year;
                string city;
                
                cout << "\n--- Retrieve Temperature Data ---" << endl;
                cout << "Enter year (" << START_YEAR << " to " << (START_YEAR + NUM_YEARS - 1) << "): ";
                cin >> year;
                
                displayCities();
                cout << "Enter city name: ";
                getline(cin >> ws, city);
                
                wds.retrieve(year, city);
                cout << "Name: Diwanshu Yadav" << endl;
                cout << "Roll No: 2401730034" << endl;
                break;
            }
            case 3: {
                // Delete temperature data
                int year;
                string city;
                
                cout << "\n--- Delete Temperature Data ---" << endl;
                cout << "Enter year (" << START_YEAR << " to " << (START_YEAR + NUM_YEARS - 1) << "): ";
                cin >> year;
                
                displayCities();
                cout << "Enter city name: ";
                getline(cin >> ws, city);
                
                wds.remove(year, city);
                cout << "Name: Diwanshu Yadav" << endl;
                cout << "Roll No: 2401730034" << endl;
                break;
            }
            case 4:
                // Display complete data matrix
                wds.displayAllData();
                cout << "Name: Diwanshu Yadav" << endl;
                cout << "Roll No: 2401730034" << endl;
                break;
            case 5: {
                // Demonstrate Row-Major Access
                int year;
                string city;
                
                cout << "\n--- Row-Major Access ---" << endl;
                cout << "Enter year (" << START_YEAR << " to " << (START_YEAR + NUM_YEARS - 1) << "): ";
                cin >> year;
                
                displayCities();
                cout << "Enter city name: ";
                getline(cin >> ws, city);
                
                wds.rowMajorAccess(year, city);
                cout << "Name: Diwanshu Yadav" << endl;
                cout << "Roll No: 2401730034" << endl;
                break;
            }
            case 6: {
                // Demonstrate Column-Major Access
                int year;
                string city;
                
                cout << "\n--- Column-Major Access ---" << endl;
                cout << "Enter year (" << START_YEAR << " to " << (START_YEAR + NUM_YEARS - 1) << "): ";
                cin >> year;
                
                displayCities();
                cout << "Enter city name: ";
                getline(cin >> ws, city);
                
                wds.columnMajorAccess(year, city);
                cout << "Name: Diwanshu Yadav" << endl;
                cout << "Roll No: 2401730034" << endl;
                break;
            }
            case 7:
                displayCities();
                cout << "Name: Diwanshu Yadav" << endl;
                cout << "Roll No: 2401730034" << endl;
                break;
            case 8:
                cout << "Exiting... Thank you for using the Weather Data System!" << endl;
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
