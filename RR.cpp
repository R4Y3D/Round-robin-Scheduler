#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <chrono>
#include <climits>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

void displayProgress(int id, int total, int remaining) {
    int completed = total - remaining;
    int bar_width = 20;
    int progress = (completed * bar_width) / total;

    cout << "P" << id << " [";
    for (int i = 0; i < bar_width; ++i) {
        if (i < progress)
            cout << "#";
        else
            cout << "-";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << "] " << completed << "/" << total << "\r";
    cout.flush();
}

void displayQueue(const queue<int>& ready_queue) {
    queue<int> temp = ready_queue;
    cout << "Ready Queue: [";
    while (!temp.empty()) {
        cout << "P" << temp.front() + 1 << " ";
        temp.pop();
    }
    cout << "]\n";
}

//input validation (no blank spaces, letters, or negative numbers)
int getValidPositiveInteger(const string& prompt) {
    string input;
    int value;
    while (true) {
        cout << prompt;
        getline(cin, input);

        if (input.empty()) {
            cout << "Error: Input cannot be empty!" << endl;
            continue;
        }

        bool valid = true;
        for (char c : input) {
            if (!isdigit(c)) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << "Error: Please enter a valid positive integer!" << endl;
            continue;
        }

        stringstream ss(input);
        ss >> value;

        if (value <= 0) {
            cout << "Error: Please enter a positive number greater than zero!" << endl;
            continue;
        }

        return value;
    }
}

void printGanttChart(const vector<pair<int, int>>& gantt_chart, int total_time) {
    cout << "Time";
    int current_time = 0;
    for (const auto& entry : gantt_chart) {
        cout << setw(6) << current_time;
        current_time += entry.second;
    }
    cout << setw(6) << total_time << endl;

    cout << "     ";
    for (const auto& entry : gantt_chart) {
        cout << setw(6) << "P" << entry.first;
    }
    cout << endl;
}

int main() {
    cout << R"(
   __                            _                      _      _        
  /__\   ___   _   _  _ __    __| |        _ __   ___  | |__  (_) _ __  
 / \//  / _ \ | | | || '_ \  / _` | _____ | '__| / _ \ | '_ \ | || '_ \ 
/ _  \ | (_) || |_| || | | || (_| ||_____|| |   | (_) || |_) || || | | |
\/ \_/  \___/  \__,_||_| |_| \__,_|       |_|    \___/ |_.__/ |_||_| |_|
)" << endl;
    cout << "Round-Robin Scheduler Simulation\nby Rayed Jawad and Ulises Jaimez\n\n";

    int num_processes = getValidPositiveInteger("Enter the number of processes: ");
    int quantum_time = getValidPositiveInteger("Enter quantum time: ");
    int context_switch_time = getValidPositiveInteger("Enter context switch duration: ");

    cout << "________________________________________\n";

    vector<Process> processes(num_processes);
    for (int i = 0; i < num_processes; ++i) {
        cout << "Process " << i + 1 << " Details:" << endl;
        processes[i].arrival_time = getValidPositiveInteger("Enter arrival time: ");
        processes[i].burst_time = getValidPositiveInteger("Enter burst time: ");

        processes[i].id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;

        cout << "\n";
    }

    queue<int> ready_queue;
    int current_time = 0;
    int completed = 0;
    vector<bool> in_queue(num_processes, false);
    vector<pair<int, int>> gantt_chart;

    for (int i = 0; i < num_processes; ++i) {
        if (processes[i].arrival_time <= current_time) {
            ready_queue.push(i);
            in_queue[i] = true;
        }
    }

    while (completed < num_processes) {
        if (ready_queue.empty()) {
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

        int current_process_id = ready_queue.front();
        ready_queue.pop();

        int execution_time = min(quantum_time, processes[current_process_id].remaining_time);
        current_time += execution_time;
        processes[current_process_id].remaining_time -= execution_time;

        gantt_chart.push_back({ processes[current_process_id].id, execution_time });

        displayProgress(processes[current_process_id].id, processes[current_process_id].burst_time, processes[current_process_id].remaining_time);

        if (processes[current_process_id].remaining_time == 0) {
            completed++;
            processes[current_process_id].completion_time = current_time;
            processes[current_process_id].turnaround_time =
                processes[current_process_id].completion_time - processes[current_process_id].arrival_time;
            processes[current_process_id].waiting_time =
                processes[current_process_id].turnaround_time - processes[current_process_id].burst_time;
        }
        else {
            if (!ready_queue.empty()) {
                current_time += context_switch_time;
            }
            ready_queue.push(current_process_id);
        }

        for (int i = 0; i < num_processes; ++i) {
            if (!in_queue[i] && processes[i].arrival_time <= current_time) {
                ready_queue.push(i);
                in_queue[i] = true;
            }
        }
    }

    cout << "\nProcess Execution Results:\n";
    cout << "+----+----------+----------+-------------+--------------+----------+\n";
    cout << "| ID | Arrival  |  Burst   | Completion  | Turnaround   | Waiting  |\n";
    cout << "+----+----------+----------+-------------+--------------+----------+\n";

    double total_turnaround_time = 0, total_waiting_time = 0;
    for (const auto& p : processes) {
        cout << "| " << setw(2) << p.id
            << " | " << setw(8) << p.arrival_time
            << " | " << setw(8) << p.burst_time
            << " | " << setw(11) << p.completion_time
            << " | " << setw(12) << p.turnaround_time
            << " | " << setw(8) << p.waiting_time << " |\n";
        total_turnaround_time += p.turnaround_time;
        total_waiting_time += p.waiting_time;
    }
    cout << "+----+----------+----------+-------------+--------------+----------+\n";

    cout << "\nAverage Turnaround Time: "
        << fixed << setprecision(2) << total_turnaround_time / num_processes << "\n";
    cout << "Average Waiting Time: "
        << fixed << setprecision(2) << total_waiting_time / num_processes << "\n";

    cout << "\nGantt Chart:\n";
    printGanttChart(gantt_chart, current_time);

    return 0;
}