#include <iostream>
#include <queue>
#include <vector>
#include <climits> // For INT_MAX

using namespace std;

// Struct to represent a process
struct Process {
    int id;             // Process ID
    int arrival_time;   // Time when process arrives
    int burst_time;     // Total time required to execute
    int remaining_time; // Time left to execute
    int completion_time; // Time when process finishes
    int waiting_time;   // Time spent waiting in the ready queue
    int turnaround_time; // Total time from arrival to completion
};

int main() {
    // Input for quantum time and context switch duration
    int quantum_time, context_switch_time, num_processes;
    cout << "Enter quantum time: ";
    cin >> quantum_time;
    cout << "Enter context switch duration: ";
    cin >> context_switch_time;
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    // Input process details
    vector<Process> processes(num_processes);
    for (int i = 0; i < num_processes; ++i) {
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burst_time;

        // Initialize process attributes
        processes[i].id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    // Simulation variables
    queue<int> ready_queue; // Queue for process IDs
    int current_time = 0;   // Tracks the current simulation time
    int completed = 0;      // Number of processes completed
    vector<bool> in_queue(num_processes, false); // Tracks if a process is in the queue

    // Add initial processes to the queue
    for (int i = 0; i < num_processes; ++i) {
        if (processes[i].arrival_time <= current_time) {
            ready_queue.push(i);
            in_queue[i] = true;
        }
    }

    // Round Robin scheduling loop
    while (completed < num_processes) {
        if (ready_queue.empty()) {
            // FIX 1: Move time forward to the next arrival, not incrementally
            int next_arrival = INT_MAX;
            for (int i = 0; i < num_processes; ++i) {
                if (!in_queue[i] && processes[i].arrival_time > current_time) {
                    next_arrival = min(next_arrival, processes[i].arrival_time);
                }
            }
            current_time = next_arrival;
            for (int i = 0; i < num_processes; ++i) {
                if (!in_queue[i] && processes[i].arrival_time <= current_time) {
                    ready_queue.push(i);
                    in_queue[i] = true;
                }
            }
            continue;
        }

        // Get the next process from the queue
        int current_process_id = ready_queue.front();
        ready_queue.pop();

        // Execute the process for quantum time or until it finishes
        int execution_time = min(quantum_time, processes[current_process_id].remaining_time);
        current_time += execution_time;
        processes[current_process_id].remaining_time -= execution_time;

        // Check if the process is completed
        if (processes[current_process_id].remaining_time == 0) {
            completed++;
            processes[current_process_id].completion_time = current_time;
            processes[current_process_id].turnaround_time =
                processes[current_process_id].completion_time - processes[current_process_id].arrival_time;
            processes[current_process_id].waiting_time =
                processes[current_process_id].turnaround_time - processes[current_process_id].burst_time;
        } else {
            // FIX 2: Add context switch time only if the queue is not empty
            if (!ready_queue.empty()) {
                current_time += context_switch_time;
            }
            // Re-queue the process
            ready_queue.push(current_process_id);
        }

        // Add new processes that have arrived to the queue
        for (int i = 0; i < num_processes; ++i) {
            if (!in_queue[i] && processes[i].arrival_time <= current_time) {
                ready_queue.push(i);
                in_queue[i] = true;
            }
        }
    }

    // Display results
    cout << "\nProcess Execution Results:\n";
    cout << "ID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    double total_turnaround_time = 0, total_waiting_time = 0;
    for (const auto& p : processes) {
        cout << p.id << "\t" << p.arrival_time << "\t" << p.burst_time
             << "\t" << p.completion_time << "\t\t" << p.turnaround_time
             << "\t\t" << p.waiting_time << "\n";
        total_turnaround_time += p.turnaround_time;
        total_waiting_time += p.waiting_time;
    }

    // Display average statistics
    cout << "\nAverage Turnaround Time: " << total_turnaround_time / num_processes << "\n";
    cout << "Average Waiting Time: " << total_waiting_time / num_processes << "\n";

    return 0;
}

