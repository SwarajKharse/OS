#include <bits/stdc++.h>
using namespace std;

int main() {
    int i, n, m, sum = 0, h;
    cout << "Enter the size of disk: ";
    cin >> m;
    cout << "Enter number of requests: ";
    cin >> n;
    cout << "Enter the requests: ";

    // creating an array of size n
    vector<int> a(n);
    for (i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (i = 0; i < n; i++) {
        if (a[i] > m) {
            cout << "Error, Unknown position " << a[i] << "\n";
            return 0;
        }
    }

    cout << "Enter the head position: ";
    cin >> h;

    // head will be at h at the starting
    int temp = h;
    cout << temp;
    for (i = 0; i < n; i++) {
        cout << " -> " << a[i] << ' ';
        // calculating the difference for the head movement
        sum += abs(a[i] - temp);
        // head is now at the next I/O request
        temp = a[i];
    }

    cout << '\n';
    cout << "Total head movements = " << sum << '\n';

    return 0;
}

// Enter the size of disk: 200
// Enter number of requests: 8
// Enter the requests: 98 183 37 122 14 124 65 67
// Enter the head position: 53
// 53 -> 98  -> 183  -> 37  -> 122  -> 14  -> 124  -> 65  -> 67 
// Total head movements = 640