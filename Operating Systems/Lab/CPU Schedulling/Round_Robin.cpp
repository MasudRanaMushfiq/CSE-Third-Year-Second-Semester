#include <iostream>
#include <vector>
using namespace std;

int main() {
    int numberOfProcesses;
    cout << "Enter number of processes: ";
    cin >> numberOfProcesses;

    vector<int> burstTime(numberOfProcesses);
    vector<int> remainingTime(numberOfProcesses);
    vector<int> waitingTime(numberOfProcesses, 0);
    vector<int> turnaroundTime(numberOfProcesses, 0);

    // Input burst times
    for (int i = 0; i < numberOfProcesses; i++) {
        cout << "Enter burst time for Process P" << i + 1 << ": ";
        cin >> burstTime[i];
        remainingTime[i] = burstTime[i];
    }

    int timeQuantum;
    cout << "Enter Time Quantum: ";
    cin >> timeQuantum;

    int currentTime = 0;
    int processesRemaining = numberOfProcesses;

    // Round Robin Scheduling
    while (processesRemaining > 0) {
        for (int i = 0; i < numberOfProcesses; i++) {
            if (remainingTime[i] > 0) {
                
                if (remainingTime[i] <= timeQuantum) {
                    // Process finishes in this cycle
                    currentTime += remainingTime[i];
                    remainingTime[i] = 0;

                    turnaroundTime[i] = currentTime;
                    waitingTime[i] = turnaroundTime[i] - burstTime[i];

                    processesRemaining--;
                } else {
                    // Process executes for time quantum
                    remainingTime[i] -= timeQuantum;
                    currentTime += timeQuantum;
                }
            }
        }
    }

    // Output results
    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;

    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";

    for (int i = 0; i < numberOfProcesses; i++) {
        cout << "P" << i + 1 << "\t"
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

