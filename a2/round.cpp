#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <string.h>
using namespace std;

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

// Function to compare processes based on arrival time
bool compare1(process p1, process p2) {
    return p1.arrival_time < p2.arrival_time;
}

// Function to compare processes based on process ID
bool compare2(process p1, process p2) {
    return p1.pid < p2.pid;
}

int main() {
    
    int n;
    int tq; // Time quantum
    
    struct process p[100]; // Array to store processes
    
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    
    float throughput;
    
    int burst_remaining[100];
    int idx; // Index of the current process
    
    cout << setprecision(2) << fixed;
    
    vector<int> Order_Of_Execution; // Vector to store order of execution
    vector<int> Time; // Vector to store time for Gantt chart

    cout<<"\nEnter the number of processes: ";
    cin>>n;
    cout<<"\nEnter time quantum: ";
    cin>>tq;

    // Input arrival time and burst time for each process
    for(int i = 0; i < n; i++) {
        cout<<"Enter ARRIVAL time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter BURST time of process "<<i+1<<": ";
        cin>>p[i].burst_time;
        burst_remaining[i] = p[i].burst_time; // Initialize burst_remaining array
        p[i].pid = i+1;
        cout<<endl;
    }

    // Sort processes based on arrival time
    sort(p, p+n, compare1);

    queue<int> q; // Ready queue
    int current_time = 0; // Current time
    
    q.push(0); // Push first process into the ready queue
    
    int completed = 0; // Number of completed processes
    int mark[100]; // Array to mark processes
    
    memset(mark, 0, sizeof(mark)); // Initialize mark array with 0

    // Loop until all processes are completed
    while(completed != n) {
        idx = q.front(); // Get the front process from the ready queue
        q.pop(); // Remove the front process from the ready queue

        // Check if the process is coming for the first time or after context switching
        if(burst_remaining[idx] == p[idx].burst_time) {
            p[idx].start_time = max(current_time, p[idx].arrival_time);
            total_idle_time += p[idx].start_time - current_time;
            current_time = p[idx].start_time;
        }

        // Check if the remaining burst time is greater than the time quantum
        if(burst_remaining[idx] - tq > 0) {
            burst_remaining[idx] -= tq;
            Order_Of_Execution.push_back(p[idx].pid); // Add process to the order of execution
            Time.push_back(current_time); // Add time to the Gantt chart
            current_time += tq;
        } else{
            // Remaining burst time is less than or equal to the time quantum
            Order_Of_Execution.push_back(p[idx].pid); // Add process to the order of execution
            Time.push_back(current_time); // Add time to the Gantt chart
            current_time += burst_remaining[idx];
            burst_remaining[idx] = 0;
            completed++;

            if (completed == n) {
                // Final Completion time
                Time.push_back(current_time);
            }

            // Calculate completion time, turnaround time, waiting time, and response time for the process
            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;
            
            // Update total turnaround time, waiting time, and response time
            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;
        }

        // Push processes into the ready queue based on arrival time and burst remaining time
        for(int i = 1; i < n; i++) {
            if(burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0) {
                q.push(i);
                mark[i] = 1;
            }
        }

        // Push the current process back into the ready queue if it's not completed
        if(burst_remaining[idx] > 0) {
            q.push(idx);
        }

        // If the ready queue is empty, push the next process with remaining burst time into the queue
        if(q.empty()) {
            for(int i = 1; i < n; i++) {
                if(burst_remaining[i] > 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
    }

    // Calculate average turnaround time, waiting time, response time, CPU utilization, and throughput
    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    avg_response_time = (float) total_response_time / n;
    cpu_utilisation = ((p[n-1].completion_time - total_idle_time) / (float) p[n-1].completion_time)*100;
    throughput = float(n) / (p[n-1].completion_time - p[0].arrival_time);

    // Sort processes based on process ID
    sort(p, p+n, compare2);

    cout<<endl<<endl;
    cout<<""<<endl;
    cout<<"#P\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<"\n"<<endl;

    // Print process details
    for(int i = 0; i < n; i++) {
        cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<p[i].response_time<< "\t"<<"\n"<<endl;
    }

    // Print Gantt chart
    cout<<"\n";
    cout<<"Gantt Chart:\n"<<"-----------"<<"\n\n\n";
    for (int i=0; i<Order_Of_Execution.size(); i++) {
        cout <<"| "<<Order_Of_Execution[i]<< " ";
    }
    cout<<"|";
    cout<<"\n";
    for (int i = 0; i < Time.size() ; i++) {
        cout <<Time[i]<< "\t";
    }
    cout<<"\n\n";
    // Print average turnaround time, waiting time, response time, CPU utilization, and throughput
    cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl<<endl;
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl<<endl;
    cout<<"Average Response Time = "<<avg_response_time<<endl<<endl;
    cout<<"CPU Utilization = "<<cpu_utilisation<<"%"<<endl<<endl;
    cout<<"Throughput = "<<throughput<<" process/unit time"<<endl<<endl;
    cout<<""<<endl;
    return 0;
}
