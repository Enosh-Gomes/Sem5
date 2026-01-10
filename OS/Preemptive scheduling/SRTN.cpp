#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Process {
public:
    string Process_name;
    float Arrival_time;
    float Burst_time;
    float Completion_time;
    float Turnaround_time;
    float Waiting_time;
    float Start_time;
    float Remaining_time;
    bool done;

    Process() {
        Process_name = "";
        Arrival_time = Burst_time = Completion_time = Turnaround_time = Waiting_time = Start_time = 0;
        Remaining_time = 0;
        done = false;
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

struct Segment {
    string name;
    float start;
    float end;
};

void GanttChart(const vector<pair<string, pair<float, float>>> &timeline) {
    int size = timeline.size();
    const int width = 10;

    cout << "\nGantt Chart\n";

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < width; j++)
            cout << "-";
        cout << "-";
    }
    cout << "-\n";

    for (int i = 0; i < size; i++) {
        cout << "|";
        int leftPadding = (width - (int)timeline[i].first.size()) / 2;
        int rightPadding = width - leftPadding - (int)timeline[i].first.size();
        cout << setw(leftPadding + (int)timeline[i].first.size()) << right << timeline[i].first;
        cout << setw(rightPadding) << " ";
    }
    cout << "|\n";

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < width; j++)
            cout << "-";
        cout << "-";
    }
    cout << "-\n";

    cout << fixed << setprecision(0);
    cout << timeline[0].second.first;
    for (int i = 0; i < size; i++) {
        cout << setw(width + 1) << timeline[i].second.second;
    }
    cout << "\n";
}

void displayProcesses(const vector<Process> &P, float average_Turn_Around_Time, float average_Waiting_Time) {
    cout << endl
        << "------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(15) << "Process Name"
        << setw(15) << "Arrival Time"
        << setw(12) << "Burst Time"
        << setw(17) << "Completion Time"
        << setw(19) << "Turn Around Time"
        << setw(17) << "Waiting Time" << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    for (const auto &process : P)
        process.DisplayProcess();

    cout << "------------------------------------------------------------------------------------------" << endl;
    cout << "\nAverage Turn Around Time: " << average_Turn_Around_Time << "\n";
    cout << "Average Waiting Time: " << average_Waiting_Time << "\n";
}

void SRTN(vector<Process> &P) {
    int n = P.size();
    int completed = 0;
    float Current_Time = 0;
    float Total_Turn_Around_Time = 0;
    float Total_Waiting_Time = 0;

    vector<Segment> execution;

    while (completed < n) {
        int index = -1;
        float min_RT = 1e9;

        for (int i = 0; i < n; i++) {
            if (!P[i].done && P[i].Arrival_time <= Current_Time) {
                if (P[i].Remaining_time < min_RT) {
                    min_RT = P[i].Remaining_time;
                    index = i;
                } else if (P[i].Remaining_time == min_RT && P[i].Arrival_time < P[index].Arrival_time) {
                    index = i;
                }
            }
        }

        if (index == -1) {
            Current_Time++;
            continue;
        }

        if (P[index].Remaining_time == P[index].Burst_time)
            P[index].Start_time = Current_Time;

        if (execution.empty() || execution.back().name != P[index].Process_name) {
            execution.push_back({P[index].Process_name, Current_Time, Current_Time + 1});
        } else {
            execution.back().end = Current_Time + 1;
        }

        P[index].Remaining_time--;
        Current_Time++;

        if (P[index].Remaining_time == 0) {
            P[index].done = true;
            P[index].Completion_time = Current_Time;
            P[index].Turnaround_time = P[index].Completion_time - P[index].Arrival_time;
            P[index].Waiting_time = P[index].Turnaround_time - P[index].Burst_time;

            Total_Turn_Around_Time += P[index].Turnaround_time;
            Total_Waiting_Time += P[index].Waiting_time;

            completed++;
        }
    }

    vector<pair<string, pair<float, float>>> timeline;
    for (auto &seg : execution)
        timeline.push_back({seg.name, {seg.start, seg.end}});

    float Average_Turn_Around_Time = Total_Turn_Around_Time / n;
    float Average_Waiting_Time = Total_Waiting_Time / n;

    displayProcesses(P, Average_Turn_Around_Time, Average_Waiting_Time);
    GanttChart(timeline);
}

int main() {
    int Process_Count;
    cout << "Enter the number of processes: ";
    cin >> Process_Count;

    vector<Process> P(Process_Count);
    for (int i = 0; i < Process_Count; i++)
        P[i].CreateProcess(i);

    SRTN(P);

    return 0;
}

/*
4
A
2
6
B
1
8
C
3
3
D
4
1
*/