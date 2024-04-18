#include<bits/stdc++.h>
using namespace std;

// Function to allocate memory to blocks as per Next Fit algorithm
void nextFit(int blockSize[], int blockNum, int processSize[], int processNum) {
    
    // Stores block id of the block allocated to a process
    int allocation[processNum];
    
    // Initially no block is assigned to any process
    memset(allocation, -1, sizeof(allocation));
    
    // Start from the first block, this is the pointer from which the next block is to be searched
    int start = 0;
    
    // Pick each process and find suitable blocks according to its size and assign to it
    for (int i = 0; i < processNum; i++){
        int j;
        for (j = start; j < blockNum; j++){
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j; // Allocate block j to process i
                blockSize[j] -= processSize[i]; // Reduce available memory in this block
                start = j + 1; // Start next search from next block
                break;
            }
        }
        
        // If no block is found, start from the first block for the next process
        if (j == blockNum){
            start = 0;
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
    cout << "Enter the number of processes: ";
    cin >> process;
    
    // Allocate memory for the array
    int blockarray[blocks];
    int processarray[process];
    
    cout << "Enter all the blocks sizes: ";
    for (int i = 0; i < blocks; i++) {
        cin >> blockarray[i];
    }
    cout << "Enter all the process sizes: ";
    for (int i = 0; i < process; i++) {
        cin >> processarray[i];
    }
    
    int m = sizeof(blockarray) / sizeof(blockarray[0]);
    int n = sizeof(processarray) / sizeof(processarray[0]);
    
    nextFit(blockarray, m, processarray, n);
    
    return 0;

}