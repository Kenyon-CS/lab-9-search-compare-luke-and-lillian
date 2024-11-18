#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>  // For std::setw, std::setprecision

using namespace std;

// Sequential search
int seq_search(vector<int> &keys, int key, int &numCmp) {
    for(int i = 0; i < keys.size(); ++i){
        ++numCmp;
        if (keys[i]==key){
            return i;
        }
    }
    return -1;
}

// Sequential search with start and stop range
int seq_search(vector<int> &keys, int key, int start, int stop, int &numCmp) {
    for(int i = start; i < stop; ++i){
        ++numCmp;
        if (keys[i]==key){
            return i;
        }
    }
    return -1;
}

// Binary search
int bin_search(vector<int> &keys, int key, int &numCmp) {
    int under, over, mid;
    under = 0;
    over = keys.size()-1;
    while(under <= over){
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

// Enhanced binary search: switches to sequential search if remaining range is < 15
int bin2_search(vector<int> &keys, int key, int &numCmp) {
    int under, over, mid;
    under = 0;
    over = keys.size()-1;
    while(under <= over){
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
        int iRand = rand() % 10000000;
        vec[i] = iRand;
    }
 
    // Sort the vector using STL sort
    sort(vec.begin(), vec.end());
    
    // Generate 50 random numbers from the data (guaranteed to be in the array)
    vector<int> intsInVec(50);
    for(int i = 0; i < 50; ++i){
        int num = rand() % vec.size();
        intsInVec[i]=vec[num];
    }

    // Generate 50 random numbers (may or may not be in the array)
    vector<int> intsMaybeVec(50);
    for(int i = 0; i < 50; ++i){
        int num = rand() % 100001;
        intsMaybeVec[i]=vec[num];
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