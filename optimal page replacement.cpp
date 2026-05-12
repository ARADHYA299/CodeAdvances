#include <iostream>
#include <vector>
using namespace std;

int predict(int pages[], vector<int>& mem, int n, int index) {
    int res = -1, farthest = index;

    for (int i = 0; i < mem.size(); i++) {
        int j;
        for (j = index; j < n; j++) {
            if (mem[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        // If not found again, return
        if (j == n) return i;
    }

    return (res == -1) ? 0 : res;
}

void Optimal(int pages[], int n, int capacity) {
    vector<int> mem;
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        bool found = false;

        for (int j = 0; j < mem.size(); j++) {
            if (mem[j] == pages[i]) {
                found = true;
                break;
            }
        }

        if (!found) {
            if (mem.size() < capacity) {
                mem.push_back(pages[i]);
            } else {
                int idx = predict(pages, mem, n, i + 1);
                mem[idx] = pages[i];
            }
            page_faults++;
        }
    }

    cout << "Optimal Page Faults: " << page_faults << endl;
}

int main(){
	int arr[] = {15,18,2,1,98};
	vector<int>mem = {15,20};
	predict(arr,mem,20,13);
	Optimal(arr,20,13);
	
	return 0;
}