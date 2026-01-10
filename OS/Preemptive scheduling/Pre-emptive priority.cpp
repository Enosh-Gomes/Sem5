#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Process {
public:
    string name;
    float arrival, burst, remaining, completion, turnaround, waiting, priority;
    bool done;

    Process() {
        name = "";
        arrival = burst = remaining = completion = turnaround = waiting = priority = 0;
        done = false;
    }

    void CreateProcess(int index) {
        cout << "\nEnter details for Process " << index + 1 << ":\n";
        cout << "Name: "; cin >> name;
        cout << "Arrival Time: "; cin >> arrival;
        cout << "Burst Time: "; cin >> burst;
        cout << "Priority: "; cin >> priority;
        remaining = burst;
    }

    void DisplayProcess() const {
        cout << left << setw(5) << "" << setw(15) << name
            << setw(15) << arrival
            << setw(12) << burst
            << setw(12) << priority
            << setw(17) << completion
            << setw(19) << turnaround
            << waiting << endl;
    }
};

struct Segment {
    string name;
    float start;
    float end;
};

void GanttChart(const vector<Segment> &timeline) {
    int size = timeline.size();
    const int width = 10;

    cout << "\nGantt Chart\n";

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < width; j++) cout << "-";
        cout << "-";
    }
    cout << "-\n";

    for (int i = 0; i < size; i++) {
        cout << "|";
        int leftPad = (width - (int)timeline[i].name.size()) / 2;
        int rightPad = width - leftPad - (int)timeline[i].name.size();
        cout << setw(leftPad + (int)timeline[i].name.size()) << right << timeline[i].name;
        cout << setw(rightPad) << " ";
    }
    cout << "|\n";

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < width; j++) cout << "-";
        cout << "-";
    }
    cout << "-\n";

    cout << fixed << setprecision(0);
    cout << timeline[0].start;
    for (int i = 0; i < size; i++) {
        cout << setw(width + 1) << timeline[i].end;
    }
    cout << "\n";
}

void displayProcesses(const vector<Process> &P, float avgTAT, float avgWT) {
    cout << endl << "------------------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(15) << "Process Name"
        << setw(15) << "Arrival Time"
        << setw(12) << "Burst Time"
        << setw(12) << "Priority"
        << setw(17) << "Completion Time"
        << setw(19) << "Turn Around Time"
        << setw(17) << "Waiting Time" << endl;
    cout << "------------------------------------------------------------------------------------------------------" << endl;

    for (const auto &process : P)
        process.DisplayProcess();

    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << "\nAverage Turn Around Time: " << avgTAT << "\n";
    cout << "Average Waiting Time: " << avgWT << "\n";
}

void PriorityScheduling(vector<Process> &P) {
    int n = P.size();
    int completed = 0;
    float time = 0, totalTAT = 0, totalWT = 0;

    vector<Segment> execution;

    while (completed < n) {
        int idx = -1;
        float bestPriority = 1e9;

        for (int i = 0; i < n; i++) {
            if (!P[i].done && P[i].arrival <= time) {
                if (P[i].priority < bestPriority) {
                    bestPriority = P[i].priority;
                    idx = i;
                } else if (P[i].priority == bestPriority && P[i].arrival < P[idx].arrival) {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        if (execution.empty() || execution.back().name != P[idx].name) {
            execution.push_back({P[idx].name, time, time + 1});
        } else {
            execution.back().end = time + 1;
        }

        P[idx].remaining--;
        time++;

        if (P[idx].remaining == 0) {
            P[idx].done = true;
            P[idx].completion = time;
            P[idx].turnaround = P[idx].completion - P[idx].arrival;
            P[idx].waiting = P[idx].turnaround - P[idx].burst;

            totalTAT += P[idx].turnaround;
            totalWT += P[idx].waiting;
            completed++;
        }
    }

    float avgTAT = totalTAT / n;
    float avgWT = totalWT / n;

    displayProcesses(P, avgTAT, avgWT);
    GanttChart(execution);
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> P(n);
    for (int i = 0; i < n; i++)
        P[i].CreateProcess(i);

    PriorityScheduling(P);

    return 0;
}

/*
5
P1
6
1
1
P2
1
2
7
P3
2
3
3
P4
1
5
3
P5
4
5
2
*/