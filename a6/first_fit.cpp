#include<bits/stdc++.h>
using namespace std;

// Function to allocate memory to blocks as per First fit algorithm
void firstFit(int blockSize[], int blockNum, int processSize[], int processNum) {
    // Stores block id of the block allocated to a process
    int allocation[processNum];
    
    // Initially no block is assigned to any process
    memset(allocation, -1, sizeof(allocation));
    
    // pick each process and find suitable blocks according to its size and assign to it
    for (int i = 0; i < processNum; i++) {
        for (int j = 0; j < blockNum; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j; // allocate block j to p[i]
                blockSize[j] -= processSize[i]; // Reduce available memory in this block.
                break;
            }
        }
    }
    
    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < processNum; i++) {
        cout << " " << i+1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

// Driver code
int main() {
    int blocks, process;
    cout << "Enter the number of blocks: ";
    cin >> blocks;
    cout << "Enter the number of process: ";
    cin >> process;
    
    // Allocate memory for the array
    int blockarray[blocks];
    int processarray[process];
    
    cout << "Enter all the blocks size: ";
    for (int i = 0; i < blocks; i++) {
        cin >> blockarray[i];
    }
    cout << "Enter all the process size: ";
    for (int i = 0; i < process; i++) {
        cin >> processarray[i];
    }
    
    int m = sizeof(blockarray) / sizeof(blockarray[0]);
    int n = sizeof(processarray) / sizeof(processarray[0]);
    
    firstFit(blockarray, m, processarray, n);
    
    return 0 ;
}
