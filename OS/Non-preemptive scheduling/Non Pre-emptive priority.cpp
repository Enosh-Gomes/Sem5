#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Process {
public:
    string Process_name;
    float Arrival_time;
    float Burst_time;
    int Priority;
    float Completion_time;
    float Turnaround_time;
    float Waiting_time;
    float Start_time;
    bool done;

    Process() {
        Process_name = "";
        Arrival_time = Burst_time = Completion_time = Turnaround_time = Waiting_time = Start_time = 0;
        Priority = 0;
        done = false;
    }

    Process(string n, float at = 0, float bt = 0, int pr = -1) {
        Process_name = n;
        Arrival_time = at;
        Burst_time = bt;
        Priority = (pr == -1) ? static_cast<int>(bt) : pr;
        Completion_time = Turnaround_time = Waiting_time = Start_time = 0;
        done = false;
    }

    ~Process() {}

    void CreateProcess(int index) {
        cout << "\nEnter name for process " << index + 1 << ": ";
        cin >> Process_name;
        cout << "Enter arrival time for process " << index + 1 << ": ";
        cin >> Arrival_time;
        cout << "Enter burst time for process " << index + 1 << ": ";
        cin >> Burst_time;
        cout << "Enter priority for process " << index + 1 << " (or -1 to let the system decide): ";
        cin >> Priority;
    }

    void CalculateTimes(float start_time) {
        Start_time = start_time;
        Completion_time = Start_time + Burst_time;
        Turnaround_time = Completion_time - Arrival_time;
        Waiting_time = Turnaround_time - Burst_time;
        done = true;
    }

    void DisplayProcess() const {
        cout << left << setw(5) << "" << setw(16) << Process_name
            << setw(13) << Arrival_time
            << setw(12) << Burst_time
            << setw(12) << Priority
            << setw(17) << Completion_time
            << setw(17) << Turnaround_time
            << Waiting_time << "\n";
    }
};

void GanttChart(const vector<Process> &P) {
    int size = P.size();
    const int width = 8;

    cout << "\nGantt Chart\n";

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < width; j++) cout << "-";
        cout << "-";
    }
    cout << "-\n";

    for (int i = 0; i < size; i++) {
        cout << "|";
        int leftPadding = (width - (int)P[i].Process_name.size()) / 2;
        int rightPadding = width - leftPadding - (int)P[i].Process_name.size();
        cout << setw(leftPadding + (int)P[i].Process_name.size()) << right << P[i].Process_name;
        cout << setw(rightPadding) << " ";
    }
    cout << "|\n";

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < width; j++) cout << "-";
        cout << "-";
    }
    cout << "-\n";

    cout << (int)P[0].Start_time;
    for (int i = 0; i < size; i++) {
        cout << setw(width + 1) << (int)P[i].Completion_time;
    }
    cout << "\n";
}

void displayProcesses(const vector<Process> &P, float average_Turn_Around_Time, float average_Waiting_Time) {
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(15) << "Process Name"
        << setw(15) << "Arrival Time"
        << setw(12) << "Burst Time"
        << setw(10) << "Priority"
        << setw(17) << "Completion Time"
        << setw(19) << "Turn Around Time"
        << setw(16) << "Waiting Time" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    for (const auto &process : P) process.DisplayProcess();
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "\nAverage Turn Around Time: " << average_Turn_Around_Time << "\n";
    cout << "Average Waiting Time: " << average_Waiting_Time << "\n";
}

void PriorityScheduling(vector<Process> &P) {
    int Process_Size = P.size();
    float Current_Time = 0;
    float Total_Turn_Around_Time = 0;
    float Total_Waiting_Time = 0;
    vector<Process> executionOrder;

    int completed = 0;
    while (completed < Process_Size) {
        int idx = -1;
        int bestPriority = 1e9;

        for (int i = 0; i < Process_Size; i++) {
            if (!P[i].done && P[i].Arrival_time <= Current_Time) {
                if (P[i].Priority < bestPriority) {
                    bestPriority = P[i].Priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            Current_Time++;
            continue;
        }

        P[idx].CalculateTimes(Current_Time);
        Current_Time = P[idx].Completion_time;

        Total_Turn_Around_Time += P[idx].Turnaround_time;
        Total_Waiting_Time += P[idx].Waiting_time;
        executionOrder.push_back(P[idx]);

        completed++;
    }

    float Average_Turn_Around_Time = Total_Turn_Around_Time / Process_Size;
    float Average_Waiting_Time = Total_Waiting_Time / Process_Size;

    displayProcesses(P, Average_Turn_Around_Time, Average_Waiting_Time);

    GanttChart(executionOrder);
}

int main() {
    int Process_Count;
    cout << "Enter the number of processes: ";
    cin >> Process_Count;

    vector<Process> P(Process_Count);
    for (int i = 0; i < Process_Count; i++) P[i].CreateProcess(i);

    PriorityScheduling(P);

    return 0;
}

/*
4
A
0
5
4
B
2
7
2
C
3
3
1
D
8
6
3

*/