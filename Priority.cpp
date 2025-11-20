#include <iostream>
#include <limits.h>
using namespace std;

class Process {
public:
    int id, at, bt, pr, ct, tat, wt, rbt;
    bool done;

    Process() {
        id = at = bt = pr = ct = tat = wt = rbt = 0;
        done = false;
    }
};

//Priority Non-Preemptive
void priorityNonPreemptive(Process p[], int n) {
    int time = 0, completed = 0;
    double totalTAT = 0, totalWT = 0;

    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time && p[i].pr < highestPriority) {
                highestPriority = p[i].pr;
                idx = i;
            }
        }

        if (idx != -1) {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].done = true;
            totalTAT += p[idx].tat;
            totalWT += p[idx].wt;
            completed++;
        } else {
            time++;
        }
    }

    cout << "\n=== Priority Scheduling (Non-Preemptive) ===\n";
    cout << "Process\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].pr
             << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\n";
    }
    cout << "\nAverage Turnaround Time = " << totalTAT / n;
    cout << "\nAverage Waiting Time = " << totalWT / n << endl;
}

//Priority Preemptive
void priorityPreemptive(Process p[], int n) {
    int time = 0, completed = 0;
    double totalTAT = 0, totalWT = 0;

    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time && p[i].pr < highestPriority) {
                highestPriority = p[i].pr;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].rbt--;
            time++;

            if (p[idx].rbt == 0) {
                p[idx].done = true;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                totalTAT += p[idx].tat;
                totalWT += p[idx].wt;
                completed++;
            }
        } else {
            time++;
        }
    }

    cout << "\n=== Priority Scheduling (Preemptive) ===\n";
    cout << "Process\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].pr
             << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\n";
    }
    cout << "\nAverage Turnaround Time = " << totalTAT / n;
    cout << "\nAverage Waiting Time = " << totalWT / n << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter Arrival Time for P" << i + 1 << ": ";
        cin >> p[i].at;
        cout << "Enter Burst Time for P" << i + 1 << ": ";
        cin >> p[i].bt;
        cout << "Enter Priority for P" << i + 1 << ": ";
        cin >> p[i].pr;
        p[i].rbt = p[i].bt;
    }

    priorityNonPreemptive(p, n);

    // Reset values before running next algorithm
    for (int i = 0; i < n; i++) {
        p[i].rbt = p[i].bt;
        p[i].done = false;
        p[i].ct = p[i].tat = p[i].wt = 0;
    }

    priorityPreemptive(p, n);

    return 0;
}

