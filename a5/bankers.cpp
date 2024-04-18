#include <iostream>
using namespace std;

int main() {
    int numProcesses, numResources;
    // Input the number of processes and resources
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    cout << "\nEnter the number of resources: ";
    cin >> numResources;

    // Arrays to store maximum resource requirements, currently allocated resources,
    // needed resources, available resources, safe sequence, and final available resources
    int maxResources[numProcesses][numResources];
    int allocated[numProcesses][numResources];
    int needed[numProcesses][numResources];
    
    int available[numResources];
    int safeSequence[numProcesses];
    int finalAvailable[numProcesses][numResources];

    // Input the maximum resource requirements for each process
    cout << "\nEnter the maximum resource requirements:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "For Process " << i << " Enter " << numResources << " Max Resources : ";
        for (int j = 0; j < numResources; j++) {
            cin >> maxResources[i][j];
        }
    }

    // Input the currently allocated resources for each process
    cout << "\nEnter the currently allocated resources:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "For Process " << i << " Enter " << numResources << " currently Allocated Resources : ";
        for (int j = 0; j < numResources; j++)
            cin >> allocated[i][j];
    }

    // Input the available resources
    cout << "\nEnter the available resources:\n";
    for (int i = 0; i < numResources; i++) {
        cout << "Resource " << i << ": ";
        cin >> available[i];
    }

    // Calculate the needed resources for each process
    cout << "\nThe required resources (Needed) are:\n";
    cout << " ";
    for (int i = 0; i < numResources; i++) {
        cout << "R" << i << " ";
    }
    
    cout << "\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "P" << i << " ";
        for (int j = 0; j < numResources; j++) {
            needed[i][j] = maxResources[i][j] - allocated[i][j];
            cout << needed[i][j] << " ";
        }
        cout << "\n";
    }

    // Check for safe or unsafe state
    bool unsafe = false;
    cout << "\nChecking for safe or unsafe state:\n";
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            if (needed[i][j] > available[j]) {
                unsafe = true;
                break;
            }
        }
    }
    
    if (unsafe) {
        cout << "The system is in an unsafe state.\n\n";
    } else {
        cout << "The system is in a safe state.\n\n";
    }

    // Initialize an array to keep track of visited processes
    bool visited[numProcesses];
    for(int i=0; i<numProcesses; i++){
        visited[i] = false;
    }
    
    int count = 0;
    // Find the safe sequence
    while (count < numProcesses){
        
        bool found = false;
        for (int i = 0; i < numProcesses; i++) {
            if (!visited[i]){
                bool canAllocate = true;
                for (int j = 0; j < numResources; j++) {
                    if (needed[i][j] > available[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    // Allocate resources
                    for (int k = 0; k < numResources; k++) {
                        available[k] += allocated[i][k];
                        finalAvailable[i][k] = available[k];
                    }
                    // Update safe sequence and mark process as visited
                    safeSequence[count++] = i;
                    visited[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "The system is in an unsafe state, and no safe sequence exists.\n";
            return 0;
        }
    }

    // Print the safe sequence
    cout << "The safe sequence is: ";
    for (int i = 0; i < numProcesses; i++) {
        cout << "P" << safeSequence[i] << " ";
    }
    cout << "\n\n";

    // Print the final process-wise available resources table
    cout << "The final process-wise available resources table:\n";
    cout << " ";
    for (int i = 0; i < numResources; i++) {
        cout << "R" << i << " ";
    }
    cout << "\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "P" << i << " ";
        for (int j = 0; j < numResources; j++) {
            cout << finalAvailable[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
