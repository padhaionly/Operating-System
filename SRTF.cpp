#include <iostream>
#include <algorithm>
using namespace std;

class Process {
    public:
    int id, at, bt, ct, tat, wt, rbt;
};

bool compareArrival(Process a, Process b) {
    return a.at < b.at;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process pro[n];

    for (int i = 0; i < n; i++) {
        pro[i].id = i + 1;
        cout << "Enter Arrival time of P" << i + 1 << ": ";
        cin >> pro[i].at;
        cout << "Enter Burst time of P" << i + 1 << ": ";
        cin >> pro[i].bt;
        pro[i].rbt = pro[i].bt;
    }

    sort(pro, pro + n, compareArrival);

    int time = 0;     
    int completed = 0; 

    while (completed < n) {
        int idx = -1;
        int minRBT = 1000000;

        for (int i = 0; i < n; i++) {
            if (pro[i].at <= time && pro[i].rbt > 0) {
                if (pro[i].rbt < minRBT) {
                    minRBT = pro[i].rbt;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            pro[idx].rbt--;
            time++;

            if (pro[idx].rbt == 0) {
                pro[idx].ct = time;
                completed++;
            }
        } else {
            time++;
        }
    }

    // Calculate TAT and WT
    double avgTAT = 0, avgWT = 0;
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        pro[i].tat = pro[i].ct - pro[i].at;
        pro[i].wt = pro[i].tat - pro[i].bt;
        avgTAT += pro[i].tat;
        avgWT += pro[i].wt;

        cout << "P" << pro[i].id << "\t\t" 
             << pro[i].at << "\t" 
             << pro[i].bt << "\t" 
             << pro[i].ct << "\t" 
             << pro[i].tat << "\t" 
             << pro[i].wt << "\n";
    }

    cout << "\nAverage Turnaround Time = " << avgTAT / n;
    cout << "\nAverage Waiting Time = " << avgWT / n << endl;

    return 0;
}

