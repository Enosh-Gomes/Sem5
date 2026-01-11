#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

void initialize(int *cylinders, vector<int> &requestQueue, int *currentHead, int *previousHead) {
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

    cout << "Enter previous head position: ";
    cin >> *previousHead;
}

void LOOK() {
    int i, cylinders, currentHead, previousHead;
    vector<int> requestQueue;

    initialize(&cylinders, requestQueue, &currentHead, &previousHead);

    sort(requestQueue.begin(), requestQueue.end());
    
    vector<int> Left, Right;
    int queueSize = requestQueue.size();

    for (int i = 0; i < queueSize; i++) {
        if (requestQueue[i] < currentHead)
            Left.push_back(requestQueue[i]);
        else
            Right.push_back(requestQueue[i]);
    }
    
    sort(Left.begin(), Left.end());
    sort(Right.begin(), Right.end());
    
    cout << "\n" << string(28, '-') << endl;
    cout << left << setw(10) << "From"
        << setw(10) << "To"
        << setw(10) << "Distance" << endl;
    cout << string(28, '-') << endl;
    
    vector<int> seekSequence;
    vector<int> trackSequence;
    trackSequence.push_back(currentHead);
    
    if (currentHead - previousHead >= 0) {
        seekSequence.insert(seekSequence.end(), Right.begin(), Right.end());
        
        reverse(Left.begin(), Left.end());
        seekSequence.insert(seekSequence.end(), Left.begin(), Left.end());
    } else {

        reverse(Left.begin(), Left.end());
        seekSequence.insert(seekSequence.end(), Left.begin(), Left.end());
        
        seekSequence.insert(seekSequence.end(), Right.begin(), Right.end());
    }
    
    int totalHeadMovement = 0, distance = 0, seekSize = seekSequence.size();

    for (i = 0; i < seekSize; i++) {
        distance = abs(seekSequence[i] - currentHead);
        totalHeadMovement += distance;
        
        cout << left << setw(10) << currentHead
            << setw(10) << seekSequence[i]
            << setw(10) << distance << endl;
        
        currentHead = seekSequence[i];
        trackSequence.push_back(currentHead);
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
    LOOK();
    return 0;
}

/*
200
99 52 10 72 131 107 89 66 187 85 222 244 218 -1
70
71
*/