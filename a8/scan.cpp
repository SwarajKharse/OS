#include <bits/stdc++.h>
using namespace std;

void SCAN(int arr[], int head, string direction, int size, int disk_size){
    
    int seek_count = 0;
    int distance, cur_track;
    
    vector<int> left, right;
    vector<int> seek_sequence;

    if (direction == "left") left.push_back(0);
    else if (direction == "right") right.push_back(disk_size - 1);

    for (int i = 0; i < size; i++) {
        if (arr[i] < head) left.push_back(arr[i]);
        if (arr[i] > head) right.push_back(arr[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int run = 2;
    while (run--) {
        if (direction == "left") {
            for (int i = left.size() - 1; i >= 0; i--) {
                cur_track = left[i];
                seek_sequence.push_back(cur_track);
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
            direction = "right";
        } else if (direction == "right") {
            for (int i = 0; i < right.size(); i++) {
                cur_track = right[i];
                seek_sequence.push_back(cur_track);
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
            direction = "left";
        }
    }

    cout << "Total number of seek operations: " << seek_count << '\n';
    cout << "Seek Sequence is: ";
    for (int i = 0; i < seek_sequence.size(); i++) {
        if (i == seek_sequence.size() - 1) cout << seek_sequence[i];
        else cout << seek_sequence[i] << " -> ";
    }
}

int main() {
    int size;
    cout << "Enter the number of requests: ";
    cin >> size;

    int disk_size;
    cout << "Enter the disk size: ";
    cin >> disk_size;

    int arr[size];
    cout << "Enter the requests: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    int head;
    cout << "Enter the initial head position: ";
    cin >> head;

    string direction;
    cout << "Enter the direction (left or right): ";
    cin >> direction;

    SCAN(arr, head, direction, size, disk_size);
    return 0;
}

// Enter the number of requests: 7
// Enter the disk size: 200
// Enter the requests: 16 24 43 82 140 170 190
// Enter the initial head position: 50
// Enter the direction (left or right): right
// Total number of seek operations: 332
// Seek Sequence is: 82 -> 140 -> 170 -> 190 -> 199 -> 43 -> 24 -> 16

