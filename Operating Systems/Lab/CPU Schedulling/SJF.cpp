#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int numberOfProcesses;
    cout << "Enter number of processes: ";
    cin >> numberOfProcesses;

    vector<int> burstTime(numberOfProcesses);
    vector<int> processId(numberOfProcesses);

    // Input burst times
    for (int i = 0; i < numberOfProcesses; i++) {
        cout << "Enter burst time for Process P" << i + 1 << ": ";
        cin >> burstTime[i];
        processId[i] = i + 1;
    }

    // Sort processes based on burst time (SJF)
    for (int i = 0; i < numberOfProcesses - 1; i++) {
        for (int j = i + 1; j < numberOfProcesses; j++) {
            if (burstTime[i] > burstTime[j]) {
                swap(burstTime[i], burstTime[j]);
                swap(processId[i], processId[j]);
            }
        }
    }

    vector<int> waitingTime(numberOfProcesses, 0);
    vector<int> turnaroundTime(numberOfProcesses, 0);

    // First process
    waitingTime[0] = 0;
    turnaroundTime[0] = burstTime[0];

    // Calculate waiting and turnaround times
    for (int i = 1; i < numberOfProcesses; i++) {
        waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
        turnaroundTime[i] = waitingTime[i] + burstTime[i];
    }

    // Output results
    double totalWaitingTime = 0, totalTurnaroundTime = 0;

    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";

    for (int i = 0; i < numberOfProcesses; i++) {
        cout << "P" << processId[i] << "\t"
             << burstTime[i] << "\t\t"
             << waitingTime[i] << "\t\t"
             << turnaroundTime[i] << endl;

        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    cout << "\nAverage Waiting Time: "
         << totalWaitingTime / numberOfProcesses << endl;

    cout << "Average Turnaround Time: "
         << totalTurnaroundTime / numberOfProcesses << endl;

    return 0;
}

