#include <iostream>
using namespace std;

class Process {
public:
    int p_id;
    int arr_time;
    int burst_time;
    int wait_time;
    int ttime;
    bool completed;

    Process() {
        p_id = 0;
        arr_time = 0;
        burst_time = 0;
        wait_time = 0;
        ttime = 0;
        completed = false;
    }
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process processes[20]; 

    for (int i = 0; i < n; i++) {
        processes[i].p_id = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arr_time >> processes[i].burst_time;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arr_time > processes[j + 1].arr_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int completedCount = 0;
    int currentTime = 0;

    while (completedCount < n) {
        int idx = -1;
        int minBurst = 1000000;

        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arr_time <= currentTime) {
                if (processes[i].burst_time < minBurst) {
                    minBurst = processes[i].burst_time;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            currentTime++;
            continue;
        }

        currentTime += processes[idx].burst_time;

        processes[idx].ttime = currentTime - processes[idx].arr_time;
        processes[idx].wait_time = processes[idx].ttime - processes[idx].burst_time;
        processes[idx].completed = true;
        completedCount++;
    }

    cout << "P\tAt\tBt\tTt\tWt\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].p_id << "\t" << processes[i].arr_time << "\t" << processes[i].burst_time << "\t"
             << processes[i].ttime << "\t" << processes[i].wait_time << "\n";
    }

    return 0;
}

