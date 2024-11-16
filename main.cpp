#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

// Process structure
struct Process {
    int pid;            // Process ID
    int arrival_time;   // Arrival Time
    int burst_time;     // Burst Time
    int priority;       // Priority (optional)
    int start_time;     // Start Time
    int completion_time; // Completion Time
    int turnaround_time; // Turnaround Time
    int waiting_time;   // Waiting Time
    int remaining_time; // Remaining Burst Time (for RR)

    Process(int id, int arrival, int burst, int prio = 0)
        : pid(id), arrival_time(arrival), burst_time(burst), priority(prio), start_time(-1), 
          completion_time(0), turnaround_time(0), waiting_time(0), remaining_time(burst) {}
};

// Function to compare processes by arrival time (for sorting)
bool compareArrivalTime(const Process& p1, const Process& p2) {
    return p1.arrival_time < p2.arrival_time;
}

// First-Come-First-Served Scheduling
void fcfs(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareArrivalTime);
    int current_time = 0;

    for (auto& process : processes) {
        if (current_time < process.arrival_time) {
            current_time = process.arrival_time;
        }
        process.start_time = current_time;
        process.completion_time = current_time + process.burst_time;
        process.turnaround_time = process.completion_time - process.arrival_time;
        process.waiting_time = process.turnaround_time - process.burst_time;
        current_time = process.completion_time;
    }
}

// Round Robin Scheduling
void roundRobin(vector<Process>& processes, int time_quantum) {
    sort(processes.begin(), processes.end(), compareArrivalTime);
    deque<Process*> ready_queue;
    int current_time = 0;
    int completed = 0;
    size_t n = processes.size();

    while (completed < n) {
        for (auto& process : processes) {
            if (process.arrival_time <= current_time && process.remaining_time > 0 &&
                find_if(ready_queue.begin(), ready_queue.end(), [&](Process* p) { return p->pid == process.pid; }) == ready_queue.end()) {
                ready_queue.push_back(&process);
            }
        }

        if (!ready_queue.empty()) {
            Process* process = ready_queue.front();
            ready_queue.pop_front();

            if (process->start_time == -1) {
                process->start_time = current_time;
            }

            int execution_time = min(time_quantum, process->remaining_time);
            current_time += execution_time;
            process->remaining_time -= execution_time;

            if (process->remaining_time == 0) {
                process->completion_time = current_time;
                process->turnaround_time = process->completion_time - process->arrival_time;
                process->waiting_time = process->turnaround_time - process->burst_time;
                completed++;
            } else {
                ready_queue.push_back(process);
            }
        } else {
            current_time++;
        }
    }
}

// Function to display and save Gantt Chart
void saveGanttChart(const vector<Process>& processes, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file for writing!\n";
        return;
    }

    cout << "\nGantt Chart:\n";
    int current_time = 0;
    for (const auto& process : processes) {
        // Add idle time if needed
        if (current_time < process.start_time) {
            cout << "| Idle ";
            file << "Idle," << current_time << "," << process.start_time << "\n";
            current_time = process.start_time;
        }
        cout << "| P" << process.pid << " ";
        file << "P" << process.pid << "," << process.start_time << "," << process.completion_time << "\n";
        current_time = process.completion_time;
    }
    cout << "|\n";
    file.close();
    cout << "Gantt chart data saved to " << filename << "\n";
}

// Main Function
int main() {
    int n, choice, time_quantum;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;
    for (int i = 0; i < n; ++i) {
        int arrival, burst, priority;
        cout << "\nProcess " << i + 1 << ":\n";
        cout << "Arrival Time: ";
        cin >> arrival;
        cout << "Burst Time: ";
        cin >> burst;
        cout << "Priority (default=0): ";
        cin >> priority;
        processes.emplace_back(i + 1, arrival, burst, priority);
    }

    cout << "\nSelect Scheduling Algorithm:\n";
    cout << "1. First-Come-First-Served (FCFS)\n";
    cout << "2. Round Robin (RR)\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 2) {
        cout << "Enter Time Quantum for Round Robin: ";
        cin >> time_quantum;
    }

    switch (choice) {
        case 1:
            fcfs(processes);
            saveGanttChart(processes, "gantt_chart.csv");
            break;
        case 2:
            roundRobin(processes, time_quantum);
            saveGanttChart(processes, "gantt_chart.csv");
            break;
        default:
            cout << "Invalid choice!\n";
            return 1;
    }

    return 0;
}
