#include<iostream>
#include<vector>
#include<iomanip>

using namespace std;

const int buffer_size = 5;
int in = 0, out = 0;
int Mutex = 1, Full = 0, Empty = buffer_size;

vector<string> buffer(buffer_size);

void wait(int *S) {
    if((*S) <= 0) {
        cout << "Wait operation failed: semaphore value is zero." << endl;
        return;
    }
    (*S)--;
}

void signal(int *S) {
    (*S)++;
}

void producer(string item) {
        wait(&Empty);
        wait(&Mutex);

        buffer[in] = item;
        cout << endl << "Produced: " << item << " at position " << in << endl;
        in = (in + 1) % buffer_size;

        signal(&Mutex);
        signal(&Full);
}

void consumer(string item) {
        wait(&Full);
        wait(&Mutex);

        item = buffer[out];
        buffer[out] = "_";
        cout << endl << "Consumed: " << item << " from position " << out << endl;
        out = (out + 1) % buffer_size;

        signal(&Mutex);
        signal(&Empty);
}

void DisplayBuffer() {
    int i;

    cout << "+---------------------+" << endl;
    cout << "|   Buffer Contents   |" << endl;
    cout << "+---------------------+" << endl;
    cout << "| Index  |  Content   |" << endl;
    cout << "+---------------------+" << endl;
    for(i = 0; i < buffer_size; i++) {
        cout << "|   " << i << "    | " << setw(6) << buffer[i] << setw(6) << "|" << endl;
    }
    cout << "+---------------------+" << endl;
    cout << "| Empty slots : " << setw(3) << Empty << setw(4) << "|" << endl;
    cout << "| Full slots  : " << setw(3) << Full << setw(4) << "|" << endl;
    cout << "| IN pointer  : " << setw(3) << in << setw(4) << "|" << endl;
    cout << "| OUT pointer : " << setw(3) << out << setw(4) << "|" << endl;
    cout << "+---------------------+" << endl;
}

int main() {
    int ch;
    string item;

    for(int i = 0; i < buffer_size; i++)
        buffer[i] = "_";

    do {
        cout << endl << "--- MENU ---" << endl;
        cout << "1. Produce Item" << endl;
        cout << "2. Consume Item" << endl;
        cout << "3. Display Buffer" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> ch;
        cout << endl;

        switch(ch) {
            case 1:
                if (Empty == 0 )
                    cout << "Buffer is full, cannot produce item." << endl;
                else {
                    cout << "Enter item to produce: ";
                    cin >> item;
                    producer(item);
                }
                break;
            case 2:
                if (Full == 0 )
                    cout << "Buffer is empty, cannot consume item." << endl;
                else
                    consumer(item);
                break;
            case 3:
                DisplayBuffer();
                break;
            case 4:
                cout << "Exiting..." << endl;
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(true);

    return 0;
}