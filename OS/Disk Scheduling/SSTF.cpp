#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <climits>
using namespace std;

void initialize(int *cylinders, vector<int> &requestQueue, int *currentHead) {
    cout << "\nEnter number of cylinders: ";
    cin >> *cylinders;

    cout << "Enter request queue (-1 to exit): ";
    int req;
    
    while (true) {
        cin >> req;
        if (req == -1) {
            break;
        }
        requestQueue.push_back(req);
    }
    
    cout << "Enter current head position: ";
    cin >> *currentHead;
}

void SSTF() {
    int cylinders, currentHead;
    vector<int> requestQueue;

    initialize(&cylinders, requestQueue, &currentHead);
    
    cout << "\n" << string(28, '-') << endl;
    cout << left << setw(10) << "From"
        << setw(10) << "To"
        << setw(10) << "Distance" << endl;
    cout << string(28, '-') << endl;
    
    vector<int> trackSequence;
    trackSequence.push_back(currentHead);
    int totalHeadMovement = 0;
    
    vector<bool> serviced(requestQueue.size(), false);
    
    for (int i = 0; i < requestQueue.size(); i++) {
        int minDistance = INT_MAX;
        int closestIndex = -1;
        
        for (int j = 0; j < requestQueue.size(); j++) {
            if (!serviced[j]) {
                int distance = abs(requestQueue[j] - currentHead);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestIndex = j;
                }
            }
        }
        
        if (closestIndex != -1) {
            int request = requestQueue[closestIndex];
            serviced[closestIndex] = true;
            totalHeadMovement += minDistance;
                        
            cout << left << setw(10) << currentHead
                << setw(10) << request
                << setw(10) << minDistance << endl;
            
            currentHead = request;
            trackSequence.push_back(currentHead);
        }
    }
    
    cout << string(28, '-') << endl;
    
    cout << "\nTrack sequence: ";
    cout << trackSequence[0];
    for (int i = 1; i < trackSequence.size(); i++) {
        cout << " -> " << trackSequence[i];
    }
    cout << "\nTotal head movement: " << totalHeadMovement << endl;
}

int main() {
    SSTF();
    return 0;
}