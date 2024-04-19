// Algorithm:
// Include all libraries => 4 
// Declare the struct
// Create 2 functions for comparisons used for sorting
// Start the main function
// Declare the variables => 
// n for num of processes
// avg and total tat, ct and cpu utiliztion/idle_time
// vector for order of processes
// declare the processes array of struct
// take inputs
// Take input n 
// Then, all the burst time and arrival time
// Then, sort the processes by arrival time
// now, loop through i = 0 to n-1
// start with a if-else => for first process and bakichya processes
// for first process the start time is the arrival time
// bakichya processes sathi start time is last process cha completion time
// then calculate all the ct, tat, wt and then total vars for tat and wt
// push the process in order of execution
// if process is first or else, idle time kiti rahila he check karaych ahe
//  So, arrival time prynt cha time ha idle time asel for P1
// bakichya sathi attachya process cha start ani last process cha completion time asa asel
// ata avg kadha for tat and wt and cpu utiilization
// ata parat sort kara on the basis of pid

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct process{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time; // Time at which process gets CPU first Time.
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

// Comparator function to sort processes based on arrival time
bool compareArrival(process p1, process p2){
    return p1.arrival_time < p2.arrival_time;
}

// Comparator function to sort processes based on process ID
bool compareID(process p1, process p2){
    return p1.pid < p2.pid;
}

int main(){
    int n;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_idle_time = 0;
    vector<int> Order_Of_Execution; // Order of processes in which they are executing.

    cout << setprecision(2) << fixed;

    cout << "\n\nEnter the number of processes: ";
    cin >> n;
    cout << endl << endl;

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        cout << "Enter ARRIVAL time of process " << i + 1 << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter BURST time of process " << i + 1 << ": ";
        cin >> p[i].burst_time;
        p[i].pid = i + 1;
        cout << endl;
    }

    // Sort processes based on arrival time
    sort(p, p + n, compareArrival);

    // Calculate completion time, turnaround time, waiting time, and total turnaround/waiting time
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            p[i].start_time = p[i].arrival_time;
        } else {
            p[i].start_time = max(p[i - 1].completion_time, p[i].arrival_time);
        }
        
        p[i].completion_time = p[i].start_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        
        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
        
        // Order of processes in which they are executing.
        Order_Of_Execution.push_back(p[i].pid);
        
        if (i == 0) {
            total_idle_time += p[i].arrival_time;
        } else {
            total_idle_time += p[i].start_time - p[i - 1].completion_time;
        }
    }

    // Calculate average turnaround time, average waiting time, and CPU utilization
    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    cpu_utilisation = ((p[n - 1].completion_time - total_idle_time) / (float)p[n - 1].completion_time) * 100;

    // Sort processes based on process ID for printing
    sort(p, p + n, compareID);

    // Print process details
    cout << "\n#P\t" << "AT\t" << "BT\t" << "ST\t" << "CT\t" << "TAT\t" << "WT\t" << "RT\t" << "\n" << endl;
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].start_time << "\t" << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t" << "\n" << endl;
    }

    // Gantt chart
    cout << "\nGantt Chart:\n" << "-----------\n\n\n";
    for (int i = 0; i < n; i++) {
        cout << "| " << Order_Of_Execution[i] << " ";
    }
    cout << "|";
    cout << "\n";
    int k;
    for (k = 0; k < n; k++) {
        // Start time according to the order of execution
        for (int j = 0; j < n; j++) {
            if (Order_Of_Execution[k] == p[j].pid){
                cout << p[j].start_time << "\t";
            }
        }
    }
    cout << endl << endl;

    // Print average turnaround time, average waiting time, and CPU utilization
    cout << "\nAverage Turnaround Time = " << avg_turnaround_time << endl;
    cout << "\nAverage Waiting Time = " << avg_waiting_time << endl;
    cout << "\nCPU Utilization = " << cpu_utilisation << "%" << endl;
    cout << endl;

    return 0;
}

// Enter the number of processes: 5


// Enter ARRIVAL time of process 1: 0
// Enter BURST time of process 1: 3

// Enter ARRIVAL time of process 2: 1
// Enter BURST time of process 2: 1

// Enter ARRIVAL time of process 3: 2
// Enter BURST time of process 3: 4

// Enter ARRIVAL time of process 4: 3
// Enter BURST time of process 4: 5

// Enter ARRIVAL time of process 5: 4
// Enter BURST time of process 5: 2


// #P  AT  BT  ST  CT  TAT WT  RT

// 1   0   3   0   3   3   0

// 2   1   1   3   4   3   2

// 3   2   4   4   8   6   2

// 4   3   5   8   13  10  5

// 5   4   2   13  15  11  9


// Gantt Chart:
// -----------


// | 1 | 2 | 3 | 4 | 5 |
// 0   3   4   8   13


// Average Turnaround Time = 6.60

// Average Waiting Time = 3.60

// CPU Utilization = 100.00%
