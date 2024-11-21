#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>  // For std::setw, std::setprecision

using namespace std;

// Sequential search
// Searches the vector for the key using a linear scan
// numCmp counts the number of comparisons
int seq_search(vector<int> &keys, int key, int &numCmp) {
    for(int i = 0; i < keys.size(); ++i){
        ++numCmp; // Comparison increment
        if (keys[i]==key){
            return i; // If the key is found, return the index
        }
    }
    return -1;
}

// Sequential search with start and stop range
// Searches within a specified range of the vector for the key
int seq_search(vector<int> &keys, int key, int start, int stop, int &numCmp) {
    for(int i = start; i < stop; ++i){
        ++numCmp; // Comparison increment
        if (keys[i]==key){
            return i; // If the key is found, return the index
        }
    }
    return -1; // If the key is not found, return -1
}

// Binary search
// Searches the sorted vector using binary search algorithm
int bin_search(vector<int> &keys, int key, int &numCmp) {
    int under, over, mid;
    under = 0; // Start of range
    over = keys.size()-1; // End of range
    while(under <= over){
        mid = (under + over)/2; // Find the midpoint of the range
        ++numCmp; // Comp Increment
        if(keys[mid]==key){ // If the key is found, return the index
            return mid;
        }
        if(keys[mid]<key){ // If the key is larger, search the right half
            under = mid + 1;
        } else { // If the key is smaller, search the left half
            over = mid - 1;
        } 
    }
    return -1; // If the key is not found, return -1
}

// Enhanced binary search: switches to sequential search if remaining range is < 15
// Optimizes binary search by switching to sequential search if the range is small
int bin2_search(vector<int> &keys, int key, int &numCmp) {
    // Same as above
    int under, over, mid;
    under = 0;
    over = keys.size()-1;
    while(under <= over){
        // If the range is small enough, switch to sequential search
        if((over-under)+1<15){
            return seq_search(keys, key, under, over, numCmp);
        }
        mid = (under + over)/2;
        ++numCmp;
        if(keys[mid]==key){
            return mid;
        }
        if(keys[mid]<key){
            under = mid + 1;
        } else {
            over = mid - 1;
        }
    }
    return -1;
}

// Test the search algorithms
int main() {
    // Initialize random seed
    srand(time(NULL));

    // Create a vector of 100,000 integers
    std::vector<int> vec(100000);
    for (int i = 0; i < 100000; ++i) {
        int iRand = rand() % 10000000; // Generate a random number
        vec[i] = iRand; // Put it in the vector
    }
 
    // Sort the vector using STL sort
    sort(vec.begin(), vec.end());
    
    // Generate 50 random numbers from the data (guaranteed to be in the array)
    vector<int> intsInVec(50);
    for(int i = 0; i < 50; ++i){
        int num = rand() % vec.size(); // Random index
        intsInVec[i]=vec[num]; // Add the number at that index to the list
    }

    // Generate 50 random numbers (may or may not be in the array)
    vector<int> intsMaybeVec(50);
    for(int i = 0; i < 50; ++i){
        int num = rand() % 100001; // Generate random numbers
        intsMaybeVec[i]=vec[num]; // Add to the list
    }

    // Test each search algorithm, output results
    // Table header
    cout << "Results for numbers definitely in the array:" << endl;
    cout << setw(10) << "Search"
         << setw(10) << "Found" 
         << setw(15) << "Seq.search" 
         << setw(15) << "Bin Search" 
         << setw(20) << "Enhanced Search" 
         << endl;

    cout << setw(10) << "------"
         << setw(10) << "-----" 
         << setw(15) << "---------" 
         << setw(15) << "----------" 
         << setw(20) << "---------------" 
         << endl;
    
    // Perform search tests for numbers that are guaranteed to be in the array
    for (int key : intsInVec) {
        int seqComps = 0;
        int binComps = 0;
        int enhanceComps = 0;
        int seqFunc = seq_search(vec, key, seqComps);
        bin_search(vec, key, binComps);
        bin2_search(vec, key, enhanceComps);
        cout << setw(10) << key
              << setw(10) << (seqFunc != -1 ? seqFunc : -1)
              << setw(15) << seqComps
              << setw(15) << binComps
              << setw(20) << enhanceComps
              << endl;
    }

    cout << endl;

    // Display the results for numbers that may or may not be in the array
    cout << "Results for numbers maybe in the array:" << endl;
    cout << setw(10) << "Search"
         << setw(10) << "Found" 
         << setw(15) << "Seq.search" 
         << setw(15) << "Bin Search" 
         << setw(20) << "Enhanced Search" 
         << endl;

    cout << setw(10) << "------"
         << setw(10) << "-----" 
         << setw(15) << "---------" 
         << setw(15) << "----------" 
         << setw(20) << "---------------" 
         << endl;

    // Perform search tests for numbers that may or may not be in the array
    for (int key : intsMaybeVec) {
        int seqComps = 0;
        int binComps = 0;
        int enhanceComps = 0;
        int seqFunc = seq_search(vec, key, seqComps);
        bin_search(vec, key, binComps);
        bin2_search(vec, key, enhanceComps);
        cout << setw(10) << key
              << setw(10) << (seqFunc != -1 ? seqFunc : -1)
              << setw(15) << seqComps
              << setw(15) << binComps
              << setw(20) << enhanceComps
              << endl;
    }
    
    return 0;
}