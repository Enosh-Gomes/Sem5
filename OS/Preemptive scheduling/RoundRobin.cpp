#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

class Process {
public:
    string Process_name;
    float Arrival_time;
    float Burst_time;
    float Remaining_time;
    float Completion_time;
    float Turnaround_time;
    float Waiting_time;
    float Start_time;
    bool started;

    Process() {
        Process_name = "";
        Arrival_time = Burst_time = Remaining_time = Completion_time = Turnaround_time = Waiting_time = Start_time = 0;
        started = false;
    }

    void CreateProcess(int index) {
        cout << "\nEnter name for process " << index + 1 << ": ";
        cin >> Process_name;
        cout << "Enter arrival time for process " << index + 1 << ": ";
        cin >> Arrival_time;
        cout << "Enter burst time for process " << index + 1 << ": ";
        cin >> Burst_time;
        Remaining_time = Burst_time;
    }

    void DisplayProcess() const {
        cout << left << setw(5) << "" << setw(16) << Process_name
            << setw(12) << Arrival_time
            << setw(14) << Burst_time
            << setw(18) << Completion_time
            << setw(17) << Turnaround_time
            << Waiting_time << "\n";
    }
};

void displayProcesses(const vector<Process> &P, float average_Turn_Around_Time, float average_Waiting_Time) {
    cout << endl << "------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(15) << "Process Name"
        << setw(15) << "Arrival Time"
        << setw(12) << "Burst Time"
        << setw(17) << "Completion Time"
        << setw(19) << "Turn Around Time"
        << setw(17) << "Waiting Time" << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    for (auto& p : P)
        p.DisplayProcess();
    cout << "------------------------------------------------------------------------------------------" << endl;
    cout << "\nAverage Turn Around Time: " << fixed << setprecision(2) << average_Turn_Around_Time << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) << average_Waiting_Time << endl;
}

void Sort_By_AT(vector<Process>& P) {
    int size = P.size();
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (P[j].Arrival_time > P[j + 1].Arrival_time)
                swap(P[j], P[j + 1]);
        }
    }
}

struct Ganttchart {
    string name;
    float start, end;
};

void GanttChart(const vector<Ganttchart> &gantt) {
    // Gantt Chart (put it as a separate function)
    cout << endl << "Gantt Chart" << endl;
    for (const auto& g : gantt) cout << "--------";
    cout << "-\n|";
    for (const auto& g : gantt) cout << "   " << setw(4) << left << g.name << "|";
    cout << endl;
    for (const auto& g : gantt) cout << "--------";
    cout << "-\n";
    cout << fixed << setprecision(0) << setw(8) << gantt[0].start;
    for (const auto& g : gantt) cout << setw(8) << g.end;
    cout << endl;
}

void RoundRobin(vector<Process>& P, float quantum) {
    Sort_By_AT(P);
    queue<int> q;
    vector<Ganttchart> gantt;
    int i, j, completed = 0, n = P.size();
    int Total_Turn_Around_Time = 0, Total_Waiting_Time = 0;
    float time = 0, total_TAT = 0, total_WT = 0;

    vector<bool> inQueue(n, false);

    q.push(0);
    inQueue[0] = true;
    time = P[0].Arrival_time;

    while (completed < n) {
        if (q.empty()) {
            for (i = 0; i < n; i++) {
                if (!inQueue[i] && P[i].Remaining_time > 0) {
                    time = P[i].Arrival_time;
                    q.push(i);
                    inQueue[i] = true;
                    break;
                }
            }
        }

        i = q.front();
        q.pop();

        // Record start time if not started yet
        if (!P[i].started) {
            P[i].Start_time = time;
            P[i].started = true;
        }

        float exec_time = min(quantum, P[i].Remaining_time);
        float start = time;
        time += exec_time;
        float end = time;
        gantt.push_back({ P[i].Process_name, start, end });

        P[i].Remaining_time -= exec_time;

        // Add new arrivals to queue
        for (j = 0; j < n; j++) {
            if (!inQueue[j] && P[j].Arrival_time <= time && P[j].Remaining_time > 0) {
                q.push(j);
                inQueue[j] = true;
            }
        }

        // If process not finished, push it again
        if (P[i].Remaining_time > 0) {
            q.push(i);
        } else {
            P[i].Completion_time = time;
            P[i].Turnaround_time = P[i].Completion_time - P[i].Arrival_time;
            P[i].Waiting_time = P[i].Turnaround_time - P[i].Burst_time;
            completed++;

            Total_Turn_Around_Time += P[i].Turnaround_time;
            Total_Waiting_Time += P[i].Waiting_time;
        }
    }

    float Average_Turn_Around_Time = Total_Turn_Around_Time / n;
    float Average_Waiting_Time = Total_Waiting_Time / n;

    displayProcesses(P, Average_Turn_Around_Time, Average_Waiting_Time);
    GanttChart(gantt);
}

int main() {
    int Process_Count;
    float quantum;

    cout << "Enter the number of processes: ";
    cin >> Process_Count;

    vector<Process> P(Process_Count);
    for (int i = 0; i < Process_Count; i++)
        P[i].CreateProcess(i);

    cout << endl << "Enter Time Quantum: ";
    cin >> quantum;

    RoundRobin(P, quantum);

    return 0;
}

/*
5
P1
0
9
P2
1
4
P3
2
11
P4
3
5
P5
6
8
3
*/

/*
3
P1
1
10
P2
2
6
P3
5
3
3
*/