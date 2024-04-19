#include <bits/stdc++.h>
using namespace std;

void calculatedifference(int request[], int head, int diff[][2], int n) {
    for (int i = 0; i < n; i++) {
        diff[i][0] = abs(head - request[i]);
    }
}

int findMIN(int diff[][2], int n) {
    int index = -1;
    int minimum = 1e9;
    for (int i = 0; i < n; i++) {
        if (!diff[i][1] && minimum > diff[i][0]) {
            minimum = diff[i][0];
            index = i;
        }
    }
    return index;
}

void shortestSeekTimeFirst(int request[], int head, int n){
    
    if (n == 0) return;
    int diff[n][2];
    for(int i=0; i<n; i++){
        for(int j=0; j<2;j++){
            diff[i][j] = 0;
        }
    }
    
    int seekcount = 0;
    
    int seeksequence[n + 1];
    memset(seeksequence, 0, sizeof(seeksequence));
    
    for (int i = 0; i < n; i++) {
        seeksequence[i] = head;
        calculatedifference(request, head, diff, n);
        int index = findMIN(diff, n);
        diff[index][1] = 1;
        seekcount += diff[index][0];
        head = request[index];
    }
    
    seeksequence[n] = head;
    
    cout << "Total number of seek operations = " << seekcount << endl;
    cout << "Seek sequence is : ";
    for (int i = 0; i <= n; i++) {
        cout << seeksequence[i] << " ";
    }
}

int main() {
    int n;
    cout << "Enter the number of requests: ";
    cin >> n;
    int proc[n];
    cout << "Enter the requests: ";
    for (int i = 0; i < n; i++) {
        cin >> proc[i];
    }
    int head;
    cout << "Enter the initial head position: ";
    cin >> head;
    shortestSeekTimeFirst(proc, head, n);
    return 0;
}

// Enter the number of requests: 8
// Enter the requests: 14 37 65 67 98 112 124 183
// Enter the initial head position: 53
// Total number of seek operations = 236
// Seek sequence is : 53 65 67 37 14 98 112 124 183 