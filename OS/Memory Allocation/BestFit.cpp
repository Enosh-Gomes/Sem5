#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

class SegmentRegion {
public:
    int max_space;
    int free_space;
    vector<int> segments;
    SegmentRegion() {}
};

class Process {
public:
    int process_number;
    int process_size;
    Process() {}
};

int Process_number(SegmentRegion region[], int i, int j, Process process[], int m) {
    int k;
    for(k = 0; k < m; k++) {
        if(region[i].segments[j] == process[k].process_size) {
            break;
        }
    }
    return process[k].process_number;
}

void displayMemoryStatus(SegmentRegion region[], int n, Process process[], int m) {
    cout << "\n----------------------------------------------------------------------------------------";
    cout << "\n| Process | Process Size (in KB) | Segment Capacity (in KB) | Memory Available (in KB) |";
    cout << "\n----------------------------------------------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        int l = region[i].segments.size();
        for (int j = 0; j < l; j++) {
            cout << "|" << setw(5) << Process_number(region, i, j, process, m) << setw(5) << " |"
                << setw(12) << region[i].segments[j] << setw(12) << " | "
                << setw(14) << region[i].max_space << setw(12) << " |"
                << setw(14) << region[i].free_space << setw(14) << " |\n";
        }
        if (l == 0) {
            cout << "|" << setw(5) << "-" << setw(5) << " |"
                << setw(11) << "-" << setw(13) << " | "
                << setw(14) << region[i].max_space << setw(12) << " |"
                << setw(14) << region[i].free_space << setw(14) << " |\n";
        }
    }
    cout << "----------------------------------------------------------------------------------------\n";
}

void bestFitAllocate(SegmentRegion region[], int n, int process_size, vector<string>& logs) {
    int bestIdx = -1;
    int minRemaining = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (region[i].free_space >= process_size) {
            int remaining = region[i].free_space - process_size;
            if (remaining < minRemaining) {
                minRemaining = remaining;
                bestIdx = i;
            }
        }
    }

    if (bestIdx != -1) {
        region[bestIdx].segments.push_back(process_size);
        region[bestIdx].free_space -= process_size;

        string log = "Process of size " + to_string(process_size)
                    + " KB allocated in segment of size "
                    + to_string(region[bestIdx].max_space) + " KB";
        logs.push_back(log);
    } else {
        string log = "No sufficient space available for process of size " + to_string(process_size) + " KB";
        logs.push_back(log);
    }
}

int main() {
    int n, m;

    cout << "\nEnter number of free segments: ";
    cin >> n;
    SegmentRegion region[n];

    for (int i = 0; i < n; i++) {
        cout << "Enter segment capacity for segment " << i << " (in KB): ";
        cin >> m;
        region[i].max_space = m;
        region[i].free_space = m;
        region[i].segments = vector<int>(0);
    }

    cout << "\nEnter number of processes: ";
    cin >> m;

    Process process[m];

    cout << "Enter process sizes (in KB):\n";
    for (int i = 0; i < m; i++) {
        process[i].process_number = i;
        cout << "Process " << i << ": ";
        cin >> process[i].process_size;
    }

    vector<string> logs;
    
    for (Process p : process)
        bestFitAllocate(region, n, p.process_size, logs);

    displayMemoryStatus(region, n, process, m);

    cout << endl;
    for (string log : logs)
        cout << log << endl;

    return 0;
}