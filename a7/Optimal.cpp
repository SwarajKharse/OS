#include <bits/stdc++.h>
using namespace std;

// This function checks if the current stream item(key) exists in any of the frames or not
int search(int key, int frame_items[], int frame_occupied) {
    for (int i = 0; i < frame_occupied; i++) {
        if (frame_items[i] == key)
            return 1;
    }
    return 0;
}

void printOuterStructure(int frameCount) {
    printf("Stream ");
    for(int i = 0; i < frameCount; i++)
        printf("Frame%d ", i + 1);
}

void printCurrFrames(int item, int frame_items[], int frame_occupied, int frameCount) {
    // print current reference stream item
    cout << "\n" << item << "\t\t";
    // print frame occupants one by one
    for(int i = 0; i < frameCount; i++) {
        if(i < frame_occupied)
            cout << frame_items[i] << "\t\t";
        else
            cout << "- \t\t";
    }
}

// This Function helps in finding the frame that will not be used for the longest period of time in the future in pagesValues[0 ... pageCount - 1]
int predict(int pagesValues[], int frame_items[], int pageCount, int index, int frame_occupied) {
    int result = -1, farthest = index;
    
    for (int i = 0; i < frame_occupied; i++) {
        int j;
        for (j = index; j < pageCount; j++) {
            if (frame_items[i] == pagesValues[j]) {
                if (j > farthest) {
                    farthest = j;
                    result = i;
                }
                break;
            }
        }
        if (j == pageCount)
            return i;
    }
    return (result == -1) ? 0 : result;
}

void optimalPage(int pagesValues[], int pageCount, int frame_items[], int frameCount){
    
    int frame_occupied = 0;
    printOuterStructure(frameCount);
    int hits = 0;
    
    for (int i = 0; i < pageCount; i++) {
        
        if (search(pagesValues[i], frame_items, frame_occupied)){
            hits++;
            printCurrFrames(pagesValues[i], frame_items, frame_occupied, frameCount);
            continue;
        }
        
        if (frame_occupied < frameCount){
            frame_items[frame_occupied] = pagesValues[i];
            frame_occupied++;
            printCurrFrames(pagesValues[i], frame_items, frame_occupied, frameCount);
        }else{
            int pos = predict(pagesValues, frame_items, pageCount, i + 1, frame_occupied);
            frame_items[pos] = pagesValues[i];
            printCurrFrames(pagesValues[i], frame_items, frame_occupied, frameCount);
        }
    }
    
    cout << "\n\nHits: " << hits << "\n";
    cout << "Misses: " << pageCount - hits << "\n";
}

// Driver Function
int main() {
    
    int frameCount, pageCount;
    
    cout << "Enter the number of frames: ";
    cin >> frameCount;
    cout << "Enter the number of pages: ";
    cin >> pageCount;
    
    int pagesValues[pageCount];
    
    cout << "Enter the page values: ";
    for(int i = 0; i < pageCount; i++){
        cin >> pagesValues[i];
    }
    
    int frame_items[frameCount];
    optimalPage(pagesValues, pageCount, frame_items, frameCount);
    
    return 0;
}

// Enter the number of frames: 4
// Enter the number of pages: 20
// Enter the page values: 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
// Stream Frame1 Frame2 Frame3 Frame4 
// 7       7       -       -       - 
// 0       7       0       -       - 
// 1       7       0       1       - 
// 2       7       0       1       2
// 0       7       0       1       2
// 3       3       0       1       2
// 0       3       0       1       2
// 4       3       0       4       2
// 2       3       0       4       2
// 3       3       0       4       2
// 0       3       0       4       2
// 3       3       0       4       2
// 2       3       0       4       2
// 1       1       0       4       2
// 2       1       0       4       2
// 0       1       0       4       2
// 1       1       0       4       2
// 7       1       0       7       2
// 0       1       0       7       2
// 1       1       0       7       2

// Hits: 12
// Misses: 8