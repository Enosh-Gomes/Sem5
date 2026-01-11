#include <iostream>
#include <iomanip>
#define MAX 10
using namespace std;

int allocation[MAX][MAX], Max[MAX][MAX], need[MAX][MAX];
int available[MAX], request[MAX];
int n, r;

void display() {
    cout << "\n----------------------------------------------------------\n";
    cout << "Process" << setw(14) << "Allocation" << setw(9) << "Max" << setw(4) << " " << setw(12) << "Available" << setw(10) << "Need";
    cout << "\n----------------------------------------------------------\n";
    int i, j;
    for(i = 0; i < n; i++) {
        cout << "P" << i << setw(9) << " ";

        for(j = 0; j < r; j++)
            cout << setw(2) << allocation[i][j] << " ";
        
        cout << setw(4) << " ";
        for(j = 0; j < r; j++)
            cout << setw(2) << Max[i][j] << " ";

        cout << setw(4) << " ";
        if(i == 0)
            for(j = 0; j < r; j++)
                cout << setw(2) << available[j] << " ";
        else
            for(j = 0; j < r; j++)
                cout << setw(3) << " ";

        cout << setw(4) << " ";
        for(j = 0; j < r; j++)
            cout << setw(2) << need[i][j] << " ";
        cout << endl;
    }
    cout << "\n----------------------------------------------------------\n";
}

bool isSafeSequence() {
    int work[MAX];
    bool finish[MAX] = {false};
    int safeSeq[MAX], count = 0;
    int i, j;

    for(i = 0; i < r; i++)
        work[i] = available[i];

    bool found;
    do {
        found = false;
        for(i = 0; i < n; i++) {
            if(!finish[i]) {
                bool canRun = true;
                for(j = 0; j < r; j++) {
                    if(need[i][j] > work[j]) {
                        canRun = false;
                        break;
                    }
                }
                if(canRun) {
                    for(j = 0; j < r; j++)
                        work[j] += allocation[i][j];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
    } while(found);

    for(i = 0; i < n; i++) {
        if(!finish[i]) {
            cout << "\nSystem is NOT in a safe state.\n";
            return false;
        }
    }

    cout << "\nSystem is in a SAFE state.\nSafe Sequence: ";
    cout << "<P" << safeSeq[0];
    for(i = 1; i < n; i++)
        cout << ", P" << safeSeq[i];
    cout << ">\n";
    return true;
}

void InitialiseResources() {
    cout << "\n============================================\n";
    cout << setw(33) << "Initialise Resources";
    cout << "\n============================================\n";
    cout << "\nEnter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resource types: ";
    cin >> r;

    int i, j;

    cout << "\nEnter Allocation Matrix:\n";
    for(i = 0; i < n; i++) {
        cout << "P" << i << ": ";
        for(j = 0; j < r; j++)
            cin >> allocation[i][j];
    }

    cout << "\nEnter Max Matrix:\n";
    for(i = 0; i < n; i++) {
        cout << "P" << i << ": ";
        for(j = 0; j < r; j++)
            cin >> Max[i][j];
    }

    cout << "\nEnter Available Resources: ";
    for(i = 0; i < r; i++)
        cin >> available[i];

    for(i = 0; i < n; i++)
        for(j = 0; j < r; j++)
            need[i][j] = Max[i][j] - allocation[i][j];

    display();
    if(!isSafeSequence()) {
        exit(1);
    }
}

bool RequestResources() {
    int i, p;
    bool cannotGrant = true;
    cout << "\n============================================\n";
    cout << setw(33) << "Request Executing Menu";
    cout << "\n============================================\n";
    cout << "\nEnter process number making request (0-" << n - 1 << "): ";
    cin >> p;

    cout << "Enter request vector: ";
    for(i = 0; i < r; i++)
        cin >> request[i];

    for(i = 0; i < r; i++) {
        if(request[i] > need[p][i]) {
            cout << "\nProcess has exceeded its maximum claim.\nRequest cannot be granted\n";
            return false;
        }
        if(request[i] > available[i]) {
            cout << "\nProcess must wait. Insufficient resources.\n";
            return false;
        }
    }

    for(i = 0; i < r; i++) {
        if(available[i] - request[i] > 0) {
            cannotGrant = false;
            break;
        }
    }

    if(cannotGrant) {
        cout << "\nRequest cannot be granted. Gives away all resources.\n";
        return false;
    }

    for(i = 0; i < r; i++) {
        available[i] -= request[i];
        allocation[p][i] += request[i];
        need[p][i] -= request[i];
    }

    cout << "\nExecuting Resource-Request Algorithm ...\n";
    cout << "\nTemporary State:\n";
    display();

    if(isSafeSequence()) {
        cout << "\nRequest can be granted immediately.\n";
        display();
        return true;
    }

    for(i = 0; i < r; i++) {
        available[i] += request[i];
        allocation[p][i] -= request[i];
        need[p][i] += request[i];
    }
    cout << "\nRequest cannot be granted. State restored.\n";
    display();
    return false;
}

int main() {
    char ch = 'y';
    InitialiseResources();

    do {
        RequestResources();
        cout << "\nTry another process? (Y/N): ";
        cin >> ch;
    } while(ch == 'y' || ch == 'Y');

    return 0;
}

/*
refer to input test case from the ppt on bankers

5
3
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
3 3 2

requests

3
1 0 0

0
4 0 0

1
1 0 2

0
2 3 0

0
0 2 0

*/