#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

void FIFO(int pages[], int n, int capacity) {
    unordered_set<int> s;  // Tracks current pages in memory
    queue<int> q;          // Maintains order of arrival
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];

        // If not in memory
        if (s.find(page) == s.end()) {
            // If memory is full, remove oldest page
            if (s.size() == capacity) {
                int oldest = q.front();
                q.pop();
                s.erase(oldest);
            }

            // Insert new page
            s.insert(page);
            q.push(page);
            page_faults++;
        }
    }

    cout << "FIFO Page Faults: " << page_faults << endl;
}

int main(){
	int arr[] = {12,4,21,3};
	FIFO(arr, 5 , 12);
	return 0;
}
