#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;

void display_Frame(vector<string> reference_string, vector<string>& frame, int page, int frames, bool page_hit) {
    cout << setw(4) << reference_string[page] << "  | ";
    for(int i = 0; i < frames; i++) {
        cout << setw(2) << frame[i] << "  ";
    }
    cout << "|";
    if(!page_hit)
        cout << setw(14) << "Page Fault!" << endl;
    else
        cout << setw(12) << "Page Hit!" << endl;
}

void FIFOPageReplacement(vector<string> reference_string, vector<string>& frame, int frames) {
    int page_faults = 0, fifo_index = 0;
    int reference_length = reference_string.size();

    cout << "\n Page |";

    int total_frame_width = frames * 4;
    int left_padding = (total_frame_width - 6) / 2;

    cout << setw(left_padding + 6) << "Frames"
        << setw(total_frame_width - left_padding - 4) << "|";

    cout << "   Hit/Fault" << endl;

    cout << "      |";
    for (int i = 0; i < frames; i++) {
        cout << " [" << i << "]";
    }
    cout << " |" << endl;

    cout << string(24 + total_frame_width, '-') << endl;

    for(int i = 0; i < reference_length; i++) {
        bool page_hit = false;

        for(int j = 0; j < frames; j++) {
            if(frame[j] == reference_string[i]) {
                page_hit = true;
                display_Frame(reference_string, frame, i, frames, page_hit);
                break;
            }
        }

        if(!page_hit) {
            page_faults++;

            int empty_index = -1;
            for(int j = 0; j < frames; j++) {
                if(frame[j] == "-") {
                    empty_index = j;
                    break;
                }
            }

            if(empty_index != -1) {
                frame[empty_index] = reference_string[i];
            } else {
                frame[fifo_index] = reference_string[i];
                fifo_index = (fifo_index + 1) % frames;
            }

            display_Frame(reference_string, frame, i, frames, page_hit);
        }
    }

    cout << "\nPage Faults: " << page_faults;
    cout << "\nPage Hits: " << reference_length - page_faults << endl;
}

int main() {
    vector<string> reference_string;
    int frames, pages;
    string ref;

    cout << "Enter the number of pages: ";
    cin >> pages;
    cout << "Enter reference string: ";

    for(int i = 0; i < pages; i++) {
        cin >> ref;
        reference_string.push_back(ref);
    }

    cout << "Enter the number of frames: ";
    cin >> frames;
    vector<string> frame(frames, "-");

    FIFOPageReplacement(reference_string, frame, frames);

    return 0;
}

/*
22
7 0 1 2 0 3 0 4 2 3 0 3 0 3 2 1 2 0 1 7 0 1
4
*/