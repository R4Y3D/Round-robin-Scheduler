#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// Struct to represent a process
struct Process {
    int id;             // Process ID
    int arrival_time;   // Time the process arrives
    int burst_time;     // Total execution time needed
    int remaining_time; // Time left to execute
    int completion_time; // Time process finishes
};

// Function to display process information
void display_processes(const std::vector<Process>& processes) {
    std::cout << "\nProcess Information:\n";
    std::cout << "ID\tArrival\tBurst\n";
    for (const auto& p : processes) {
        std::cout << p.id << "\t" << p.arrival_time << "\t" << p.burst_time << "\n";
    }
}

int main() {
    // Welcome message
    std::cout << "=== Round Robin Scheduler Simulator ===\n";

    // Step 1: User input for quantum and context switch time
    int quantum, context_switch, num_processes;
    std::cout << "Enter the quantum time: ";
    std::cin >> quantum;
    std::cout << "Enter the context switch duration: ";
    std::cin >> context_switch;

    // Step 2: Input the number of processes and their details
    std::cout << "Enter the number of processes: ";
    std::cin >> num_processes;

    std::vector<Process> processes;
    for (int i = 0; i < num_processes; ++i) {
        int arrival, burst;
        std::cout << "Enter arrival time for Process " << i + 1 << ": ";
        std::cin >> arrival;
        std::cout << "Enter burst time for Process " << i + 1 << ": ";
        std::cin >> burst;
        processes.push_back({i + 1, arrival, burst, burst, 0}); // Initialize process
    }

    // Display the entered processes
    display_processes(processes);

    // Step 3: Initialize variables for the Round Robin logic
    std::queue<Process> ready_queue;
    int current_time = 0;

    // TODO: Implement Round Robin scheduling logic

    // Placeholder for output
    std::cout << "\nSimulation complete! (Round Robin logic to be implemented)\n";

    // Step 4: Metrics calculation (to be added)
    std::cout << "\nFinal Results (Metrics to be added):\n";
    // TODO: Print completion time, turnaround time, waiting time

    return 0;
}