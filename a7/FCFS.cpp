#include <iostream>
using namespace std;

int main(){
    
    int pageFaults = 0;
    int frames, pages;

    // Ask for the frame size
    cout << "Enter the frame size: ";
    cin >> frames;

    // Ask for the number of pages
    cout << "Enter the number of pages: ";
    cin >> pages;

    int incomingStream[pages];

    // Ask for the page values
    cout << "Enter the page values: ";
    for (int i = 0; i < pages; i++){
        cin >> incomingStream[i];
    }

    // no page is present in the frames.
    int temp[frames];
    for (int i = 0; i < frames; i++){
        temp[i] = -1;
    }

    // Printing the heading of the columns
    cout << "Incoming\t";
    for (int i = 0; i < frames; i++){
        cout << "Frame " << i + 1 << "\t\t";
    }

    for (int i = 0; i < pages; i++){
        int s = 0;
        
        // Checking if the page is already present in the frames
        for (int j = 0; j < frames; j++){
            if (incomingStream[i] == temp[j]){
                s++;
                pageFaults--;  // If the page is already present in the frames, no page fault occurs
            }
        }
        
        pageFaults++;
        if ((pageFaults <= frames) && (s == 0)){
            temp[i] = incomingStream[i];
        }
        else if(s == 0){
            temp[(pageFaults - 1) % frames] = incomingStream[i];
        }

        cout << "\n";
        cout << incomingStream[i] << "\t\t\t\t";
        for (int j = 0; j < frames; j++){
            if (temp[j] != -1)
                cout << temp[j] << "\t\t\t\t";
            else
                cout << "-\t\t\t\t";
        }
    }

    cout << "\n\nTotal Page Faults:\t" << pageFaults;
    cout << "\nTotal Hits :\t" << pages - pageFaults;
    return 0;
}

// Enter the frame size: 3
// Enter the number of pages: 15
// Enter the page values: 7 0 1 2 0 3 0 4 2 3 0 3 1 2 0
// Incoming    Frame 1     Frame 2     Frame 3
// 7               7               -               -
// 0               7               0               -
// 1               7               0               1
// 2               2               0               1
// 0               2               0               1
// 3               2               3               1
// 0               2               3               0
// 4               4               3               0
// 2               4               2               0
// 3               4               2               3
// 0               0               2               3
// 3               0               2               3
// 1               0               1               3
// 2               0               1               2
// 0               0               1               2

// Total Page Faults:  12
// Total Hits :    3
