#include <iostream>
using namespace std;

int main() {
    
    int total_frames, total_pages, position, k, l;
    int page_fault = 0;

    // Ask for the number of frames
    cout << "Enter the number of frames: ";
    cin >> total_frames;
    
    int frames[total_frames];
    int temp[total_frames];

    // Ask for the number of pages
    cout << "Enter the number of pages: ";
    cin >> total_pages;
    int pages[total_pages];

    // Ask for the page values
    cout << "Enter the page values: ";
    for (int n = 0; n < total_pages; n++) {
        cin >> pages[n];
    }

    // Print the header with appropriate spacing
    cout << "Incoming\t";
    for (int m = 0; m < total_frames; m++) {
        cout << "Frame " << m + 1 << "\t\t";
    }
    cout << endl;

    // Initialize frames array with -1
    for (int m = 0; m < total_frames; m++) {
        frames[m] = -1;
    }

    // Process each incoming page
    for (int n = 0; n < total_pages; n++) {
        cout << pages[n] << "\t\t\t";
        int a = 0, b = 0;  // To check if frame found or not

        // Check if page is already in frames
        for (int m = 0; m < total_frames; m++) {
            if (frames[m] == pages[n]){
                a = 1;
                b = 1;
                break;
            }
        }

        // If page not found in frames check if any frame is empty and if it is replace them.. 
        if (a == 0) {
            for (int m = 0; m < total_frames; m++) {
                if (frames[m] == -1) {
                    frames[m] = pages[n];
                    b = 1;
                    page_fault++;
                    break;
                }
            }
        }

        // If no empty frame, find page to replace
        if (b == 0) {

            // initialize the temp array with 0 
            for(int m = 0; m < total_frames; m++) {
                temp[m] = 0;
            }

            // Check which frames are being used recently and update the temp array
            for (k = n - 1, l = 1; l <= total_frames - 1; l++, k--) {
                for (int m = 0; m < total_frames; m++) {
                    if (frames[m] == pages[k]) {
                        temp[m] = 1;
                    }
                }
            }

            // If temp array has 0, replace the frame with the page that is not being used recently
            for (int m = 0; m < total_frames; m++) {
                if(temp[m] == 0) {
                    position = m;
                }
            }
            
            frames[position] = pages[n];
            page_fault++;
        }

        // Print the frames with appropriate spacing
        for (int m = 0; m < total_frames; m++) {
            cout << frames[m] << "\t\t\t";
        }
        cout << endl;
    }

    // Print total page faults
    cout << "\nTotal Number of Page Faults: " << page_fault << endl;

    return 0;
}