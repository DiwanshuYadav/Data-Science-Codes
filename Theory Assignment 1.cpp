#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// Weather Record ADT Implementation
class WeatherRecord {
private:
    string date;
    string city;
    double temperature;

public:
    // Constructor
    WeatherRecord(string d = "", string c = "", double temp = -999.0) 
        : date(d), city(c), temperature(temp) {}

    // Getter methods
    string getDate() const { return date; }
    string getCity() const { return city; }
    double getTemperature() const { return temperature; }

    // Setter methods
    void setDate(string d) { date = d; }
    void setCity(string c) { city = c; }
    void setTemperature(double temp) { temperature = temp; }

    // Check if record is valid (not missing data)
    bool isValid() const {
        return temperature != -999.0;
    }

    // Display method
    void display() const {
        cout << "Date: " << date << ", City: " << city 
             << ", Temperature: " << (isValid() ? to_string(temperature) + "°C" : "Missing Data") << endl;
    }
};

// Sparse Matrix Entry for handling missing data efficiently
struct SparseEntry {
    int row, col;
    double value;

    SparseEntry(int r, int c, double v) : row(r), col(c), value(v) {}
};

// Main Data Storage Class
class WeatherDataStorage {
private:
    static const int YEARS = 5;    // 2021-2025
    static const int CITIES = 5;   // Delhi, Gurgaon, Mumbai, Jaipur, Rewari
    static const double MISSING_VALUE = -999.0;

    // 2D array for complete storage
    double temperatureData[YEARS][CITIES];

    // City and year mappings
    vector<string> cityNames = {"Delhi", "Gurgaon", "Mumbai", "Jaipur", "Rewari"};
    vector<int> years = {2021, 2022, 2023, 2024, 2025};

    // Sparse matrix representation
    vector<SparseEntry> sparseMatrix;

    // Maps for quick lookups
    map<string, int> cityIndex;
    map<int, int> yearIndex;

    // Random number generator for realistic data
    mutable mt19937 rng;

public:
    WeatherDataStorage() : rng(chrono::steady_clock::now().time_since_epoch().count()) {
        // Initialize mappings
        for(int i = 0; i < CITIES; i++) {
            cityIndex[cityNames[i]] = i;
        }
        for(int i = 0; i < YEARS; i++) {
            yearIndex[years[i]] = i;
        }

        // Initialize 2D array with missing values
        for(int i = 0; i < YEARS; i++) {
            for(int j = 0; j < CITIES; j++) {
                temperatureData[i][j] = MISSING_VALUE;
            }
        }
    }

    // Generate realistic temperature data based on city climate
    double generateRealisticTemperature(const string& city) {
        uniform_real_distribution<double> dist;

        // Define realistic temperature ranges for each city
        if(city == "Delhi") {
            dist = uniform_real_distribution<double>(-2.0, 48.0);
        } else if(city == "Gurgaon") {
            dist = uniform_real_distribution<double>(-1.0, 47.0);
        } else if(city == "Mumbai") {
            dist = uniform_real_distribution<double>(16.0, 40.0);
        } else if(city == "Jaipur") {
            dist = uniform_real_distribution<double>(2.0, 46.0);
        } else if(city == "Rewari") {
            dist = uniform_real_distribution<double>(0.0, 45.0);
        } else {
            dist = uniform_real_distribution<double>(10.0, 40.0); // default
        }

        return round(dist(rng) * 10.0) / 10.0; // Round to 1 decimal place
    }

    // Populate the 2D array with realistic data (30% sparse)
    void populateArray() {
        uniform_real_distribution<double> sparseDist(0.0, 1.0);

        cout << "\n=== Populating Weather Data (30% sparse) ===\n";

        for(int year = 0; year < YEARS; year++) {
            for(int city = 0; city < CITIES; city++) {
                // 30% chance of missing data
                if(sparseDist(rng) > 0.3) {
                    double temp = generateRealisticTemperature(cityNames[city]);
                    temperatureData[year][city] = temp;

                    // Add to sparse matrix
                    sparseMatrix.push_back(SparseEntry(year, city, temp));
                }
            }
        }

        cout << "Data populated successfully!\n";
        cout << "Total entries: " << YEARS * CITIES << "\n";
        cout << "Valid entries: " << sparseMatrix.size() << "\n";
        cout << "Missing entries: " << (YEARS * CITIES - sparseMatrix.size()) << "\n";
        cout << "Sparsity: " << fixed << setprecision(1) 
             << (100.0 * (YEARS * CITIES - sparseMatrix.size()) / (YEARS * CITIES)) << "%\n";
    }

    // Insert a new weather record
    bool insert(const WeatherRecord& record) {
        string city = record.getCity();
        string dateStr = record.getDate();

        // Extract year from date (assuming DD-MM-YYYY format)
        int year = stoi(dateStr.substr(6, 4));

        if(cityIndex.find(city) == cityIndex.end() || yearIndex.find(year) == yearIndex.end()) {
            cout << "Error: Invalid city or year for insertion\n";
            return false;
        }

        int yearIdx = yearIndex[year];
        int cityIdx = cityIndex[city];

        // Update 2D array
        temperatureData[yearIdx][cityIdx] = record.getTemperature();

        // Update sparse matrix
        auto it = find_if(sparseMatrix.begin(), sparseMatrix.end(), [yearIdx, cityIdx](const SparseEntry& entry) {
            return entry.row == yearIdx && entry.col == cityIdx;
        });

        if(it != sparseMatrix.end()) {
            it->value = record.getTemperature();
        } else {
            sparseMatrix.push_back(SparseEntry(yearIdx, cityIdx, record.getTemperature()));
        }

        return true;
    }

    // Delete a weather record
    bool deleteRecord(const string& city, int year) {
        if(cityIndex.find(city) == cityIndex.end() || yearIndex.find(year) == yearIndex.end()) {
            return false;
        }

        int yearIdx = yearIndex[year];
        int cityIdx = cityIndex[city];

        // Remove from 2D array
        temperatureData[yearIdx][cityIdx] = MISSING_VALUE;

        // Remove from sparse matrix
        sparseMatrix.erase(
            remove_if(sparseMatrix.begin(), sparseMatrix.end(),[yearIdx, cityIdx](const SparseEntry& entry) {
                return entry.row == yearIdx && entry.col == cityIdx;
            }),
            sparseMatrix.end()
        );

        return true;
    }

    // Retrieve temperature data for a specific city and year
    double retrieve(const string& city, int year) {
        if(cityIndex.find(city) == cityIndex.end() || yearIndex.find(year) == yearIndex.end()) {
            return MISSING_VALUE;
        }

        int yearIdx = yearIndex[year];
        int cityIdx = cityIndex[city];

        return temperatureData[yearIdx][cityIdx];
    }

    // Row-major access implementation
    void rowMajorAccess() {
        cout << "\n=== Row-Major Access (Year-wise) ===\n";
        auto start = high_resolution_clock::now();

        for(int year = 0; year < YEARS; year++) {
            cout << "Year " << years[year] << ": ";
            for(int city = 0; city < CITIES; city++) {
                if(temperatureData[year][city] != MISSING_VALUE) {
                    cout << cityNames[city] << "(" << temperatureData[year][city] << "°C) ";
                }
            }
            cout << "\n";
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "Row-major access time: " << duration.count() << " microseconds\n";
    }

    // Column-major access implementation
    void columnMajorAccess() {
        cout << "\n=== Column-Major Access (City-wise) ===\n";
        auto start = high_resolution_clock::now();

        for(int city = 0; city < CITIES; city++) {
            cout << cityNames[city] << ": ";
            for(int year = 0; year < YEARS; year++) {
                if(temperatureData[year][city] != MISSING_VALUE) {
                    cout << years[year] << "(" << temperatureData[year][city] << "°C) ";
                }
            }
            cout << "\n";
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "Column-major access time: " << duration.count() << " microseconds\n";
    }

    // Handle sparse data using sparse matrix representation
    void handleSparseData() {
        cout << "\n=== Sparse Data Handling ===\n";
        cout << "Using Coordinate List (COO) format:\n";
        cout << "Format: (Year_Index, City_Index, Temperature)\n";

        for(const auto& entry : sparseMatrix) {
            cout << "(" << entry.row << ", " << entry.col << ", "  << entry.value << "°C) -> " << years[entry.row] << ", " << cityNames[entry.col] << "\n";
        }

        cout << "\nSparse matrix efficiency:\n";
        cout << "Full matrix storage: " << YEARS * CITIES * sizeof(double) << " bytes\n";
        cout << "Sparse matrix storage: " << sparseMatrix.size() * sizeof(SparseEntry) << " bytes\n";
        cout << "Memory savings: " << fixed << setprecision(1)
             << (100.0 * (1.0 - (sparseMatrix.size() * sizeof(SparseEntry)) 
                               / (YEARS * CITIES * sizeof(double)))) << "%\n";
    }

    // Analyze and document time and space complexity
    void analyzeComplexity() {
        cout << "\n=== Complexity Analysis ===\n";
        cout << "\n1. INSERT Operation:\n";
        cout << "   Time Complexity: O(1) for 2D array + O(n) for sparse matrix update\n";
        cout << "   Space Complexity: O(1) additional space\n";

        cout << "\n2. DELETE Operation:\n";
        cout << "   Time Complexity: O(1) for 2D array + O(n) for sparse matrix removal\n";
        cout << "   Space Complexity: O(1) additional space\n";

        cout << "\n3. RETRIEVE Operation:\n";
        cout << "   Time Complexity: O(1) - direct array access\n";
        cout << "   Space Complexity: O(1) additional space\n";

        cout << "\n4. ROW-MAJOR Access:\n";
        cout << "   Time Complexity: O(m*n) where m=years, n=cities\n";
        cout << "   Space Complexity: O(1) additional space\n";
        cout << "   Cache Performance: Excellent (sequential memory access)\n";

        cout << "\n5. COLUMN-MAJOR Access:\n";
        cout << "   Time Complexity: O(m*n) where m=years, n=cities\n";
        cout << "   Space Complexity: O(1) additional space\n";
        cout << "   Cache Performance: Poor (non-sequential memory access)\n";

        cout << "\n6. SPARSE Matrix Storage:\n";
        cout << "   Time Complexity: O(k) for operations, where k = non-zero elements\n";
        cout << "   Space Complexity: O(k) instead of O(m*n)\n";
        cout << "   Memory Efficiency: High for sparse data (>50% missing)\n";
    }

    // Display complete data overview
    void displayDataOverview() {
        cout << "\n=== Complete Weather Data Overview ===\n";
        cout << setw(10) << "Year";
        for(const string& city : cityNames) {
            cout << setw(12) << city;
        }
        cout << "\n" << string(70, '-') << "\n";

        for(int year = 0; year < YEARS; year++) {
            cout << setw(10) << years[year];
            for(int city = 0; city < CITIES; city++) {
                if(temperatureData[year][city] != MISSING_VALUE) {
                    cout << setw(12) << fixed << setprecision(1) << temperatureData[year][city];
                } else {
                    cout << setw(12) << "Missing";
                }
            }
            cout << "\n";
        }
    }

    // Performance comparison between access methods
    void compareAccessMethods() {
        cout << "\n=== Performance Comparison ===\n";

        // Row-major timing
        auto start = high_resolution_clock::now();
        int rowCount = 0;
        for(int year = 0; year < YEARS; year++) {
            for(int city = 0; city < CITIES; city++) {
                if(temperatureData[year][city] != MISSING_VALUE) {
                    rowCount++;
                }
            }
        }
        auto end = high_resolution_clock::now();
        auto rowTime = duration_cast<nanoseconds>(end - start).count();

        // Column-major timing
        start = high_resolution_clock::now();
        int colCount = 0;
        for(int city = 0; city < CITIES; city++) {
            for(int year = 0; year < YEARS; year++) {
                if(temperatureData[year][city] != MISSING_VALUE) {
                    colCount++;
                }
            }
        }
        end = high_resolution_clock::now();
        auto colTime = duration_cast<nanoseconds>(end - start).count();

        cout << "Row-major traversal time: " << rowTime << " nanoseconds\n";
        cout << "Column-major traversal time: " << colTime << " nanoseconds\n";
        cout << "Performance difference: " << 
                (colTime > rowTime ? "Row-major is faster" : "Column-major is faster") << "\n";
        cout << "Cache efficiency factor: " << fixed << setprecision(2) 
             << (double)max(rowTime, colTime) / min(rowTime, colTime) << "x\n";
    }
};

// Demonstration and testing function
int main() {
    cout << "=== Weather Data Storage System ===\n";
    cout << "Developed for CSE Data Structures Assignment\n";
    cout << "Years: 2021-2025, Cities: Delhi, Gurgaon, Mumbai, Jaipur, Rewari\n";

    WeatherDataStorage weatherSystem;

    // Step 1: Populate with realistic data
    weatherSystem.populateArray();

    // Step 2: Display data overview
    weatherSystem.displayDataOverview();

    // Step 3: Demonstrate ADT operations
    cout << "\n=== Testing WeatherRecord ADT Operations ===\n";

    // Insert operation
    WeatherRecord newRecord("15-03-2023", "Delhi", 25.5);
    cout << "Inserting new record: ";
    newRecord.display();
    weatherSystem.insert(newRecord);

    // Retrieve operation
    double temp = weatherSystem.retrieve("Delhi", 2023);
    cout << "Retrieved temperature for Delhi 2023: " << (temp != -999.0 ? to_string(temp) + "°C" : "Missing Data") << "\n";

    // Delete operation
    cout << "Deleting record for Gurgaon 2022...\n";
    weatherSystem.deleteRecord("Gurgaon", 2022);

    // Step 4: Compare access methods
    weatherSystem.rowMajorAccess();
    weatherSystem.columnMajorAccess();
    weatherSystem.compareAccessMethods();

    // Step 5: Sparse data handling
    weatherSystem.handleSparseData();

    // Step 6: Complexity analysis
    weatherSystem.analyzeComplexity();

    cout << "\n=== Assignment Implementation Complete ===\n";
    cout << "All ADT methods, sparse handling, and complexity analysis implemented.\n";

    return 0;
}