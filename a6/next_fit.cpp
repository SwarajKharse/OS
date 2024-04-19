#include<bits/stdc++.h>
using namespace std;

// Function to allocate memory to blocks as per Next Fit algorithm
void nextFit(int blockSize[], int blockNum, int processSize[], int processNum) {
    int allocation[processNum];
    memset(allocation, -1, sizeof(allocation));

    int start = 0;

    for (int i = 0; i < processNum; i++) {
        int found = false;
        for (int j = start; j < blockNum; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                start = (j + 1) % blockNum;
                found = true;
                break;
            }
        }

        if (!found) {
            for (int j = 0; j < start; j++) {
                if (blockSize[j] >= processSize[i]) {
                    allocation[i] = j;
                    blockSize[j] -= processSize[i];
                    start = (j + 1) % blockNum;
                    found = true;
                    break;
                }
            }
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < processNum; i++) {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
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

// Enter the number of blocks: 5
// Enter the number of processes: 4
// Enter all the blocks sizes: 100 500 200 300 600
// Enter all the process sizes: 212 417 112 426

// Process No. Process Size    Block no.
//  1      212     2
//  2      417     5
//  3      112     2
//  4      426     Not Allocated
