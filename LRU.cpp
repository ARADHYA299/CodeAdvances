#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

void LRU(int pages[], int n, int capacity) {
    unordered_set<int> s; // Holds pages in memory
    unordered_map<int, int> indexes; // Last used index
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];

        // If not present
        if (s.find(page) == s.end()) {
            // If full, find least recently used
            if (s.size() == capacity) {
                int lru = INT_MAX, val;
                for (int p : s) {
                    if (indexes[p] < lru) {
                        lru = indexes[p];
                        val = p;
                    }
                }
                s.erase(val);
            }
            s.insert(page);
            page_faults++;
        }

        // Update the last used index
        indexes[page] = i;
    }

    cout << "LRU Page Faults: " << page_faults << endl;
}

int main(){
	int arr[] = {43,2,1,53,87};
	
	LRU(arr,12,15);
	
	return 0;
}