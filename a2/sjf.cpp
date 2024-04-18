#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstring>
using namespace std;

// Define the struct which has 7 attributes
struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time; // Time at which process gets CPU first Time.
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int main() {
    int n;
    struct process p[100];

    // Variables for calculating the averages
    float avg_turnaround_time;
    float avg_waiting_time;
    float cpu_utilisation;

    // variables required for counting the totals 
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_idle_time = 0;

    // to check if the processes are completed or not
    int is_completed[100];
    memset(is_completed, 0, sizeof(is_completed));
    
    // Order of processes in which they are executing.
    vector<int> Order_Of_Execution; 

    cout << setprecision(2) << fixed;
    cout << "\nEnter the number of processes: ";
    cin >> n;
    cout << endl;

    // Take Inputs i.e. arrival time and burst time of each process
    for (int i = 0; i < n; i++) {
        cout << "Enter ARRIVAL time of process " << i + 1 << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter BURST time of process " << i + 1 << ": ";
        cin >> p[i].burst_time;
        p[i].pid = i + 1;
        cout << endl;
    }

    // vars required to know current situation of the processes
    int current_time = 0;
    int completed = 0;
    int prev = 0;
    
    // Loop till all executing is completed
    while (completed != n) {
        int idx = -1;
        int mn = 10000000;

        // Finding the shortest job to execute next
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && is_completed[i] == 0) {
                
                // Compute least burst time
                if (p[i].burst_time < mn) {
                    mn = p[i].burst_time;
                    idx = i;
                }
                
                // Compare arrival time when 'least burst time' will be same for two processes
                if (p[i].burst_time == mn) {
                    if (p[i].arrival_time < p[idx].arrival_time) {
                        mn = p[i].burst_time;
                        idx = i;
                    }
                }
            }
        }

        // If we get a process else increment one second in current time
        if (idx != -1) {
            
            // Calculate the basic details of the process which are due to non-preemption
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

            // Calculate the overall total variables
            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_idle_time += p[idx].start_time - prev;

            // update the visited array and increment the completed var
            is_completed[idx] = 1;
            completed++;

            // Push the variable in the vector and update the current time
            // The current time is the completion time of the previous process
            Order_Of_Execution.push_back(p[idx].pid);
            current_time = p[idx].completion_time;
            prev = current_time;
        } else {
            current_time++;
        }
    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;

    for (int i = 0; i < n; i++) {
        min_arrival_time = min(min_arrival_time, p[i].arrival_time);
        max_completion_time = max(max_completion_time, p[i].completion_time);
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    cpu_utilisation = ((max_completion_time - total_idle_time) / (float)max_completion_time) * 100;

    cout << endl << endl;
    cout << "" << endl;
    cout << "#P\t" << "AT\t" << "BT\t" << "ST\t" << "CT\t" << "TAT\t" << "WT\t" << "RT\t" << "\n" << endl;

    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].start_time << "\t" << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t" << "\t" << "\n" << endl;
    }

    // Gantt chart...
    cout << "\n";
    cout << "Gantt Chart:\n" << "-----------" << "\n\n\n";

    for (int i = 0; i < n; i++) {
        cout << "| " << Order_Of_Execution[i] << " ";
    }

    cout << "|" << endl;

    int k;

    for (k = 0; k < Order_Of_Execution.size(); k++) {
        // Start time according to order of execution.
        for (int j = 0; j < Order_Of_Execution.size(); j++) {
            if (Order_Of_Execution[k] == p[j].pid) {
                cout << p[j].start_time << "\t";
            }
        }
    }

    cout << max_completion_time << endl << endl;
    cout << "Average Turnaround Time = " << avg_turnaround_time << endl << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << endl << endl;
    cout << "CPU Utilization = " << cpu_utilisation << "%" << endl << endl;
    cout << "" << endl;

    return 0;
}
